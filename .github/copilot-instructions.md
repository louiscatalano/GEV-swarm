## Project snapshot

- This repository is a ROS2/colcon workspace. Packages live under `src/` (e.g. `src/my_agent`, `src/environment_msgs`).
- Custom ROS messages are defined in `src/environment_msgs/msg/` (example: `AgentState.msg`).
- Launch files are Python-based and live under package `launch/` directories (example: `src/my_agent/launch/multi_agent.launch.py`).

## Big picture (what an agent needs to know)

- Build & runtime: the project uses `colcon` to build packages and generates message artifacts into `install/`.
- Typical developer flow: edit code in `src/`, run `colcon build`, then `source install/setup.bash` before running nodes or launch files.
- Nodes communicate over ROS topics; this repo uses a topic named `/environment_state` carrying `environment_msgs/msg/AgentState`.
- Launch files configure multiple agent nodes by namespace, remappings and ROS parameters. Example: `multi_agent.launch.py` sets `package='my_agent'`, `executable='agent_node'`, remaps `environment_state` → `/environment_state`, and sets `agent_id` as a parameter.

## Concrete dev commands

- Build workspace:

  ```bash
  colcon build --symlink-install --parallel-workers 4
  ```

- Source the workspace for running and for unit/ros2 tests:

  ```bash
  source install/setup.bash
  ```

- Run the multi-agent launch (after sourcing):

  ```bash
  ros2 launch my_agent multi_agent.launch.py
  ```

## Patterns & conventions specific to this repo

- Package layout: put packages in `src/`. Do not edit generated files under `build/` or `install/` — change source under `src/` and re-build.
- Message schema: add new messages under `src/<package>/msg/` and ensure package manifest (package.xml/CMakeLists) is updated so `colcon build` generates artifacts.
- Launch files are Python functions returning a `LaunchDescription`. When changing how agents are spawned, update both `namespace` and `parameters` consistently (see `multi_agent.launch.py` — note it currently hardcodes `namespace='agent_0'` and `agent_id: 0`; update those to the loop index when adding agents).
- Topic naming: global environment topic is `/environment_state`. Remappings are used in launch files — prefer launch remappings over code-level name changes.

## Integration points & external dependencies

- ROS2 (Foxy/Galactic/Humble — verify distro from environment). This repo expects `colcon` and standard ROS2 tooling (`ros2`, `colcon`).
- Custom message package: `environment_msgs` provides `AgentState.msg` with fields (`int32 agent_id`, `int32 i`, `int32 j`). Generated Python/C++ message modules are produced by `colcon build`.

## What to watch for when modifying code

- Always rebuild after changing message definitions or CMake/package manifests: `colcon build` → `source install/setup.bash`.
- Don't change runtime files in `install/` or `build/`. Edits there are lost on rebuild and confuse reviewers.
- When editing launch files that spawn multiple agents, ensure unique `namespace` and distinct `agent_id` parameters per instance to avoid namespace collisions.

## Examples to copy when implementing changes

- Publish/subscribe to the environment state topic using type `environment_msgs.msg.AgentState` (Python) or `environment_msgs::msg::AgentState` (C++). See `src/environment_msgs/msg/AgentState.msg` for fields.
- Example: modify `multi_agent.launch.py` loop to set `namespace=f'agent_{idx}'` and `parameters=[{'agent_id': idx, 'i0': i0, 'j0': j0}]`.

## Quick checklist for PRs

- Verify `colcon build` completes locally.
- Source `install/setup.bash` and run relevant launch file(s) to smoke-test behavior.
- Ensure no edits in `build/` or `install/` are included in commits.

---
If anything above is unclear or you want more examples (unit test patterns, exact ROS distro used, or node entrypoints), tell me which area to expand and I will iterate.
