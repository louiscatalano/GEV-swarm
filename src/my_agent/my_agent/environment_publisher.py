# this node publishes a dynamic 2D environment state that changes over time

import rclpy
from rclpy.node import Node
import numpy as np
import random
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
        self.agent_starts = []
        self.land_value = np.nan
        self.forbidden = self.generate_land(self.size, self.size, goal=(32,32))
        for _ in range(6):
            self.agent_starts.append(self.sample_free_cell())

        # --- State ---
        self.step = 0
        self.base_field = self._initialize_field()
        self.field = self.base_field.copy()

        # --- Publisher ---
        self.publisher = self.create_publisher(
            EnvironmentState,
            '/environment_state',
            10
        )

        # --- Timer ---
        self.timer = self.create_timer(self.dt, self.update)

        self.get_logger().info('Environment publisher started')

    def sample_free_cell(self):
        """Sample a random free cell not in forbidden"""
        while True:
            i = random.randint(0, self.size - 1)
            j = random.randint(0, self.size - 1)
            if not self.forbidden[i, j]:
                return int(i), int(j)
                        
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

        msg = EnvironmentState()
        msg.step = self.step
        msg.width = self.size
        msg.height = self.size
        msg.data = self.field.flatten().tolist()

        self.publisher.publish(msg)

        self.get_logger().info(f'Published environment step {self.step}')
        self.step += 1
    
    def generate_land(self, height, width, goal=(32,32)):
        forbidden = np.zeros((height, width), dtype=bool)

        p_no_land = 0.5
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

            target_size = random.randint(
                min_body_size,
                max_land_cells - total_land
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
            return self.generate_land(height, width, goal)
        return forbidden
        

def main():
    rclpy.init()
    node = EnvironmentPublisher()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
    