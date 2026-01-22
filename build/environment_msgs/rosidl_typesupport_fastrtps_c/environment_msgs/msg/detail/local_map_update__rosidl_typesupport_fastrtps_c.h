// generated from rosidl_typesupport_fastrtps_c/resource/idl__rosidl_typesupport_fastrtps_c.h.em
// with input from environment_msgs:msg/LocalMapUpdate.idl
// generated code does not contain a copyright notice
#ifndef ENVIRONMENT_MSGS__MSG__DETAIL__LOCAL_MAP_UPDATE__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
#define ENVIRONMENT_MSGS__MSG__DETAIL__LOCAL_MAP_UPDATE__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_


#include <stddef.h>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "environment_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "environment_msgs/msg/detail/local_map_update__struct.h"
#include "fastcdr/Cdr.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_environment_msgs
bool cdr_serialize_environment_msgs__msg__LocalMapUpdate(
  const environment_msgs__msg__LocalMapUpdate * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_environment_msgs
bool cdr_deserialize_environment_msgs__msg__LocalMapUpdate(
  eprosima::fastcdr::Cdr &,
  environment_msgs__msg__LocalMapUpdate * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_environment_msgs
size_t get_serialized_size_environment_msgs__msg__LocalMapUpdate(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_environment_msgs
size_t max_serialized_size_environment_msgs__msg__LocalMapUpdate(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_environment_msgs
bool cdr_serialize_key_environment_msgs__msg__LocalMapUpdate(
  const environment_msgs__msg__LocalMapUpdate * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_environment_msgs
size_t get_serialized_size_key_environment_msgs__msg__LocalMapUpdate(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_environment_msgs
size_t max_serialized_size_key_environment_msgs__msg__LocalMapUpdate(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_environment_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, environment_msgs, msg, LocalMapUpdate)();

#ifdef __cplusplus
}
#endif

#endif  // ENVIRONMENT_MSGS__MSG__DETAIL__LOCAL_MAP_UPDATE__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
