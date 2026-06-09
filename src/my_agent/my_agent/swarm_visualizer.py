import rclpy
from rclpy.node import Node
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.lines import Line2D

from environment_msgs.msg import EnvironmentState, PredictedMap, GuidanceField
from geometry_msgs.msg import Point


class SwarmVisualizer(Node):

    def __init__(self):
        super().__init__('swarm_visualizer')

        self.agent_positions = {}
        self.agent_paths = {}
        self.predicted_map = None
        self.guidance_field = None

        self.declare_parameter('num_agents', 6)
        self.num_agents = self.get_parameter('num_agents').value
        self.agent_colors = self._build_agent_color_map(self.num_agents)

        # Depth 1: drop stale env frames — only render the latest.
        self.create_subscription(
            EnvironmentState,
            '/environment_state',
            self.env_callback,
            1
        )

        # Subscribe to SLAM node outputs
        self.create_subscription(
            PredictedMap,
            '/swarm/predicted_map',
            self.predicted_map_callback,
            1
        )
        self.create_subscription(
            GuidanceField,
            '/swarm/guidance',
            self.guidance_callback,
            1
        )

        num_agents = self.num_agents

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
        
        # Second figure for SLAM/AI node view
        self.fig_slam, self.ax_slam = plt.subplots()

    def predicted_map_callback(self, msg):
        self.predicted_map = np.array(msg.data).reshape(msg.height, msg.width)

    def guidance_callback(self, msg):
        self.guidance_field = np.array(msg.data).reshape(msg.height, msg.width)

    def _build_agent_color_map(self, num_agents):
        # Exclude blues and greens to avoid blending with viridis background
        colors = [
            '#e74c3c',  # red
            '#f39c12',  # orange
            '#f1c40f',  # yellow
            '#9b59b6',  # purple
            '#e91e63',  # pink
            '#8b4513',  # brown
            '#c0504d',  # dark red
            '#ffa500',  # orange
            '#da70d6',  # orchid
            '#ff69b4',  # hot pink
            '#800080',  # dark purple
            '#d2691e',  # chocolate
            '#ff6347',  # tomato
            '#daa520',  # goldenrod
            '#ba55d3',  # medium orchid
            '#dc143c',  # crimson
        ]
        return {
            aid: colors[aid % len(colors)]
            for aid in range(num_agents)
        }

    def _agent_color(self, agent_id):
        if agent_id not in self.agent_colors:
            colors = [
                '#e74c3c',  # red
                '#f39c12',  # orange
                '#f1c40f',  # yellow
                '#9b59b6',  # purple
                '#e91e63',  # pink
                '#8b4513',  # brown
                '#c0504d',  # dark red
                '#ffa500',  # orange
                '#da70d6',  # orchid
                '#ff69b4',  # hot pink
                '#800080',  # dark purple
                '#d2691e',  # chocolate
                '#ff6347',  # tomato
                '#daa520',  # goldenrod
                '#ba55d3',  # medium orchid
                '#dc143c',  # crimson
            ]
            self.agent_colors[agent_id] = colors[agent_id % len(colors)]
        return self.agent_colors[agent_id]

    def pose_callback(self, msg, agent_id):
        # agent_node publishes Point with x=row (i), y=column (j)
        pos = (int(msg.x), int(msg.y))
        self.agent_positions[agent_id] = pos
        self.agent_paths.setdefault(agent_id, []).append(pos)
        # Keep path history bounded for performance
        if len(self.agent_paths[agent_id]) > 200:
            self.agent_paths[agent_id].pop(0)

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

        for aid, path in self.agent_paths.items():
            if len(path) >= 2:
                xs = [pos[1] for pos in path]
                ys = [pos[0] for pos in path]
                color = self._agent_color(aid)
                self.ax.plot(xs, ys, color=color, linewidth=1.5, alpha=0.85, zorder=2)

        for aid, (i, j) in self.agent_positions.items():
            color = self._agent_color(aid)
            self.ax.scatter(j, i, c=[color], s=60, edgecolors='black', linewidths=0.5, zorder=3)
            self.ax.text(j + 0.5, i + 0.5, str(aid), color='white', fontsize=7, zorder=4)

        # Goal marker — j=32, i=32 → scatter(x=col, y=row)
        self.ax.scatter(32, 32, c='yellow', s=100, marker='*', zorder=5)

        legend_handles = [
            Line2D([0], [0], color=self._agent_color(aid), lw=2, marker='o', markersize=5, markerfacecolor=self._agent_color(aid), label=f'Agent {aid}')
            for aid in sorted(self.agent_positions.keys())
        ]
        if legend_handles:
            self.ax.legend(handles=legend_handles, loc='upper right', fontsize=6, framealpha=0.8)

        self.ax.set_xlim(-0.5, msg.width - 0.5)
        self.ax.set_ylim(-0.5, msg.height - 0.5)
        self.ax.set_aspect('equal')
        self.ax.set_title(f'GEV Swarm — {len(self.agent_positions)} agents')

        self.fig.canvas.draw()
        self.fig.canvas.flush_events()
        
        # Also render the SLAM view
        self.render_slam_view()

    def render_slam_view(self):
        """Render the predicted map and guidance field from the SLAM node."""
        if self.predicted_map is None or self.guidance_field is None:
            return
        
        self.ax_slam.clear()
        
        # Display predicted map
        im = self.ax_slam.imshow(self.predicted_map, origin='lower', cmap='plasma')
        
        # Overlay guidance field with alpha
        guidance_normalized = (self.guidance_field - self.guidance_field.min()) / (self.guidance_field.max() - self.guidance_field.min() + 1e-6)
        guidance_overlay = np.zeros((*self.guidance_field.shape, 4))
        guidance_overlay[..., 0] = guidance_normalized  # red channel for positive guidance
        guidance_overlay[..., 3] = 0.3 * np.abs(guidance_normalized)  # alpha based on magnitude
        self.ax_slam.imshow(guidance_overlay, origin='lower')
        
        self.ax_slam.set_title('SLAM Node View: Predicted Map + Guidance Field')
        self.ax_slam.set_aspect('equal')
        
        self.fig_slam.canvas.draw()
        self.fig_slam.canvas.flush_events()


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
