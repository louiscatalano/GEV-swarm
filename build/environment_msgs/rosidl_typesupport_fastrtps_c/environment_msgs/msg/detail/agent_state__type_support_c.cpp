// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from environment_msgs:msg/AgentState.idl
// generated code does not contain a copyright notice
#include "environment_msgs/msg/detail/agent_state__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <cstddef>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/serialization_helpers.hpp"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "environment_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "environment_msgs/msg/detail/agent_state__struct.h"
#include "environment_msgs/msg/detail/agent_state__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif


// forward declare type support functions


using _AgentState__ros_msg_type = environment_msgs__msg__AgentState;


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_environment_msgs
bool cdr_serialize_environment_msgs__msg__AgentState(
  const environment_msgs__msg__AgentState * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: agent_id
  {
    cdr << ros_message->agent_id;
  }

  // Field name: i
  {
    cdr << ros_message->i;
  }

  // Field name: j
  {
    cdr << ros_message->j;
  }

  // Field name: intent_i
  {
    cdr << ros_message->intent_i;
  }

  // Field name: intent_j
  {
    cdr << ros_message->intent_j;
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_environment_msgs
bool cdr_deserialize_environment_msgs__msg__AgentState(
  eprosima::fastcdr::Cdr & cdr,
  environment_msgs__msg__AgentState * ros_message)
{
  // Field name: agent_id
  {
    cdr >> ros_message->agent_id;
  }

  // Field name: i
  {
    cdr >> ros_message->i;
  }

  // Field name: j
  {
    cdr >> ros_message->j;
  }

  // Field name: intent_i
  {
    cdr >> ros_message->intent_i;
  }

  // Field name: intent_j
  {
    cdr >> ros_message->intent_j;
  }

  return true;
}  // NOLINT(readability/fn_size)


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_environment_msgs
size_t get_serialized_size_environment_msgs__msg__AgentState(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _AgentState__ros_msg_type * ros_message = static_cast<const _AgentState__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Field name: agent_id
  {
    size_t item_size = sizeof(ros_message->agent_id);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: i
  {
    size_t item_size = sizeof(ros_message->i);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: j
  {
    size_t item_size = sizeof(ros_message->j);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: intent_i
  {
    size_t item_size = sizeof(ros_message->intent_i);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: intent_j
  {
    size_t item_size = sizeof(ros_message->intent_j);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_environment_msgs
size_t max_serialized_size_environment_msgs__msg__AgentState(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // Field name: agent_id
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: i
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: j
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: intent_i
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: intent_j
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }


  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = environment_msgs__msg__AgentState;
    is_plain =
      (
      offsetof(DataType, intent_j) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_environment_msgs
bool cdr_serialize_key_environment_msgs__msg__AgentState(
  const environment_msgs__msg__AgentState * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: agent_id
  {
    cdr << ros_message->agent_id;
  }

  // Field name: i
  {
    cdr << ros_message->i;
  }

  // Field name: j
  {
    cdr << ros_message->j;
  }

  // Field name: intent_i
  {
    cdr << ros_message->intent_i;
  }

  // Field name: intent_j
  {
    cdr << ros_message->intent_j;
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_environment_msgs
size_t get_serialized_size_key_environment_msgs__msg__AgentState(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _AgentState__ros_msg_type * ros_message = static_cast<const _AgentState__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;

  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Field name: agent_id
  {
    size_t item_size = sizeof(ros_message->agent_id);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: i
  {
    size_t item_size = sizeof(ros_message->i);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: j
  {
    size_t item_size = sizeof(ros_message->j);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: intent_i
  {
    size_t item_size = sizeof(ros_message->intent_i);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: intent_j
  {
    size_t item_size = sizeof(ros_message->intent_j);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_environment_msgs
size_t max_serialized_size_key_environment_msgs__msg__AgentState(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;
  // Field name: agent_id
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: i
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: j
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: intent_i
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: intent_j
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = environment_msgs__msg__AgentState;
    is_plain =
      (
      offsetof(DataType, intent_j) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}


static bool _AgentState__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const environment_msgs__msg__AgentState * ros_message = static_cast<const environment_msgs__msg__AgentState *>(untyped_ros_message);
  (void)ros_message;
  return cdr_serialize_environment_msgs__msg__AgentState(ros_message, cdr);
}

static bool _AgentState__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  environment_msgs__msg__AgentState * ros_message = static_cast<environment_msgs__msg__AgentState *>(untyped_ros_message);
  (void)ros_message;
  return cdr_deserialize_environment_msgs__msg__AgentState(cdr, ros_message);
}

static uint32_t _AgentState__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_environment_msgs__msg__AgentState(
      untyped_ros_message, 0));
}

static size_t _AgentState__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_environment_msgs__msg__AgentState(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_AgentState = {
  "environment_msgs::msg",
  "AgentState",
  _AgentState__cdr_serialize,
  _AgentState__cdr_deserialize,
  _AgentState__get_serialized_size,
  _AgentState__max_serialized_size,
  nullptr
};

static rosidl_message_type_support_t _AgentState__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_AgentState,
  get_message_typesupport_handle_function,
  &environment_msgs__msg__AgentState__get_type_hash,
  &environment_msgs__msg__AgentState__get_type_description,
  &environment_msgs__msg__AgentState__get_type_description_sources,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, environment_msgs, msg, AgentState)() {
  return &_AgentState__type_support;
}

#if defined(__cplusplus)
}
#endif
