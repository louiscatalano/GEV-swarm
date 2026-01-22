# this launch file starts a random number of multiple instances of the agent_node between 3 and 5 with random different initial positions

import random
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():

    agents = []
    num_agents = random.randint(3, 5)

    # Hardcode same size for now (matches environment)
    SIZE = 64

    initial_positions = []
    while len(initial_positions) < num_agents:
        i = random.randint(0, SIZE - 1)
        j = random.randint(0, SIZE - 1)
        initial_positions.append((i, j))

    for idx, (i0, j0) in enumerate(initial_positions):
        agents.append(
            Node(
                package='my_agent',
                executable='agent_node',
                namespace=f'agent_{idx}',
                remappings=[
                    ('environment_state', '/environment_state')
                ],
                parameters=[{'agent_id': idx, 'i0': i0, 'j0': j0, 'num_agents': num_agents}]
            )
        )

    # Launch the visualizer and pass num_agents so it receives the parameter
    agents.append(
        Node(
            package='my_agent',
            executable='swarm_visualizer',
            name='swarm_visualizer',
            remappings=[('environment_state', '/environment_state')],
            parameters=[{'num_agents': num_agents}]
        )
    )

    return LaunchDescription(agents)
