from setuptools import find_packages, setup
from glob import glob
import os

package_name = 'my_agent'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/my_agent']),
        ('share/my_agent', ['package.xml']),
        (os.path.join('share', 'my_agent', 'launch'),
            glob('launch/*.launch.py')),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='lcata',
    maintainer_email='lcata@todo.todo',
    description='TODO: Package description',
    license='TODO: License declaration',
    extras_require={
        'test': [
            'pytest',
        ],
    },
    entry_points={
        'console_scripts': [
            'agent_node = my_agent.agent_node:main',
            'environment_publisher = my_agent.environment_publisher:main',
            'swarm_visualizer = my_agent.swarm_visualizer:main',
            'swarm_ai_node = my_agent.swarm_ai_node:main',
            'swarm_cli = my_agent.swarm_cli:main',
        ],
    },
)
