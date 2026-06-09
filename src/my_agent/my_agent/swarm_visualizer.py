import rclpy
from rclpy.node import Node
import numpy as np
import matplotlib.pyplot as plt

from environment_msgs.msg import EnvironmentState
from geometry_msgs.msg import Point


class SwarmVisualizer(Node):

    def __init__(self):
        super().__init__('swarm_visualizer')

        self.agent_positions = {}

        # Depth 1: drop stale env frames — only render the latest.
        self.create_subscription(
            EnvironmentState,
            '/environment_state',
            self.env_callback,
            1
        )

        self.declare_parameter('num_agents', 6)
        num_agents = self.get_parameter('num_agents').value

        # Subscribe to each agent's dedicated pose topic at depth 1.
        #
        # The old /swarm/state approach (one shared topic, depth 10) caused
        # apparent teleporting: all agents competed for the same 10-slot queue.
        # A slow matplotlib render let the queue fill with messages spanning
        # multiple time steps. When the executor drained them in order,
        # agent_positions briefly held positions from earlier in the simulation
        # before current messages arrived — the visualizer rendered that
        # intermediate state as a "jump back to initial position."
        #
        # Per-agent topics at depth 1 give each agent an independent queue.
        # Depth 1 drops any message that arrives before the previous one is
        # consumed, so agent_positions always holds the most recent known
        # position for every agent regardless of render latency.
        for k in range(num_agents):
            self.create_subscription(
                Point,
                f'/agent_{k}/pose',
                lambda msg, kid=k: self.pose_callback(msg, kid),
                1
            )

        plt.ion()
        self.fig, self.ax = plt.subplots()

    def pose_callback(self, msg, agent_id):
        # agent_node publishes Point with x=row (i), y=column (j)
        self.agent_positions[agent_id] = (int(msg.x), int(msg.y))

    def env_callback(self, msg):
        field = np.array(msg.data).reshape(msg.height, msg.width)

        self.ax.clear()

        land_mask = ~np.isfinite(field)
        viz_field = field.copy()
        viz_field[land_mask] = np.nan

        self.ax.imshow(viz_field, origin='lower', cmap='viridis')

        land_overlay = np.zeros((*land_mask.shape, 4))
        land_overlay[land_mask] = [0.2, 0.2, 0.2, 1.0]
        self.ax.imshow(land_overlay, origin='lower')

        for aid, (i, j) in self.agent_positions.items():
            self.ax.scatter(j, i, c='red', s=40, zorder=3)
            self.ax.text(j + 0.5, i + 0.5, str(aid), color='white', fontsize=7, zorder=4)

        # Goal marker — j=32, i=32 → scatter(x=col, y=row)
        self.ax.scatter(32, 32, c='yellow', s=100, marker='*', zorder=5)

        self.ax.set_xlim(-0.5, msg.width - 0.5)
        self.ax.set_ylim(-0.5, msg.height - 0.5)
        self.ax.set_aspect('equal')
        self.ax.set_title(f'GEV Swarm — {len(self.agent_positions)} agents')

        self.fig.canvas.draw()
        self.fig.canvas.flush_events()


def main():
    rclpy.init()
    node = SwarmVisualizer()
    try:
        while rclpy.ok():
            rclpy.spin_once(node, timeout_sec=0.05)
            plt.pause(0.001)
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
