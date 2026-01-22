// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from environment_msgs:msg/LocalMapUpdate.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "environment_msgs/msg/local_map_update.h"


#ifndef ENVIRONMENT_MSGS__MSG__DETAIL__LOCAL_MAP_UPDATE__STRUCT_H_
#define ENVIRONMENT_MSGS__MSG__DETAIL__LOCAL_MAP_UPDATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/LocalMapUpdate in the package environment_msgs.
typedef struct environment_msgs__msg__LocalMapUpdate
{
  int32_t agent_id;
  int32_t i;
  int32_t j;
  float value;
} environment_msgs__msg__LocalMapUpdate;

// Struct for a sequence of environment_msgs__msg__LocalMapUpdate.
typedef struct environment_msgs__msg__LocalMapUpdate__Sequence
{
  environment_msgs__msg__LocalMapUpdate * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} environment_msgs__msg__LocalMapUpdate__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ENVIRONMENT_MSGS__MSG__DETAIL__LOCAL_MAP_UPDATE__STRUCT_H_
