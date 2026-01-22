// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from environment_msgs:msg/EnvironmentState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "environment_msgs/msg/environment_state.h"


#ifndef ENVIRONMENT_MSGS__MSG__DETAIL__ENVIRONMENT_STATE__STRUCT_H_
#define ENVIRONMENT_MSGS__MSG__DETAIL__ENVIRONMENT_STATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'data'
// Member 'forbidden'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/EnvironmentState in the package environment_msgs.
typedef struct environment_msgs__msg__EnvironmentState
{
  int32_t step;
  int32_t width;
  int32_t height;
  rosidl_runtime_c__float__Sequence data;
  rosidl_runtime_c__boolean__Sequence forbidden;
} environment_msgs__msg__EnvironmentState;

// Struct for a sequence of environment_msgs__msg__EnvironmentState.
typedef struct environment_msgs__msg__EnvironmentState__Sequence
{
  environment_msgs__msg__EnvironmentState * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} environment_msgs__msg__EnvironmentState__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ENVIRONMENT_MSGS__MSG__DETAIL__ENVIRONMENT_STATE__STRUCT_H_
