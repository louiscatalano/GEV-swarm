import rclpy
from rclpy.node import Node

class AgentNode(Node):
    def __init__(self):
        super().__init__('agent_node')

        self.timer_period = 0.5 
        self.timer = self.create_timer(self.timer_period, self.step)

        self.get_logger().info("Agent node started")

    def step(self):
        self.get_logger().info("step")

def main():
    rclpy.init()
    node = AgentNode()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()
