import rclpy
from rclpy.node import Node
import numpy as np
from scipy.ndimage import gaussian_filter

from environment_msgs.msg import LocalMapUpdate, PredictedMap, GuidanceField
from nav_msgs.msg import OccupancyGrid

class EnhancedSLAM(Node):

    def __init__(self):
        super().__init__('enhanced_slam')

        self.declare_parameter('height', 64)
        self.declare_parameter('width', 64)

        self.height = self.get_parameter('height').value
        self.width = self.get_parameter('width').value

        # Occupancy grid in log-odds space
        # log-odds = log(p / (1-p))
        # Allows for efficient Bayesian updates
        self.log_odds = np.zeros((self.height, self.width))
        
        # Prior belief (0 = 50% occupied)
        self.l0 = 0.0
        
        # Sensor model parameters (log-odds)
        self.l_occ = np.log(0.9 / 0.1)   # Observed occupied
        self.l_free = np.log(0.1 / 0.9)  # Observed free
        
        # Observation tracking
        self.observation_count = np.zeros((self.height, self.width))
        self.last_observed = np.full((self.height, self.width), -1.0)
        
        # Subscribe to local observations
        self.create_subscription(
            LocalMapUpdate,
            '/swarm/local_map_update',
            self.observation_callback,
            10
        )
        
        # Publishers
        self.map_pub = self.create_publisher(
            OccupancyGrid,
            '/swarm/occupancy_grid',
            10
        )
        
        self.pred_pub = self.create_publisher(
            PredictedMap,
            '/swarm/predicted_map',
            10
        )
        
        self.guidance_pub = self.create_publisher(
            GuidanceField,
            '/swarm/guidance',
            10
        )
        
        # Periodic publishing
        self.create_timer(1.0, self.publish_maps)
        
        self.get_logger().info('Enhanced SLAM node started with Bayesian occupancy grids')

    def observation_callback(self, msg):
        i, j = msg.i, msg.j
        value = msg.value
        
        # Determine observation type
        if not np.isfinite(value):
            # NaN = obstacle/land (high confidence occupied)
            delta_log_odds = self.l_occ
        else:
            # Use cost value to infer occupancy
            if value < 0.2:
                # Very low cost = definitely free
                delta_log_odds = self.l_free
            elif value > 0.8:
                # Very high cost = likely occupied
                delta_log_odds = self.l_occ * 0.7
            elif value > 0.5:
                # Medium-high cost = somewhat occupied
                delta_log_odds = self.l_occ * 0.3
            else:
                # Medium cost = slightly occupied
                delta_log_odds = self.l_occ * 0.1
        
        # Bayesian update in log-odds space
        self.log_odds[i, j] += delta_log_odds
        
        # Clamp to prevent numerical overflow
        self.log_odds[i, j] = np.clip(self.log_odds[i, j], -10, 10)
        
        # Track observations
        self.observation_count[i, j] += 1
        self.last_observed[i, j] = self.get_clock().now().nanoseconds / 1e9

    def get_probability(self):
        return 1.0 / (1.0 + np.exp(-self.log_odds))

    def get_entropy(self):
        p_safe = np.clip(self.get_probability(), 1e-10, 1 - 1e-10)
        return -(p_safe * np.log(p_safe) + (1 - p_safe) * np.log(1 - p_safe))

    def interpolate_unknown_regions(self):
        observed_mask = self.observation_count > 0
        
        if np.sum(observed_mask) < 10:
            # Not enough data for interpolation
            return self.get_probability()
        
        # Get probability map
        prob = self.get_probability()
        
        # Create a version with unknown cells set to 0.5 (uncertain)
        prob_filled = prob.copy()
        prob_filled[~observed_mask] = 0.5
        
        # Apply Gaussian smoothing
        # Sigma controls how far the influence spreads
        sigma = 2.0
        smoothed = gaussian_filter(prob_filled, sigma=sigma)
        
        # Blend: keep observed values, use smoothed for unknown
        result = np.where(observed_mask, prob, smoothed)
        
        return result

    def predict_field(self):
        prob = self.interpolate_unknown_regions()
        max_entropy = -0.5 * np.log(0.5) * 2
        uncertainty = self.get_entropy() / max_entropy
        return 0.7 * prob + 0.3 * uncertainty

    def publish_maps(self):
        self.publish_occupancy_grid()
        self.publish_predicted_map()
        self.publish_guidance()

    def publish_occupancy_grid(self):
        msg = OccupancyGrid()
        msg.header.stamp = self.get_clock().now().to_msg()
        msg.header.frame_id = 'world'
        
        # Map metadata
        msg.info.resolution = 1.0  # 1 grid cell = 1 unit
        msg.info.width = self.width
        msg.info.height = self.height
        msg.info.origin.position.x = 0.0
        msg.info.origin.position.y = 0.0
        msg.info.origin.position.z = 0.0
        
        # Convert probability to occupancy [0-100]
        prob = self.get_probability()
        occupancy = (prob * 100).astype(np.int8)
        
        # Mark unobserved cells as unknown (-1)
        occupancy[self.observation_count == 0] = -1
        
        msg.data = occupancy.flatten().tolist()
        
        self.map_pub.publish(msg)

    def publish_predicted_map(self):
        predicted = self.predict_field()
        
        msg = PredictedMap()
        msg.height = self.height
        msg.width = self.width
        msg.data = predicted.flatten().tolist()
        
        self.pred_pub.publish(msg)

    def publish_guidance(self):
        max_entropy = -0.5 * np.log(0.5) * 2
        uncertainty = self.get_entropy() / max_entropy
        
        # Guidance: negative cost for high uncertainty (encourage exploration)
        # Only for cells that haven't been observed recently
        current_time = self.get_clock().now().nanoseconds / 1e9
        time_since_observation = current_time - self.last_observed
        
        # Cells not observed for >10 seconds get exploration bonus
        exploration_mask = (time_since_observation > 10.0) | (self.observation_count == 0)
        
        guidance = np.zeros((self.height, self.width))
        guidance[exploration_mask] = -0.3 * uncertainty[exploration_mask]
        
        msg = GuidanceField()
        msg.width = self.width
        msg.height = self.height
        msg.data = guidance.flatten().tolist()
        
        self.guidance_pub.publish(msg)


def main():
    rclpy.init()
    node = EnhancedSLAM()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
    