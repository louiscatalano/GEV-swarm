// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from environment_msgs:msg/AgentState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "environment_msgs/msg/agent_state.hpp"


#ifndef ENVIRONMENT_MSGS__MSG__DETAIL__AGENT_STATE__STRUCT_HPP_
#define ENVIRONMENT_MSGS__MSG__DETAIL__AGENT_STATE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__environment_msgs__msg__AgentState __attribute__((deprecated))
#else
# define DEPRECATED__environment_msgs__msg__AgentState __declspec(deprecated)
#endif

namespace environment_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct AgentState_
{
  using Type = AgentState_<ContainerAllocator>;

  explicit AgentState_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->agent_id = 0l;
      this->i = 0l;
      this->j = 0l;
      this->intent_i = 0l;
      this->intent_j = 0l;
    }
  }

  explicit AgentState_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->agent_id = 0l;
      this->i = 0l;
      this->j = 0l;
      this->intent_i = 0l;
      this->intent_j = 0l;
    }
  }

  // field types and members
  using _agent_id_type =
    int32_t;
  _agent_id_type agent_id;
  using _i_type =
    int32_t;
  _i_type i;
  using _j_type =
    int32_t;
  _j_type j;
  using _intent_i_type =
    int32_t;
  _intent_i_type intent_i;
  using _intent_j_type =
    int32_t;
  _intent_j_type intent_j;

  // setters for named parameter idiom
  Type & set__agent_id(
    const int32_t & _arg)
  {
    this->agent_id = _arg;
    return *this;
  }
  Type & set__i(
    const int32_t & _arg)
  {
    this->i = _arg;
    return *this;
  }
  Type & set__j(
    const int32_t & _arg)
  {
    this->j = _arg;
    return *this;
  }
  Type & set__intent_i(
    const int32_t & _arg)
  {
    this->intent_i = _arg;
    return *this;
  }
  Type & set__intent_j(
    const int32_t & _arg)
  {
    this->intent_j = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    environment_msgs::msg::AgentState_<ContainerAllocator> *;
  using ConstRawPtr =
    const environment_msgs::msg::AgentState_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<environment_msgs::msg::AgentState_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<environment_msgs::msg::AgentState_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      environment_msgs::msg::AgentState_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<environment_msgs::msg::AgentState_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      environment_msgs::msg::AgentState_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<environment_msgs::msg::AgentState_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<environment_msgs::msg::AgentState_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<environment_msgs::msg::AgentState_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__environment_msgs__msg__AgentState
    std::shared_ptr<environment_msgs::msg::AgentState_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__environment_msgs__msg__AgentState
    std::shared_ptr<environment_msgs::msg::AgentState_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const AgentState_ & other) const
  {
    if (this->agent_id != other.agent_id) {
      return false;
    }
    if (this->i != other.i) {
      return false;
    }
    if (this->j != other.j) {
      return false;
    }
    if (this->intent_i != other.intent_i) {
      return false;
    }
    if (this->intent_j != other.intent_j) {
      return false;
    }
    return true;
  }
  bool operator!=(const AgentState_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct AgentState_

// alias to use template instance with default allocator
using AgentState =
  environment_msgs::msg::AgentState_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace environment_msgs

#endif  // ENVIRONMENT_MSGS__MSG__DETAIL__AGENT_STATE__STRUCT_HPP_
