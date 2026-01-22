// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from environment_msgs:msg/LocalMapUpdate.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "environment_msgs/msg/local_map_update.hpp"


#ifndef ENVIRONMENT_MSGS__MSG__DETAIL__LOCAL_MAP_UPDATE__STRUCT_HPP_
#define ENVIRONMENT_MSGS__MSG__DETAIL__LOCAL_MAP_UPDATE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__environment_msgs__msg__LocalMapUpdate __attribute__((deprecated))
#else
# define DEPRECATED__environment_msgs__msg__LocalMapUpdate __declspec(deprecated)
#endif

namespace environment_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LocalMapUpdate_
{
  using Type = LocalMapUpdate_<ContainerAllocator>;

  explicit LocalMapUpdate_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->agent_id = 0l;
      this->i = 0l;
      this->j = 0l;
      this->value = 0.0f;
    }
  }

  explicit LocalMapUpdate_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->agent_id = 0l;
      this->i = 0l;
      this->j = 0l;
      this->value = 0.0f;
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
  using _value_type =
    float;
  _value_type value;

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
  Type & set__value(
    const float & _arg)
  {
    this->value = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    environment_msgs::msg::LocalMapUpdate_<ContainerAllocator> *;
  using ConstRawPtr =
    const environment_msgs::msg::LocalMapUpdate_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<environment_msgs::msg::LocalMapUpdate_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<environment_msgs::msg::LocalMapUpdate_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      environment_msgs::msg::LocalMapUpdate_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<environment_msgs::msg::LocalMapUpdate_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      environment_msgs::msg::LocalMapUpdate_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<environment_msgs::msg::LocalMapUpdate_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<environment_msgs::msg::LocalMapUpdate_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<environment_msgs::msg::LocalMapUpdate_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__environment_msgs__msg__LocalMapUpdate
    std::shared_ptr<environment_msgs::msg::LocalMapUpdate_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__environment_msgs__msg__LocalMapUpdate
    std::shared_ptr<environment_msgs::msg::LocalMapUpdate_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LocalMapUpdate_ & other) const
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
    if (this->value != other.value) {
      return false;
    }
    return true;
  }
  bool operator!=(const LocalMapUpdate_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LocalMapUpdate_

// alias to use template instance with default allocator
using LocalMapUpdate =
  environment_msgs::msg::LocalMapUpdate_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace environment_msgs

#endif  // ENVIRONMENT_MSGS__MSG__DETAIL__LOCAL_MAP_UPDATE__STRUCT_HPP_
