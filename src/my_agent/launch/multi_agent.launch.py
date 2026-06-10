import random
import numpy as np
from collections import deque
from datetime import datetime
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, OpaqueFunction
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def _fill_lakes(forbidden, height, width):
    """Mark enclosed water cells (unreachable from border) as land."""
    reachable = np.zeros((height, width), dtype=bool)
    queue = deque()
    for i in range(height):
        for j in (0, width - 1):
            if not forbidden[i, j] and not reachable[i, j]:
                reachable[i, j] = True
                queue.append((i, j))
    for j in range(width):
        for i in (0, height - 1):
            if not forbidden[i, j] and not reachable[i, j]:
                reachable[i, j] = True
                queue.append((i, j))
    while queue:
        ci, cj = queue.popleft()
        for di, dj in ((-1, 0), (1, 0), (0, -1), (0, 1)):
            ni, nj = ci + di, cj + dj
            if 0 <= ni < height and 0 <= nj < width and not forbidden[ni, nj] and not reachable[ni, nj]:
                reachable[ni, nj] = True
                queue.append((ni, nj))
    forbidden[~reachable] = True
    return forbidden


def _generate_land(rng, height, width, goal=(32, 32), max_retries=10):
    """Mirror of EnvironmentPublisher.generate_land using an explicit rng instance."""
    forbidden = np.zeros((height, width), dtype=bool)

    p_no_land = 0.05
    max_coverage = 0.3
    min_body_frac = 0.05
    max_bodies = 2

    if rng.random() < p_no_land:
        return forbidden

    max_land_cells = int(max_coverage * height * width)
    min_body_size = int(min_body_frac * height * width)

    total_land = 0
    n_bodies = rng.randint(0, max_bodies)

    for _ in range(n_bodies):
        if total_land >= max_land_cells:
            break
        for _ in range(100):
            si = rng.randint(0, height - 1)
            sj = rng.randint(0, width - 1)
            if (si, sj) == goal or forbidden[si, sj]:
                continue
            break
        else:
            continue
        remaining_land = max_land_cells - total_land
        if remaining_land < min_body_size:
            break
        target_size = rng.randint(min_body_size, remaining_land)
        q = deque([(si, sj)])
        forbidden[si, sj] = True
        grown = 1
        while q and grown < target_size:
            ci, cj = q.popleft()
            for di, dj in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                ni, nj = ci + di, cj + dj
                if ni < 0 or ni >= height or nj < 0 or nj >= width:
                    continue
                if forbidden[ni, nj] or (ni, nj) == goal:
                    continue
                if rng.random() < 0.7:
                    forbidden[ni, nj] = True
                    q.append((ni, nj))
                    grown += 1
                    if grown >= target_size:
                        break
        total_land += grown

    gi, gj = goal
    if forbidden[gi, gj]:
        if max_retries > 0:
            return _generate_land(rng, height, width, goal, max_retries - 1)
        else:
            return np.zeros((height, width), dtype=bool)

    forbidden = _fill_lakes(forbidden, height, width)
    forbidden[gi, gj] = False
    return forbidden


def launch_setup(context, *args, **kwargs):
    seed_str = LaunchConfiguration('seed').perform(context)
    seed = int(seed_str)
    if seed == -1:
        seed = random.randint(0, 2**31 - 1)

    random.seed(seed)
    
    # Generate launch_id from seed and timestamp for uniqueness
    launch_id = f"{seed}_{datetime.now().strftime('%Y%m%d_%H%M%S')}"
    
    # Get SLAM enabled flag from launch argument
    slam_enabled_str = LaunchConfiguration('slam_enabled').perform(context)
    slam_enabled = slam_enabled_str.lower() == 'true'

    SIZE = 64
    MARGIN = 5

    num_agents = random.randint(3, 5)
    goal_i = random.randint(MARGIN, SIZE - 1 - MARGIN)
    goal_j = random.randint(MARGIN, SIZE - 1 - MARGIN)

    # Replicate land generation with a fresh RNG seeded identically to the
    # environment_publisher so forbidden cells are known before placing agents.
    land_rng = random.Random(seed)
    forbidden = _generate_land(land_rng, SIZE, SIZE, goal=(goal_i, goal_j))

    initial_positions = []
    seen = set()
    seen.add((goal_i, goal_j))
    while len(initial_positions) < num_agents:
        i = random.randint(0, SIZE - 1)
        j = random.randint(0, SIZE - 1)
        if not forbidden[i, j] and (i, j) not in seen:
            initial_positions.append((i, j))
            seen.add((i, j))

    nodes = []

    nodes.append(
        Node(
            package='my_agent',
            executable='environment_publisher',
            name='environment_publisher',
            parameters=[{
                'goal_i': goal_i,
                'goal_j': goal_j,
                'seed': seed,
                'launch_id': launch_id,
                'slam_enabled': slam_enabled,
                'num_agents': num_agents,
            }]
        )
    )

    for idx, (i0, j0) in enumerate(initial_positions):
        nodes.append(
            Node(
                package='my_agent',
                executable='agent_node',
                namespace=f'agent_{idx}',
                remappings=[('environment_state', '/environment_state')],
                parameters=[{
                    'agent_id': idx,
                    'i0': i0,
                    'j0': j0,
                    'goal_i': goal_i,
                    'goal_j': goal_j,
                    'launch_id': launch_id,
                }]
            )
        )

    # Conditionally launch SLAM node based on slam_enabled parameter
    if slam_enabled:
        nodes.append(
            Node(
                package='my_agent',
                executable='swarm_ai_node',
                name='swarm_ai_node',
                parameters=[{'height': SIZE, 'width': SIZE}]
            )
        )

    nodes.append(
        Node(
            package='my_agent',
            executable='swarm_visualizer',
            name='swarm_visualizer',
            remappings=[('environment_state', '/environment_state')],
            parameters=[{'num_agents': num_agents, 'goal_i': goal_i, 'goal_j': goal_j}]
        )
    )

    return nodes


def generate_launch_description():
    return LaunchDescription([
        DeclareLaunchArgument(
            'seed',
            default_value='-1',
            description='RNG seed for land generation, goal position, agent count, and initial positions. -1 = random.'
        ),
        DeclareLaunchArgument(
            'slam_enabled',
            default_value='true',
            description='Enable SLAM node (swarm_ai_node). Set to "false" to disable SLAM for comparison runs.'
        ),
        OpaqueFunction(function=launch_setup),
    ])
