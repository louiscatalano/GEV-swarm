# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What this repo is

A ROS2 colcon workspace implementing multi-agent swarm navigation for Unmanned Ground Effect Vehicles (UGEVs) on a dynamic 2D grid environment. Agents cooperatively navigate from random start positions to a shared goal using path planning, ORCA collision avoidance, formation control, and distributed SLAM.

## Build & run

```bash
# Full clean rebuild (do this after changing message definitions or CMakeLists.txt)
rm -rf build install log
colcon build --symlink-install --parallel-workers 4
source install/setup.bash

# Incremental rebuild (after editing Python source only)
colcon build --symlink-install --parallel-workers 4
source install/setup.bash

# Run the environment publisher standalone
ros2 run my_agent environment_publisher

# Run the full multi-agent simulation (3–5 agents, random starts, V-formation)
ros2 launch my_agent multi_agent.launch.py

# Run the SLAM node (not included in the launch file by default)
ros2 run my_agent swarm_ai_node
```

**Always** `source install/setup.bash` before any `ros2` command. Do not edit files under `build/` or `install/`—they are regenerated on every build.

## Package layout

```
src/
  environment_msgs/      # Custom ROS2 message definitions only
    msg/                 # .msg files → generated Python/C++ at build time
  my_agent/              # All executable nodes
    my_agent/            # Python package
      agent_node.py      # Per-agent navigation node
      environment_publisher.py  # Dynamic grid environment
      swarm_ai_node.py   # Distributed SLAM (EnhancedSLAM node)
      swarm_visualizer.py       # Matplotlib live display
      path_planner.py    # DStarLite and PotentialField classes
      formation_control.py      # FormationController (V, line, diamond, echelon, column)
      orca.py            # ORCAAvoidance and orca_grid_move
    launch/
      multi_agent.launch.py
```

## ROS topic graph

| Topic | Message type | Publisher → Subscribers |
|---|---|---|
| `/environment_state` | `EnvironmentState` | `environment_publisher` → all agents, visualizer |
| `/swarm/state` | `AgentState` | each agent → all other agents (collision avoidance) |
| `/swarm/local_map_update` | `LocalMapUpdate` | each agent → `swarm_ai_node` |
| `/swarm/predicted_map` | `PredictedMap` | `swarm_ai_node` → each agent |
| `/swarm/guidance` | `GuidanceField` | `swarm_ai_node` → each agent |
| `/swarm/occupancy_grid` | `OccupancyGrid` | `swarm_ai_node` → (external tools) |
| `/agent_{id}/pose` | `geometry_msgs/Point` | each agent → (external tools) |

`NaN` in the environment field means impassable (land/obstacle).

## Custom message fields

- `EnvironmentState`: `step`, `width`, `height`, `float32[] data`, `bool[] forbidden`
- `AgentState`: `agent_id`, `i`, `j`, `intent_i`, `intent_j` (intent = next intended position; -1 means no intent)
- `LocalMapUpdate`: `agent_id`, `i`, `j`, `float32 value`
- `PredictedMap` / `GuidanceField`: `height`, `width`, `float32[] data`

All grid fields are row-major flat arrays; reshape with `np.array(msg.data).reshape(msg.height, msg.width)`.

## Agent architecture (agent_node.py)

Each `AgentNode` runs one iteration per `/environment_state` message:

1. **Costmap assembly** (`build_costmap`): base field + 0.5 × predicted_map + guidance_field
2. **Path planning** (`DStarLite` or `PotentialField`): replans periodically or when ≥10 cells change
3. **ORCA collision avoidance** (`navigate_with_orca`): adjusts move toward next waypoint; falls back to intent-conflict check
4. **Mode switch**: `TRANSIT` → `LOITER` on goal arrival at `(goal_i, goal_j)` (default `(32, 32)`)
5. **Publish**: `/agent_{id}/pose`, `/swarm/state`, `/swarm/local_map_update`

Agent node parameters: `agent_id`, `i0`, `j0`, `goal_i`, `goal_j`, `planner_type` (`'dstar'` or `'potential'`), `enable_formation`, `formation_type`.

## Formation control

`FormationController` in `formation_control.py` implements a virtual-structure approach. Agent 0 is always the leader. Available formation types: `V` (default, aerodynamically efficient), `line`, `diamond`, `echelon`, `column`. Formation is initialized lazily once ≥2 agents are observed. Enable via `enable_formation: True` parameter.

## SLAM node (swarm_ai_node.py)

`EnhancedSLAM` maintains a Bayesian occupancy grid (log-odds representation) updated from `/swarm/local_map_update`. It publishes:
- `/swarm/predicted_map`: interpolated cost field using Gaussian smoothing over unobserved regions
- `/swarm/guidance`: exploration bonus (negative cost) for cells unobserved for >10 seconds
- `/swarm/occupancy_grid`: standard ROS `OccupancyGrid` for external tooling

The SLAM node is **not included** in `multi_agent.launch.py`—run it separately if needed.

## Key invariants

- Grid is always 64×64. `EnvironmentPublisher` and `multi_agent.launch.py` both hardcode `SIZE = 64`.
- Goal cell is `(32, 32)` by default; `generate_land` ensures it is never blocked.
- Agent logs are written to `~/.ros/swarm_logs/agent_{id}_log_{timestamp}.csv`.
- When adding new messages to `environment_msgs`, update both `CMakeLists.txt` and `package.xml`, then do a full rebuild.
- When adding agents to the launch file, ensure unique `namespace=f'agent_{idx}'` and distinct `agent_id` parameters to avoid topic collisions.
