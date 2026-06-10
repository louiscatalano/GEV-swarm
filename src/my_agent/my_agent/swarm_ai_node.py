import rclpy
from rclpy.node import Node
import numpy as np
from scipy.spatial import cKDTree

from environment_msgs.msg import LocalMapUpdate, PredictedMap, GuidanceField
from nav_msgs.msg import OccupancyGrid


class Observation:
    """Timestamped observation in the buffer."""
    def __init__(self, i, j, value, age, var):
        self.i = i
        self.j = j
        self.value = value
        self.age = age  # in steps
        self.var = var  # variance


class NowcastSLAM(Node):

    def __init__(self):
        super().__init__('nowcast_slam')

        # Grid parameters
        self.declare_parameter('height', 64)
        self.declare_parameter('width', 64)

        # Advection parameters (in cells per step)
        self.declare_parameter('vx', 0.0)
        self.declare_parameter('vy', 0.0)

        # Observation variance model
        self.declare_parameter('obs_var_init', 0.01)
        self.declare_parameter('obs_var_growth_rate', 0.02)  # per step

        # Interpolation parameters
        self.declare_parameter('interp_sigma', 1.0)  # Gaussian kernel width (cells)

        # Confidence parameters
        self.declare_parameter('confidence_decay_tau', 5.0)  # steps, characteristic decay time
        self.declare_parameter('confidence_distance_scale', 2.0)  # cells, spatial decay scale

        # Buffer management
        self.declare_parameter('max_buffer_age', 30)  # steps

        # Optional OccupancyGrid publishing
        self.declare_parameter('publish_occupancy_grid', False)

        self.height = self.get_parameter('height').value
        self.width = self.get_parameter('width').value
        self.vx = self.get_parameter('vx').value
        self.vy = self.get_parameter('vy').value
        self.obs_var_init = self.get_parameter('obs_var_init').value
        self.obs_var_growth_rate = self.get_parameter('obs_var_growth_rate').value
        self.interp_sigma = self.get_parameter('interp_sigma').value
        self.confidence_decay_tau = self.get_parameter('confidence_decay_tau').value
        self.confidence_distance_scale = self.get_parameter('confidence_distance_scale').value
        self.max_buffer_age = self.get_parameter('max_buffer_age').value
        self.publish_occupancy_grid = self.get_parameter('publish_occupancy_grid').value

        # Observation buffer: list of Observation objects
        self.observations = []

        # Land mask: static cells that are impassable (NaN observations)
        self.land_mask = np.zeros((self.height, self.width), dtype=bool)

        # Running advection offsets (sub-grid position accumulation)
        self.offset_x = 0.0
        self.offset_y = 0.0

        # Current time (in steps)
        self.current_step = 0

        # Subscribe to local observations
        self.create_subscription(
            LocalMapUpdate,
            '/swarm/local_map_update',
            self.observation_callback,
            10
        )

        # Publishers
        self.pred_pub = self.create_publisher(
            PredictedMap,
            '/swarm/predicted_map',
            10
        )

        self.confidence_pub = self.create_publisher(
            GuidanceField,
            '/swarm/guidance',
            10
        )

        self.occ_grid_pub = self.create_publisher(
            OccupancyGrid,
            '/swarm/occupancy_grid',
            10
        )

        # Periodic publishing (once per step callback or can be independent)
        self.create_timer(1.0, self.publish_maps)

        self.get_logger().info(
            f'Nowcast SLAM started | Grid: {self.height}x{self.width} | '
            f'Advection: ({self.vx}, {self.vy}) cells/step | '
            f'Buffer age max: {self.max_buffer_age} steps'
        )

    def observation_callback(self, msg):
        """Process incoming local map update (global grid coordinates)."""
        i, j = msg.i, msg.j
        value = msg.value

        # Validate grid bounds
        if not (0 <= i < self.height and 0 <= j < self.width):
            return

        # Increment time step (each observation callback is one step)
        self.current_step += 1

        # Advance advection offsets
        self.offset_x += self.vx
        self.offset_y += self.vy

        # Extract integer shifts and update offsets
        shift_i = int(np.floor(self.offset_x))
        shift_j = int(np.floor(self.offset_y))
        self.offset_x -= shift_i
        self.offset_y -= shift_j

        # Apply accumulated shifts to all observations in buffer
        if shift_i != 0 or shift_j != 0:
            self._shift_observations(shift_i, shift_j)

        # Age all observations
        for obs in self.observations:
            obs.age += 1
            # Grow variance with age
            obs.var += self.obs_var_growth_rate

        # Discard stale observations
        self.observations = [obs for obs in self.observations if obs.age <= self.max_buffer_age]

        # Process the new observation
        if not np.isfinite(value):
            # NaN = land (immutable)
            self.land_mask[i, j] = True
            # Remove any non-land observations at this cell
            self.observations = [obs for obs in self.observations if not (obs.i == i and obs.j == j)]
        else:
            # Finite observation: add to buffer
            obs = Observation(i, j, value, age=0, var=self.obs_var_init)
            self.observations.append(obs)

    def _shift_observations(self, shift_i, shift_j):
        """Shift all observations by integer grid steps due to accumulated offset."""
        for obs in self.observations:
            obs.i += shift_i
            obs.j += shift_j

        # Also shift land_mask
        if shift_i != 0 or shift_j != 0:
            self.land_mask = np.roll(self.land_mask, shift_i, axis=0)
            self.land_mask = np.roll(self.land_mask, shift_j, axis=1)
            # Clear edges to prevent wrap-around artifacts
            if shift_i > 0:
                self.land_mask[:shift_i, :] = False
            elif shift_i < 0:
                self.land_mask[shift_i:, :] = False
            if shift_j > 0:
                self.land_mask[:, :shift_j] = False
            elif shift_j < 0:
                self.land_mask[:, shift_j:] = False

    def predict_field_and_confidence(self):
        """
        Predict the nowcast field and per-cell confidence by interpolating
        advected observations onto the grid.

        Returns:
            nowcast_field (H x W): interpolated cost values
            confidence_field (H x W): per-cell confidence in [0, 1]
        """
        nowcast = np.zeros((self.height, self.width), dtype=np.float32)
        confidence = np.zeros((self.height, self.width), dtype=np.float32)

        # Land cells: fixed, high confidence
        nowcast[self.land_mask] = np.nan
        confidence[self.land_mask] = 1.0

        if len(self.observations) == 0:
            # No observations: field is neutral and low confidence
            return nowcast, confidence

        # Prepare observation data for interpolation
        obs_positions = np.array([[obs.i + self.offset_x, obs.j + self.offset_y] for obs in self.observations])
        obs_values = np.array([obs.value for obs in self.observations])
        obs_vars = np.array([obs.var for obs in self.observations])

        # Build KD-tree for efficient neighbor queries
        tree = cKDTree(obs_positions)

        # Gaussian-weighted interpolation for each grid cell
        for ii in range(self.height):
            for jj in range(self.width):
                if self.land_mask[ii, jj]:
                    continue

                cell_pos = np.array([ii, jj])

                # Query nearby observations (within 3 * interp_sigma)
                radius = 3.0 * self.interp_sigma
                indices = tree.query_ball_point(cell_pos, r=radius)

                if not indices:
                    # No nearby observations: neutral value, low confidence
                    nowcast[ii, jj] = 0.5
                    confidence[ii, jj] = 0.0
                    continue

                # Compute weighted interpolation
                weights = []
                values = []
                age_confidences = []

                for idx in indices:
                    obs = self.observations[idx]
                    pos = np.array([obs.i + self.offset_x, obs.j + self.offset_y])

                    # Gaussian spatial weight (decays with distance and age-grown variance)
                    kernel_sigma = self.interp_sigma + 0.5 * np.sqrt(obs.var)
                    spatial_dist_sq = np.sum((cell_pos - pos) ** 2)
                    spatial_weight = np.exp(-spatial_dist_sq / (2.0 * kernel_sigma ** 2))

                    # Age-based confidence: decay with age
                    age_confidence = np.exp(-obs.age / max(self.confidence_decay_tau, 1.0))

                    weights.append(spatial_weight * age_confidence)
                    values.append(obs.value)
                    age_confidences.append(age_confidence)

                weights = np.array(weights)
                values = np.array(values)
                age_confidences = np.array(age_confidences)

                # Normalize weights
                weight_sum = np.sum(weights)
                if weight_sum > 1e-6:
                    normalized_weights = weights / weight_sum
                    nowcast[ii, jj] = np.dot(normalized_weights, values)

                    # Confidence: measure of support from fresh, nearby observations
                    # Combine spatial weight and age decay
                    max_possible_weight = 1.0  # Fresh observation at zero distance
                    confidence[ii, jj] = np.clip(weight_sum / max_possible_weight, 0.0, 1.0)
                else:
                    nowcast[ii, jj] = 0.5
                    confidence[ii, jj] = 0.0

        return nowcast, confidence

    def publish_maps(self):
        """Publish nowcast field and confidence field."""
        nowcast, confidence = self.predict_field_and_confidence()

        # Publish predicted map (nowcast field)
        pred_msg = PredictedMap()
        pred_msg.height = self.height
        pred_msg.width = self.width
        pred_msg.data = nowcast.flatten().tolist()
        self.pred_pub.publish(pred_msg)

        # Publish confidence as guidance field
        conf_msg = GuidanceField()
        conf_msg.height = self.height
        conf_msg.width = self.width
        conf_msg.data = confidence.flatten().tolist()
        self.confidence_pub.publish(conf_msg)

        # Optionally publish occupancy grid (for external tools)
        if self.publish_occupancy_grid:
            self.publish_occupancy_grid_msg(nowcast, confidence)

        self.get_logger().debug(
            f'Published nowcast at step {self.current_step} | '
            f'Observations: {len(self.observations)} | Land cells: {np.sum(self.land_mask)}'
        )

    def publish_occupancy_grid_msg(self, nowcast, confidence):
        """Optionally publish OccupancyGrid for backward compatibility."""
        msg = OccupancyGrid()
        msg.header.stamp = self.get_clock().now().to_msg()
        msg.header.frame_id = 'world'

        msg.info.resolution = 1.0
        msg.info.width = self.width
        msg.info.height = self.height
        msg.info.origin.position.x = 0.0
        msg.info.origin.position.y = 0.0
        msg.info.origin.position.z = 0.0

        # Convert nowcast field to occupancy: use confidence to scale
        occupancy = np.zeros((self.height, self.width), dtype=np.int8)
        
        for ii in range(self.height):
            for jj in range(self.width):
                if self.land_mask[ii, jj]:
                    occupancy[ii, jj] = 100  # Land = occupied
                elif not np.isfinite(nowcast[ii, jj]):
                    occupancy[ii, jj] = -1  # Unknown
                else:
                    # Map cost [0, 1] to occupancy [0, 100] scaled by confidence
                    occ_val = int(nowcast[ii, jj] * 100.0 * confidence[ii, jj])
                    occupancy[ii, jj] = np.clip(occ_val, 0, 100)

        msg.data = occupancy.flatten().tolist()
        self.occ_grid_pub.publish(msg)


def main():
    rclpy.init()
    node = NowcastSLAM()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
