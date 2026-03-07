# this node subscribes to the environment state and moves the agent to the neighboring cell with the lowest neighboring value
# LOITER: move to lowest neighboring cell, TRANSIT: move to lowest neighboring cell in the direction of goal_i, goal_j 
# Collision, oscillation, and wraparound avoidance applies in both modes

import rclpy
from rclpy.node import Node
import numpy as np

from environment_msgs.msg import EnvironmentState, AgentState, LocalMapUpdate, PredictedMap, GuidanceField
from geometry_msgs.msg import Point

class AgentNode(Node):

    def __init__(self):
        super().__init__('agent_node')

        self.declare_parameter('agent_id', 0)
        self.declare_parameter('i0', 32)
        self.declare_parameter('j0', 32)

        self.agent_id = self.get_parameter('agent_id').value
        self.i = self.get_parameter('i0').value
        self.j = self.get_parameter('j0').value

        self.prev_i = None
        self.prev_j = None
        self.intent = None
        self.guidance = None

        # Subscription to environment state
        self.create_subscription(
            EnvironmentState,
            '/environment_state',
            self.environment_callback,
            10
        )

        # Publisher for agent pose
        self.pose_pub = self.create_publisher(
            Point,
            f'/agent_{self.agent_id}/pose',
            10
        )

        # Publisher for Agent state
        self.state_pub = self.create_publisher(
            AgentState,
            '/swarm/state',
            10
        )

        # Local map publisher
        self.local_map_pub = self.create_publisher(
            LocalMapUpdate,
            '/swarm/local_map_update',
            10
        )

        # Subscription to other agents' states for collision avoidance
        self.create_subscription(
            AgentState,
            '/swarm/state',
            self.agent_state_callback,
            10
        )

        # Subscription to local map updates from other agents
        self.create_subscription(
            LocalMapUpdate,
            '/swarm/local_map_update',
            self.local_map_callback,
            10
        )

        # Subscription to predicted map updates from other agents
        self.create_subscription(
            PredictedMap,
            '/swarm/predicted_map',
            self.predicted_map_callback,
            10
        )

        #Subcription to Guidance Field from swarm AI
        self.create_subscription(
            GuidanceField,
            '/swarm/guidance',
            self.guidance_callback,
            10
        )

        # Dictionary to hold other agents' positions
        self.other_agents = {}
        self.other_intents = {}
        self.shared_map = {}
        self.agent_timeout = 2.0  # seconds
        
        # Initial mode
        self.mode = "TRANSIT"
        self.goal_i = 32
        self.goal_j = 32

    # Callback for other agents' states
    def agent_state_callback(self, msg):
        if msg.agent_id == self.agent_id:
            return

        timestamp = self.get_clock().now()
        self.other_agents[msg.agent_id] = (msg.i, msg.j, timestamp)

        if msg.intent_i >= 0 and msg.intent_j >= 0:
            self.other_intents[msg.agent_id] = (msg.intent_i, msg.intent_j)

    def get_valid_agents(self):
        current_time = self.get_clock().now()
        valid_agents = {}
        for aid, (i, j, timestamp) in self.other_agents.items():
            if (current_time - timestamp).nanoseconds < self.agent_timeout * 1e9:
                valid_agents[aid] = (i, j)
        return valid_agents

    # Callback for local map updates from other agents
    def local_map_callback(self, msg):
        if msg.agent_id == self.agent_id:
            return
        
        self.shared_map[(msg.i, msg.j)] = msg.value
    
    # Callback for predicted map updates from other agents
    def predicted_map_callback(self, msg):
        self.predicted_field = np.array(msg.data).reshape(msg.height, msg.width)

    # Callback for Guidance Field from swarm AI
    def guidance_callback(self, msg):
        self.guidance = np.array(msg.data).reshape(msg.height, msg.width)

    # Callback for environment state updates
    def environment_callback(self, msg):
        field = np.array(msg.data).reshape(msg.height, msg.width)

        update = LocalMapUpdate()
        update.agent_id = self.agent_id
        update.i = self.i
        update.j = self.j
        update.value = float(field[self.i, self.j])
        self.local_map_pub.publish(update)
        self.intent = None
        best_val = field[self.i, self.j]
        best_pos = None
        neighbors = [(-1,0),(1,0),(0,-1),(0,1),(-1,-1),(-1,1),(1,-1),(1,1)]

        forbidden = set()
        forbidden.add((self.i, self.j))  # also avoid own current position

        for oid, (oi, oj) in self.get_valid_agents().items():
            for di, dj in [
                (-1,-1),(-1,0),(-1,1),
                (0,-1),(0,0),(0,1),
                (1,-1),(1,0),(1,1)
            ]:
                fi = oi + di
                fj = oj + dj
                forbidden.add((fi, fj))

        if self.mode == "LOITER":
            pass  # already defined neighbors
        elif self.mode == "TRANSIT" and self.goal_i is not None:
            di = int(np.sign(self.goal_i - self.i))
            dj = int(np.sign(self.goal_j - self.j))
            preferred = {(di,0),(0,dj),(di,dj)}
            neighbors = [m for m in neighbors if m in preferred] or neighbors

            # fallback if goal-aligned neighbors are blocked
            if di == 0 and dj == 0:
                neighbors = [(-1,0),(1,0),(0,-1),(0,1)]

        # Explore neighboring cells
        for di, dj in neighbors:
            ni = self.i + di
            nj = self.j + dj

            if ni < 0 or ni >= msg.height or nj < 0 or nj >= msg.width:
                continue

            # Prevent oscillation
            if self.prev_i is not None and (ni, nj) == (self.prev_i, self.prev_j):
                continue

            # Prevent collision           
            if (ni, nj) in forbidden:
                continue

            # --- cost components ---
            v_env = field[ni, nj]
            if not np.isfinite(v_env):
                continue  # skip non-navigable cells

            v_pred = 0.0
            if hasattr(self, 'predicted_field'):
                v_pred = 0.5 * self.predicted_field[ni, nj]

            v_guid = 0.0
            if self.guidance is not None:
                v_guid = self.guidance[ni, nj]

            # --- total cost ---
            v = v_env + v_pred + v_guid

            if v < best_val:
                best_val = v
                best_pos = (ni, nj)

        # --- FORCE MOVE FALLBACK ---
        if best_pos is None:
            for di, dj in [(-1,0),(1,0),(0,-1),(0,1),(-1,-1),(-1,1),(1,-1),(1,1)]:
                ni = self.i + di
                nj = self.j + dj

                if ni < 0 or ni >= msg.height or nj < 0 or nj >= msg.width:
                    continue

                # avoid collision only (hard safety)
                if (ni, nj) in forbidden:
                    continue

                best_pos = (ni, nj)
                break

        # Move to best position if found
        if best_pos is not None:
            self.intent = best_pos
            self.prev_i, self.prev_j = self.i, self.j
            self.i, self.j = best_pos

        # Goal arrival check
        if (
            self.mode == "TRANSIT" and self.goal_i is not None and
            self.i == self.goal_i and self.j == self.goal_j):
            self.get_logger().info(
                f'Agent {self.agent_id} reached goal ({self.goal_i},{self.goal_j}), switching to LOITER mode.'
            )
            self.mode = "LOITER"
            self.goal_i = None
            self.goal_j = None

        self.get_logger().info(
            f'Agent {self.agent_id} | pos=({self.i},{self.j}) | value={field[self.i, self.j]:.3f}'
        )

        p = Point()
        p.x = float(self.i)
        p.y = float(self.j)
        p.z = 0.0
        self.pose_pub.publish(p)

        state = AgentState()
        state.agent_id = self.agent_id
        state.i = self.i
        state.j = self.j
        if self.intent is not None:
            state.intent_i = self.intent[0]
            state.intent_j = self.intent[1]
        else:
            state.intent_i = -1
            state.intent_j = -1
        self.state_pub.publish(state)

def main():
    rclpy.init()
    node = AgentNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
