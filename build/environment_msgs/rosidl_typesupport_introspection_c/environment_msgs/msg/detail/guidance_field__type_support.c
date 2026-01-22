// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from environment_msgs:msg/GuidanceField.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "environment_msgs/msg/detail/guidance_field__rosidl_typesupport_introspection_c.h"
#include "environment_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "environment_msgs/msg/detail/guidance_field__functions.h"
#include "environment_msgs/msg/detail/guidance_field__struct.h"


// Include directives for member types
// Member `data`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void environment_msgs__msg__GuidanceField__rosidl_typesupport_introspection_c__GuidanceField_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  environment_msgs__msg__GuidanceField__init(message_memory);
}

void environment_msgs__msg__GuidanceField__rosidl_typesupport_introspection_c__GuidanceField_fini_function(void * message_memory)
{
  environment_msgs__msg__GuidanceField__fini(message_memory);
}

size_t environment_msgs__msg__GuidanceField__rosidl_typesupport_introspection_c__size_function__GuidanceField__data(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * environment_msgs__msg__GuidanceField__rosidl_typesupport_introspection_c__get_const_function__GuidanceField__data(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * environment_msgs__msg__GuidanceField__rosidl_typesupport_introspection_c__get_function__GuidanceField__data(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void environment_msgs__msg__GuidanceField__rosidl_typesupport_introspection_c__fetch_function__GuidanceField__data(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    environment_msgs__msg__GuidanceField__rosidl_typesupport_introspection_c__get_const_function__GuidanceField__data(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void environment_msgs__msg__GuidanceField__rosidl_typesupport_introspection_c__assign_function__GuidanceField__data(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    environment_msgs__msg__GuidanceField__rosidl_typesupport_introspection_c__get_function__GuidanceField__data(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool environment_msgs__msg__GuidanceField__rosidl_typesupport_introspection_c__resize_function__GuidanceField__data(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember environment_msgs__msg__GuidanceField__rosidl_typesupport_introspection_c__GuidanceField_message_member_array[3] = {
  {
    "width",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(environment_msgs__msg__GuidanceField, width),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "height",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(environment_msgs__msg__GuidanceField, height),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "data",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(environment_msgs__msg__GuidanceField, data),  // bytes offset in struct
    NULL,  // default value
    environment_msgs__msg__GuidanceField__rosidl_typesupport_introspection_c__size_function__GuidanceField__data,  // size() function pointer
    environment_msgs__msg__GuidanceField__rosidl_typesupport_introspection_c__get_const_function__GuidanceField__data,  // get_const(index) function pointer
    environment_msgs__msg__GuidanceField__rosidl_typesupport_introspection_c__get_function__GuidanceField__data,  // get(index) function pointer
    environment_msgs__msg__GuidanceField__rosidl_typesupport_introspection_c__fetch_function__GuidanceField__data,  // fetch(index, &value) function pointer
    environment_msgs__msg__GuidanceField__rosidl_typesupport_introspection_c__assign_function__GuidanceField__data,  // assign(index, value) function pointer
    environment_msgs__msg__GuidanceField__rosidl_typesupport_introspection_c__resize_function__GuidanceField__data  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers environment_msgs__msg__GuidanceField__rosidl_typesupport_introspection_c__GuidanceField_message_members = {
  "environment_msgs__msg",  // message namespace
  "GuidanceField",  // message name
  3,  // number of fields
  sizeof(environment_msgs__msg__GuidanceField),
  false,  // has_any_key_member_
  environment_msgs__msg__GuidanceField__rosidl_typesupport_introspection_c__GuidanceField_message_member_array,  // message members
  environment_msgs__msg__GuidanceField__rosidl_typesupport_introspection_c__GuidanceField_init_function,  // function to initialize message memory (memory has to be allocated)
  environment_msgs__msg__GuidanceField__rosidl_typesupport_introspection_c__GuidanceField_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t environment_msgs__msg__GuidanceField__rosidl_typesupport_introspection_c__GuidanceField_message_type_support_handle = {
  0,
  &environment_msgs__msg__GuidanceField__rosidl_typesupport_introspection_c__GuidanceField_message_members,
  get_message_typesupport_handle_function,
  &environment_msgs__msg__GuidanceField__get_type_hash,
  &environment_msgs__msg__GuidanceField__get_type_description,
  &environment_msgs__msg__GuidanceField__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_environment_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, environment_msgs, msg, GuidanceField)() {
  if (!environment_msgs__msg__GuidanceField__rosidl_typesupport_introspection_c__GuidanceField_message_type_support_handle.typesupport_identifier) {
    environment_msgs__msg__GuidanceField__rosidl_typesupport_introspection_c__GuidanceField_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &environment_msgs__msg__GuidanceField__rosidl_typesupport_introspection_c__GuidanceField_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
