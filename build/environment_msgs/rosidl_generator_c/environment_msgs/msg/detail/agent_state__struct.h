// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from environment_msgs:msg/AgentState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "environment_msgs/msg/agent_state.h"


#ifndef ENVIRONMENT_MSGS__MSG__DETAIL__AGENT_STATE__STRUCT_H_
#define ENVIRONMENT_MSGS__MSG__DETAIL__AGENT_STATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/AgentState in the package environment_msgs.
typedef struct environment_msgs__msg__AgentState
{
  int32_t agent_id;
  int32_t i;
  int32_t j;
  int32_t intent_i;
  int32_t intent_j;
} environment_msgs__msg__AgentState;

// Struct for a sequence of environment_msgs__msg__AgentState.
typedef struct environment_msgs__msg__AgentState__Sequence
{
  environment_msgs__msg__AgentState * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} environment_msgs__msg__AgentState__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ENVIRONMENT_MSGS__MSG__DETAIL__AGENT_STATE__STRUCT_H_
