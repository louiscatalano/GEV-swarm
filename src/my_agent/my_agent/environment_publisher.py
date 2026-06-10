import rclpy
from rclpy.node import Node
import numpy as np
import random
import csv
import os
from datetime import datetime
from collections import deque

from environment_msgs.msg import EnvironmentState


class EnvironmentPublisher(Node):

    def __init__(self):
        super().__init__('environment_publisher')

        # --- Parameters ---
        self.size = 64
        self.dt = 0.5  # seconds
        self.vx = 0.2  # grid cells per step (x)
        self.vy = 0.1  # grid cells per step (y)
        self.land_value = np.nan
        self.declare_parameter('goal_i', 32)
        self.declare_parameter('goal_j', 32)
        self.declare_parameter('seed', -1)
        self.declare_parameter('launch_id', 'default')
        self.declare_parameter('slam_enabled', True)
        self.declare_parameter('num_agents', 3)
        self.goal_i = self.get_parameter('goal_i').value
        self.goal_j = self.get_parameter('goal_j').value
        self.seed = self.get_parameter('seed').value
        self.launch_id = self.get_parameter('launch_id').value
        self.slam_enabled = self.get_parameter('slam_enabled').value
        self.num_agents = self.get_parameter('num_agents').value
        if self.seed != -1:
            random.seed(self.seed)
            np.random.seed(self.seed)
        self.forbidden = self.generate_land(self.size, self.size, goal=(self.goal_i, self.goal_j))

        # --- State ---
        self.step = 0
        self.base_field = self._initialize_field()
        self.field = self.base_field.copy()
        self.field[self.forbidden] = self.land_value

        # --- Publisher ---
        self.publisher = self.create_publisher(
            EnvironmentState,
            '/environment_state',
            10
        )

        # --- Timer ---
        self.timer = self.create_timer(self.dt, self.update)
        
        # --- Write launch metadata ---
        self.write_launch_metadata()

        self.get_logger().info('Environment publisher started')

    def write_launch_metadata(self):
        """Write launch-level metadata to CSV"""
        log_dir = os.path.expanduser('~/.ros/swarm_logs')
        os.makedirs(log_dir, exist_ok=True)
        
        # Calculate land coverage as fraction of forbidden cells
        land_coverage = np.sum(self.forbidden) / (self.size * self.size)
        
        # Use same filename pattern as agent logs
        timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
        metadata_filename = os.path.join(log_dir, f'launch_{self.launch_id}_{timestamp}_metadata.csv')
        
        # Write metadata (single row per launch)
        with open(metadata_filename, 'w', newline='') as f:
            writer = csv.writer(f)
            writer.writerow([
                'launch_id', 'timestamp', 'seed', 'goal_i', 'goal_j',
                'num_agents', 'land_coverage', 'slam_enabled'
            ])
            writer.writerow([
                self.launch_id,
                timestamp,
                self.seed,
                self.goal_i,
                self.goal_j,
                self.num_agents,
                land_coverage,
                self.slam_enabled
            ])
        
        self.get_logger().info(
            f'Launch metadata written to {metadata_filename}: '
            f'seed={self.seed}, goal=({self.goal_i},{self.goal_j}), '
            f'agents={self.num_agents}, land={land_coverage:.3f}, slam={self.slam_enabled}'
        )
    
    def _initialize_field(self):
        """Initial smooth random field"""
        field = np.random.rand(self.size, self.size)
        field = self._smooth(field)
        return field

    def _smooth(self, field):
        """Cheap spatial correlation"""
        return (
            field +
            np.roll(field, 1, axis=0) +
            np.roll(field, -1, axis=0) +
            np.roll(field, 1, axis=1) +
            np.roll(field, -1, axis=1)
        ) / 5.0

    def _advect(self, field):
        """Shift field with wraparound"""
        dx = int(np.round(self.vx))
        dy = int(np.round(self.vy))
        field = np.roll(field, dx, axis=1)
        field = np.roll(field, dy, axis=0)
        field += 0.01 * np.random.randn(*field.shape)  # small noise
        return self._smooth(field)

    def update(self):
        self.base_field = self._advect(self.base_field)
        self.field = self.base_field.copy()
        self.field[self.forbidden] = self.land_value
        
        # Absolute guarantee: goal cell is NEVER land, even if accidentally marked
        self.field[self.goal_i, self.goal_j] = self.base_field[self.goal_i, self.goal_j]
        self.forbidden[self.goal_i, self.goal_j] = False

        msg = EnvironmentState()
        msg.step = self.step
        msg.width = self.size
        msg.height = self.size
        msg.data = self.field.flatten().tolist()

        self.publisher.publish(msg)

        self.get_logger().info(f'Published environment step {self.step}')
        self.step += 1
    
    def generate_land(self, height, width, goal=(32,32), max_retries=10):
        forbidden = np.zeros((height, width), dtype=bool)

        p_no_land = 0.05
        max_coverage = 0.3
        min_body_frac = 0.05
        max_bodies = 2

        if random.random() < p_no_land:
            return forbidden  # no land
        
        max_land_cells = int(max_coverage * height * width)
        min_body_size = int(min_body_frac * height * width)

        total_land = 0
        n_bodies = random.randint(0, max_bodies)

        for _ in range(n_bodies):
            if total_land >= max_land_cells:
                break

            for _ in range(100):  # try 100 times to place a body
                si = random.randint(0, height - 1)
                sj = random.randint(0, width - 1)   

                if (si, sj) == goal:
                    continue
                if forbidden[si, sj]:
                    continue
                break
            else:
                continue  # failed to place body

            remaining_land = max_land_cells - total_land
            if remaining_land < min_body_size:
                break

            target_size = random.randint(
                min_body_size,
                remaining_land
            )

            queue = deque()
            queue.append((si, sj))
            forbidden[si, sj] = True
            grown = 1

            while queue and grown < target_size:
                ci, cj = queue.popleft()
                for di, dj in [(-1,0),(1,0),(0,-1),(0,1)]:
                    ni, nj = ci + di, cj + dj

                    if ni < 0 or ni >= height or nj < 0 or nj >= width:
                        continue
                    if forbidden[ni, nj]:
                        continue
                    if (ni, nj) == goal:
                        continue
                    if random.random() < 0.7:  # growth probability
                        forbidden[ni, nj] = True
                        queue.append((ni, nj))
                        grown += 1
                        if grown >= target_size:
                            break
            total_land += grown

        gi, gj = goal
        if forbidden[gi, gj]:
            if max_retries > 0:
                return self.generate_land(height, width, goal, max_retries - 1)
            else:
                self.get_logger().warn('Failed to generate land without blocking goal after retries')
                return np.zeros((height, width), dtype=bool)  # fallback to no land

        forbidden = self._fill_lakes(forbidden, height, width)

        # Absolute guarantee: goal is never forbidden
        forbidden[gi, gj] = False
        return forbidden

    def _fill_lakes(self, forbidden, height, width):
        """Convert enclosed water cells (lakes) to land by flood-filling from the border."""
        reachable = np.zeros((height, width), dtype=bool)
        queue = deque()

        for i in range(height):
            for j in (0, width - 1):
                if not forbidden[i, j] and not reachable[i, j]:
                    reachable[i, j] = True
                    queue.append((i, j))
        for j in range(width):
            for i in (0, height - 1):
                if not forbidden[i, j] and not reachable[i, j]:
                    reachable[i, j] = True
                    queue.append((i, j))

        while queue:
            ci, cj = queue.popleft()
            for di, dj in ((-1, 0), (1, 0), (0, -1), (0, 1)):
                ni, nj = ci + di, cj + dj
                if 0 <= ni < height and 0 <= nj < width and not forbidden[ni, nj] and not reachable[ni, nj]:
                    reachable[ni, nj] = True
                    queue.append((ni, nj))

        # Water cells that are not reachable from the border are lakes → fill as land
        forbidden[~reachable] = True
        return forbidden
    
    def get_land_coverage(self):
        """Return fraction of map that is land"""
        return np.sum(self.forbidden) / (self.size * self.size)
        

def main():
    rclpy.init()
    node = EnvironmentPublisher()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
    