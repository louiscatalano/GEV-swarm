// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from environment_msgs:msg/LocalMapUpdate.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "environment_msgs/msg/detail/local_map_update__functions.h"
#include "environment_msgs/msg/detail/local_map_update__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace environment_msgs
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void LocalMapUpdate_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) environment_msgs::msg::LocalMapUpdate(_init);
}

void LocalMapUpdate_fini_function(void * message_memory)
{
  auto typed_message = static_cast<environment_msgs::msg::LocalMapUpdate *>(message_memory);
  typed_message->~LocalMapUpdate();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember LocalMapUpdate_message_member_array[4] = {
  {
    "agent_id",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(environment_msgs::msg::LocalMapUpdate, agent_id),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "i",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(environment_msgs::msg::LocalMapUpdate, i),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "j",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(environment_msgs::msg::LocalMapUpdate, j),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "value",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(environment_msgs::msg::LocalMapUpdate, value),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers LocalMapUpdate_message_members = {
  "environment_msgs::msg",  // message namespace
  "LocalMapUpdate",  // message name
  4,  // number of fields
  sizeof(environment_msgs::msg::LocalMapUpdate),
  false,  // has_any_key_member_
  LocalMapUpdate_message_member_array,  // message members
  LocalMapUpdate_init_function,  // function to initialize message memory (memory has to be allocated)
  LocalMapUpdate_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t LocalMapUpdate_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &LocalMapUpdate_message_members,
  get_message_typesupport_handle_function,
  &environment_msgs__msg__LocalMapUpdate__get_type_hash,
  &environment_msgs__msg__LocalMapUpdate__get_type_description,
  &environment_msgs__msg__LocalMapUpdate__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace environment_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<environment_msgs::msg::LocalMapUpdate>()
{
  return &::environment_msgs::msg::rosidl_typesupport_introspection_cpp::LocalMapUpdate_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, environment_msgs, msg, LocalMapUpdate)() {
  return &::environment_msgs::msg::rosidl_typesupport_introspection_cpp::LocalMapUpdate_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
