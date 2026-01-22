// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from environment_msgs:msg/GuidanceField.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "environment_msgs/msg/guidance_field.h"


#ifndef ENVIRONMENT_MSGS__MSG__DETAIL__GUIDANCE_FIELD__STRUCT_H_
#define ENVIRONMENT_MSGS__MSG__DETAIL__GUIDANCE_FIELD__STRUCT_H_

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
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/GuidanceField in the package environment_msgs.
typedef struct environment_msgs__msg__GuidanceField
{
  int32_t width;
  int32_t height;
  rosidl_runtime_c__float__Sequence data;
} environment_msgs__msg__GuidanceField;

// Struct for a sequence of environment_msgs__msg__GuidanceField.
typedef struct environment_msgs__msg__GuidanceField__Sequence
{
  environment_msgs__msg__GuidanceField * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} environment_msgs__msg__GuidanceField__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ENVIRONMENT_MSGS__MSG__DETAIL__GUIDANCE_FIELD__STRUCT_H_
