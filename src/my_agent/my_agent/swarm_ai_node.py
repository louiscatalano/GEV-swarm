import rclpy
from rclpy.node import Node
import numpy as np

from environment_msgs.msg import LocalMapUpdate, PredictedMap, GuidanceField

class SwarmAINode(Node):

    def __init__(self):
        super().__init__('swarm_ai_node')

        self.declare_parameter('height', 64)
        self.declare_parameter('width', 64)

        self.height = self.get_parameter('height').value
        self.width = self.get_parameter('width').value

        # Internal memory
        self.known_map = np.full((self.height, self.width), np.nan)

        # Subscriptions
        self.create_subscription(
            LocalMapUpdate,
            '/swarm/local_map_update',
            self.local_map_callback,
            10
        )

        self.guidance_pub = self.create_publisher(
            GuidanceField,
            '/swarm/guidance',
            10
        )

        # Publishers
        self.pred_pub = self.create_publisher(
            PredictedMap,
            '/swarm/predicted_map',
            10
        )

        self.get_logger().info('Swarm AI node started (no learning yet).')

    def local_map_callback(self, msg):
        self.known_map[msg.i, msg.j] = msg.value
        self.publish_prediction()

    def publish_prediction(self):
        # For now: zero-fill unknowns (baseline)
        predicted = np.nan_to_num(self.known_map, nan=0.0)

        msg = PredictedMap()
        msg.height = self.height
        msg.width = self.width
        msg.data = predicted.flatten().tolist()

        self.pred_pub.publish(msg)
        self.publish_guidance()

    def publish_guidance(self):
        msg = GuidanceField()
        msg.width = self.predicted_map.width
        msg.height = self.predicted_map.height

        # Phase 1: direct passthrough
        msg.data = self.predicted_map.to_flat_list()

        self.guidance_pub.publish(msg)

def main():
    rclpy.init()
    node = SwarmAINode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
