# CLI for swarm commands

import rclpy
from rclpy.node import Node
from environment_msgs.msg import SwarmCommand

class SwarmCommandPublisher(Node):

    def __init__(self):
        super().__init__('swarm_command_publisher')
        self.publisher_ = self.create_publisher(SwarmCommand, '/swarm/command', 10)

    def publish_command(self, mode, goal_i=0, goal_j=0):
        msg = SwarmCommand()
        msg.mode = mode
        msg.goal_i = goal_i
        msg.goal_j = goal_j
        self.publisher_.publish(msg)
        self.get_logger().info(f'Published {mode}')

def cli_loop(node):
    while rclpy.ok():
        cmd = input("Enter command (loiter | transit i j): ").strip()
        if cmd == "loiter":
            node.publish_command("LOITER")
        elif cmd.startswith("transit"):
            _, i, j = cmd.split()
            node.publish_command("TRANSIT", int(i), int(j))

def main():
    rclpy.init()
    node = SwarmCommandPublisher()

    import threading
    threading.Thread(target=cli_loop, args=(node,), daemon=True).start()

    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == '__main__':
    main()
