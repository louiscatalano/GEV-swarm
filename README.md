# GEV-swarm

# Build 
rm -rf build install log
colcon build --symlink-install --parallel-workers 4
source install/setup.bash
ros2 run my_agent environment_publisher

# Run
source install/setup.bash
ros2 launch my_agent multi_agent.launch.py
