import rclpy
from rclpy.node import Node
import numpy as np
import csv
from datetime import datetime
import os

from environment_msgs.msg import EnvironmentState, AgentState, LocalMapUpdate, PredictedMap, GuidanceField
from geometry_msgs.msg import Point
from my_agent.path_planner import DStarLite, PotentialField
from my_agent.orca import ORCAAvoidance, orca_grid_move


class AgentNode(Node):

    def __init__(self):
        super().__init__('agent_node')

        self.declare_parameter('agent_id', 0)
        self.declare_parameter('i0', 32)
        self.declare_parameter('j0', 32)
        self.declare_parameter('goal_i', 32)
        self.declare_parameter('goal_j', 32)
        self.declare_parameter('planner_type', 'dstar')  # 'dstar' or 'potential'

        self.agent_id = self.get_parameter('agent_id').value
        self.i = self.get_parameter('i0').value
        self.j = self.get_parameter('j0').value
        self.needs_free_cell = True
        self.goal_i = self.get_parameter('goal_i').value
        self.goal_j = self.get_parameter('goal_j').value
        self.planner_type = self.get_parameter('planner_type').value
        self.orca = ORCAAvoidance(time_horizon=1.5, agent_radius=0.5)
        self.position_snapshot = {}
        self.held_last_step = False

        self.intent = None
        self.guidance = None

        self.global_path = []
        self.replan_counter = 0
        self.replan_interval = 20

        self.planner = None
        self.planner_initialized = False
        self.planner_goal = None
        self.planner_first_init = False

        self.create_subscription(EnvironmentState, '/environment_state', self.environment_callback, 10)

        self.pose_pub = self.create_publisher(Point, f'/agent_{self.agent_id}/pose', 10)
        self.state_pub = self.create_publisher(AgentState, '/swarm/state', 10)
        self.local_map_pub = self.create_publisher(LocalMapUpdate, '/swarm/local_map_update', 10)

        self.create_subscription(AgentState, '/swarm/state', self.agent_state_callback, 10)
        self.create_subscription(PredictedMap, '/swarm/predicted_map', self.predicted_map_callback, 10)
        self.create_subscription(GuidanceField, '/swarm/guidance', self.guidance_callback, 10)

        self.other_agents = {}
        self.other_intents = {}
        self.agent_timeout = 2.0

        self.csv_file = None
        self.csv_writer = None
        self.step_counter = 0
        self.setup_logging()

        self.get_logger().info(
            f'Agent {self.agent_id} initialized | Planner: {self.planner_type} | Goal: ({self.goal_i},{self.goal_j})'
        )

    def setup_logging(self):
        log_dir = os.path.expanduser('~/.ros/swarm_logs')
        os.makedirs(log_dir, exist_ok=True)
        timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
        filename = os.path.join(log_dir, f'agent_{self.agent_id}_log_{timestamp}.csv')
        self.csv_file = open(filename, 'w', newline='')
        self.csv_writer = csv.writer(self.csv_file)
        self.csv_writer.writerow(['step', 'i', 'j', 'cost', 'goal_i', 'goal_j', 'path_len', 'replanned', 'num_neighbors'])
        self.csv_file.flush()

    def agent_state_callback(self, msg):
        if msg.agent_id == self.agent_id:
            return
        self.other_agents[msg.agent_id] = (msg.i, msg.j, self.get_clock().now())
        if msg.intent_i >= 0 and msg.intent_j >= 0:
            self.other_intents[msg.agent_id] = (msg.intent_i, msg.intent_j)

    def get_valid_agents(self):
        now = self.get_clock().now()
        return {
            aid: (i, j)
            for aid, (i, j, ts) in self.other_agents.items()
            if (now - ts).nanoseconds < self.agent_timeout * 1e9
        }

    def predicted_map_callback(self, msg):
        self.predicted_field = np.array(msg.data).reshape(msg.height, msg.width)

    def guidance_callback(self, msg):
        self.guidance = np.array(msg.data).reshape(msg.height, msg.width)

    def build_costmap(self, field):
        costmap = field.copy()
        finite = np.isfinite(costmap)

        if hasattr(self, 'predicted_field'):
            costmap[finite] += 0.5 * self.predicted_field[finite]

        if self.guidance is not None:
            costmap[finite] += self.guidance[finite]

        # D* Lite requires non-negative edge costs. The guidance field can push
        # finite cells below zero, causing extract_path to find zero-cost cycles.
        costmap[finite] = np.maximum(costmap[finite], 1e-3)

        return costmap

    def should_replan(self, costmap):
        if (self.i, self.j) == (self.goal_i, self.goal_j):
            return False

        if not self.global_path:
            return True

        # Emergency replan: the front of the path became land.
        ni, nj = self.global_path[0]
        if not np.isfinite(costmap[ni, nj]):
            return True

        # Periodic replan to adapt to gradual environment drift.
        # The old environment-change threshold fired every 1-2 steps because
        # the SLAM guidance field updates every second and shifts hundreds of
        # costmap cells by >0.1 simultaneously — well above the threshold of 10.
        # That caused a direction change every other step (hopping). Periodic
        # replanning every N steps lets the agent follow a stable path while
        # still adapting to slow drift.
        self.replan_counter += 1
        if self.replan_counter >= self.replan_interval:
            self.replan_counter = 0
            return True

        return False

    def get_next_waypoint(self):
        if not self.global_path:
            return None

        while self.global_path and self.global_path[0] == (self.i, self.j):
            self.global_path.pop(0)

        # Return the path head regardless of distance. ORCA can move the agent
        # diagonally opposite to the intended direction in one step (e.g., path
        # says +i,+j but ORCA goes +i,-j), putting the path head 2 cells away
        # in one axis. The strict <=1 adjacency check cleared the path in that
        # case, triggering an immediate replan into a SLAM-updated costmap and
        # producing a direction change every other step (hopping). The direction
        # computation sign(head - current) always produces a valid 1-cell step
        # toward the head regardless of how far away it is, so no clearing needed.
        return self.global_path[0] if self.global_path else None

    def is_collision_risk(self, pos, costmap, msg):
        """Check if moving to pos risks collision with neighbors in next step."""
        ni, nj = pos
        neighbors = self.get_valid_agents()
        
        if not neighbors:
            return False
        
        # Check distance to all neighbors
        for oid, (oi, oj) in neighbors.items():
            dist = max(abs(ni - oi), abs(nj - oj))  # Chebyshev distance
            
            # If neighbor is adjacent or overlapping, collision risk
            if dist <= 1:
                # Try to predict if neighbor is moving toward us
                if oid in self.position_snapshot:
                    prev_oi, prev_oj = self.position_snapshot[oid]
                    neighbor_vel = (float(oi - prev_oi), float(oj - prev_oj))
                    
                    # Check if neighbor velocity points toward our next position
                    # If neighbor moves closer to our intended position, it's risky
                    next_oi, next_oj = oi + neighbor_vel[0], oj + neighbor_vel[1]
                    next_dist = max(abs(ni - next_oi), abs(nj - next_oj))
                    
                    # If neighbor will be at our position or closer, avoid
                    if next_dist <= 1 or (oi, oj) == pos:
                        return True
                else:
                    # Unknown velocity, be conservative
                    return True
        
        return False

    def forced_move(self, costmap, msg):
        # Ignores intent reservation so a one-step hold never persists beyond a single step.
        occupied = set(self.get_valid_agents().values())
        best_cost = float('inf')
        best = None
        for di in [-1, 0, 1]:
            for dj in [-1, 0, 1]:
                if di == 0 and dj == 0:
                    continue
                ni, nj = self.i + di, self.j + dj
                if 0 <= ni < msg.height and 0 <= nj < msg.width:
                    if np.isfinite(costmap[ni, nj]) and (ni, nj) not in occupied:
                        # Avoid collision-risk moves even in forced_move
                        if not self.is_collision_risk((ni, nj), costmap, msg):
                            if costmap[ni, nj] < best_cost:
                                best_cost = costmap[ni, nj]
                                best = (ni, nj)
        return best

    def navigate_with_orca(self, waypoint, costmap, msg):
        neighbors = self.get_valid_agents()
        live_agents = neighbors
        
        # Check for imminent collisions (neighbors very close)
        imminent_collision = any(
            max(abs(i - self.i), abs(j - self.j)) <= 1 
            for _, (i, j) in neighbors.items()
        )
        
        # If imminent collision, avoid moving toward the collision source
        if imminent_collision:
            self.get_logger().warn(f'Agent {self.agent_id} COLLISION AVOIDANCE: {len(neighbors)} neighbors within 1 cell')
            # Find safest direction (away from neighbors)
            best_dist = -1
            best_dir = (0.0, 0.0)
            for di in [-1, 0, 1]:
                for dj in [-1, 0, 1]:
                    if di == 0 and dj == 0:
                        continue
                    ni, nj = self.i + di, self.j + dj
                    if 0 <= ni < msg.height and 0 <= nj < msg.width:
                        if np.isfinite(costmap[ni, nj]):
                            # Compute minimum distance to any neighbor
                            min_dist_to_neighbor = min(
                                max(abs(ni - oi), abs(nj - oj))
                                for _, (oi, oj) in neighbors.items()
                            ) if neighbors else float('inf')
                            
                            if min_dist_to_neighbor > best_dist:
                                best_dist = min_dist_to_neighbor
                                best_dir = (float(di), float(dj))
            
            # Use safety direction if found
            if best_dir != (0.0, 0.0):
                desired_dir = best_dir
            else:
                # Hold in place if no safe moves
                return (self.i, self.j)
        else:
            # Normal navigation: use waypoint or greedy best cell
            if waypoint:
                desired_dir = (float(np.sign(waypoint[0] - self.i)), float(np.sign(waypoint[1] - self.j)))
            else:
                best_cost = float('inf')
                best_dir = (0.0, 0.0)
                for di in [-1, 0, 1]:
                    for dj in [-1, 0, 1]:
                        if di == 0 and dj == 0:
                            continue
                        ni, nj = self.i + di, self.j + dj
                        if 0 <= ni < msg.height and 0 <= nj < msg.width:
                            cost = costmap[ni, nj]
                            if np.isfinite(cost) and cost < best_cost:
                                best_cost = cost
                                best_dir = (float(di), float(dj))
                desired_dir = best_dir
        
        neighbor_vels = {
            oid: (
                (float(oi - self.position_snapshot[oid][0]), float(oj - self.position_snapshot[oid][1]))
                if oid in self.position_snapshot else (0.0, 0.0)
            )
            for oid, (oi, oj) in neighbors.items()
        }

        next_pos = orca_grid_move(
            (self.i, self.j), desired_dir, neighbors, neighbor_vels,
            msg.height, msg.width, self.orca
        )

        ni, nj = next_pos
        if not np.isfinite(costmap[ni, nj]):
            return None

        # Check for collision risk before committing to move
        if self.is_collision_risk((ni, nj), costmap, msg):
            self.get_logger().warn(f'Agent {self.agent_id} COLLISION RISK at ({ni},{nj}): avoiding move')
            # If collision risk, try to find safer alternative
            for di, dj in [(-1,0),(1,0),(0,-1),(0,1),(-1,-1),(-1,1),(1,-1),(1,1)]:
                alt_i, alt_j = self.i + di, self.j + dj
                if 0 <= alt_i < msg.height and 0 <= alt_j < msg.width:
                    if np.isfinite(costmap[alt_i, alt_j]) and not self.is_collision_risk((alt_i, alt_j), costmap, msg):
                        return (alt_i, alt_j)
            # No safe alternative, hold in place
            return (self.i, self.j)

        # Safety fallback: if ORCA's cell is claimed by another agent's intent,
        # find an uncontested neighbor. Only live agents' intents count — stale
        # entries in other_intents would block cells indefinitely otherwise.
        for oid, intent_pos in self.other_intents.items():
            if oid not in live_agents:
                continue
            if oid != self.agent_id and intent_pos == (ni, nj):
                for di, dj in [(-1,0),(1,0),(0,-1),(0,1),(-1,-1),(-1,1),(1,-1),(1,1)]:
                    alt_i, alt_j = self.i + di, self.j + dj
                    if 0 <= alt_i < msg.height and 0 <= alt_j < msg.width:
                        if np.isfinite(costmap[alt_i, alt_j]) and not self.is_collision_risk((alt_i, alt_j), costmap, msg):
                            contested = any(
                                intent == (alt_i, alt_j)
                                for other_id, intent in self.other_intents.items()
                                if other_id != self.agent_id and other_id in live_agents
                            )
                            if not contested:
                                return (alt_i, alt_j)
                return (self.i, self.j)

        return next_pos

    def environment_callback(self, msg):
        field = np.array(msg.data).reshape(msg.height, msg.width)

        # Snapshot is set at the END of each callback (see bottom of this method).
        # other_agents is updated by agent_state_callbacks that fire BETWEEN env
        # callbacks, so snapshot[t-1] vs get_valid_agents()[t] gives real velocity.

        if self.needs_free_cell:
            if not np.isfinite(field[self.i, self.j]):
                for di, dj in [(-1,0),(1,0),(0,-1),(0,1),(-1,-1),(1,1),(-1,1),(1,-1)]:
                    ni, nj = self.i + di, self.j + dj
                    if 0 <= ni < msg.height and 0 <= nj < msg.width and np.isfinite(field[ni, nj]):
                        self.i, self.j = ni, nj
                        break
            self.needs_free_cell = False

        if not self.planner_initialized:
            self.planner = DStarLite(msg.height, msg.width) if self.planner_type == 'dstar' else PotentialField()
            self.planner_initialized = True

        update = LocalMapUpdate()
        update.agent_id = self.agent_id
        update.i = self.i
        update.j = self.j
        update.value = float(field[self.i, self.j])
        self.local_map_pub.publish(update)

        costmap = self.build_costmap(field)
        self.intent = None

        # At the goal, should_replan returns False so we skip D* Lite;
        # get_next_waypoint returns None and greedy navigation moves the agent
        # one cell — GEVs cannot stop, so we keep moving at the goal.
        if self.should_replan(costmap):
            goal = (self.goal_i, self.goal_j)
            if not self.planner_first_init or goal != self.planner_goal:
                self.global_path = self.planner.plan((self.i, self.j), goal, costmap)
                self.planner_goal = goal
                self.planner_first_init = True
            else:
                self.global_path = self.planner.replan((self.i, self.j), costmap)
            if self.global_path:
                self.global_path = self.validate_path(self.global_path, costmap)

        waypoint = self.get_next_waypoint()
        best_pos = self.navigate_with_orca(waypoint, costmap, msg)

        # Enforce move-every-step: if the agent was held last step (collision
        # avoidance), bypass intent reservation this step and force a move to
        # any passable, unoccupied neighbor. The agent may only hold for one
        # consecutive step; it must move on the step that follows.
        held = best_pos is None or best_pos == (self.i, self.j)
        if held and self.held_last_step:
            alt = self.forced_move(costmap, msg)
            if alt is not None:
                best_pos = alt
                held = False
        self.held_last_step = held

        if best_pos is not None and best_pos != (self.i, self.j):
            self.intent = best_pos
            self.i, self.j = best_pos
        elif best_pos is None:
            self.get_logger().warn(f'Agent {self.agent_id} has no valid moves from ({self.i},{self.j})')

        if self.i == self.goal_i and self.j == self.goal_j:
            self.get_logger().info(f'Agent {self.agent_id} at goal ({self.goal_i},{self.goal_j})')

        self.get_logger().info(f'Agent {self.agent_id} | pos=({self.i},{self.j}) | neighbors={len(self.get_valid_agents())} | held={self.held_last_step}')

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

        # Save snapshot AFTER publishing so next callback can compute velocity
        # as delta(other_agents_now - snapshot_prev). Saving at the start gives
        # velocity = 0 and blind ORCA collision geometry.
        self.position_snapshot = {aid: (i, j) for aid, (i, j, _) in self.other_agents.items()}

        self.log_metrics(field)

    def validate_path(self, path, costmap):
        if not path:
            return None
        valid_path = []
        for pos in path:
            i, j = pos
            if np.isfinite(costmap[i, j]):
                valid_path.append(pos)
            else:
                break
        return valid_path if valid_path else None

    def log_metrics(self, costmap):
        self.csv_writer.writerow([
            self.step_counter,
            self.i,
            self.j,
            costmap[self.i, self.j],
            self.goal_i,
            self.goal_j,
            len(self.global_path) if self.global_path else 0,
            1 if self.replan_counter == 0 else 0,
            len(self.get_valid_agents()),
        ])
        self.csv_file.flush()
        os.fsync(self.csv_file.fileno())
        self.step_counter += 1


def main():
    rclpy.init()
    node = AgentNode()
    try:
        rclpy.spin(node)
    finally:
        if hasattr(node, 'csv_file') and node.csv_file:
            node.csv_file.close()
        node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
