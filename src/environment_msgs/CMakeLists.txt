cmake_minimum_required(VERSION 3.8)
project(environment_msgs)

find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/EnvironmentState.msg"
  "msg/AgentState.msg"
  "msg/LocalMapUpdate.msg"
  "msg/PredictedMap.msg"
  "msg/GuidanceField.msg"
)

ament_export_dependencies(rosidl_default_runtime)
ament_package()
