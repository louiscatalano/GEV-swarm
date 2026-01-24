# this node visualizes the swarm agents on a 2D environment grid
# each agent publishes its position, which are displayed on the environment map with historical path
# using matplotlib for visualization

import rclpy
from rclpy.node import Node
import numpy as np
import matplotlib.pyplot as plt

from environment_msgs.msg import EnvironmentState, AgentState

class SwarmVisualizer(Node):

    def __init__(self):
        super().__init__('swarm_visualizer')

        self.agent_positions = {}

        # Environment subscription
        self.create_subscription(
            EnvironmentState,
            '/environment_state',
            self.env_callback,
            10
        )

        # Get number of agents from parameter server
        self.declare_parameter('num_agents', 6)
        num_agents = self.get_parameter('num_agents').value

        # Agent subscriptions
        for k in range(num_agents):
            self.create_subscription(
            AgentState,
            f'/swarm/state',
            lambda msg, k=k: self.agent_callback(msg),
            10
            )

        plt.ion()
        self.fig, self.ax = plt.subplots()

    def agent_callback(self, msg):
        self.agent_positions[msg.agent_id] = (msg.i, msg.j)

    def env_callback(self, msg):
        field = np.array(msg.data).reshape(msg.height, msg.width)

        # --- Clear frame ---
        self.ax.clear()

        # --- Environment field ---
        land_mask = ~np.isfinite(field)
        viz_field = field.copy()
        viz_field[land_mask] = np.nan

        self.ax.imshow(
            viz_field,
            origin='lower',
            cmap='viridis'
        )

        # --- Land overlay ---
        land_overlay = np.zeros((*land_mask.shape, 4))
        land_overlay[land_mask] = [0.2, 0.2, 0.2, 1.0]
        self.ax.imshow(land_overlay, origin='lower')

        # --- Agents ---
        for aid, (i, j) in self.agent_positions.items():
            self.ax.scatter(j, i, c='red', s=40)
            self.ax.text(j + 0.5, i + 0.5, str(aid), color='white')

        # --- Goal ---
        self.ax.scatter(32, 32, c='yellow', s=100, marker='*')

        # --- Axis discipline (prevents teleport illusion) ---
        self.ax.set_xlim(0, msg.width)
        self.ax.set_ylim(0, msg.height)
        self.ax.set_aspect('equal')

        self.ax.set_title('GEV Swarm State')
        plt.pause(0.001)

def main():
    rclpy.init()
    node = SwarmVisualizer()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == '__main__':
    main()
