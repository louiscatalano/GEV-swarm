from setuptools import find_packages
from setuptools import setup

setup(
    name='environment_msgs',
    version='0.0.0',
    packages=find_packages(
        include=('environment_msgs', 'environment_msgs.*')),
)
