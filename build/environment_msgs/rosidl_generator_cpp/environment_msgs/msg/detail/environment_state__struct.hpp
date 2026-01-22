// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from environment_msgs:msg/EnvironmentState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "environment_msgs/msg/environment_state.hpp"


#ifndef ENVIRONMENT_MSGS__MSG__DETAIL__ENVIRONMENT_STATE__STRUCT_HPP_
#define ENVIRONMENT_MSGS__MSG__DETAIL__ENVIRONMENT_STATE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__environment_msgs__msg__EnvironmentState __attribute__((deprecated))
#else
# define DEPRECATED__environment_msgs__msg__EnvironmentState __declspec(deprecated)
#endif

namespace environment_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct EnvironmentState_
{
  using Type = EnvironmentState_<ContainerAllocator>;

  explicit EnvironmentState_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->step = 0l;
      this->width = 0l;
      this->height = 0l;
    }
  }

  explicit EnvironmentState_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->step = 0l;
      this->width = 0l;
      this->height = 0l;
    }
  }

  // field types and members
  using _step_type =
    int32_t;
  _step_type step;
  using _width_type =
    int32_t;
  _width_type width;
  using _height_type =
    int32_t;
  _height_type height;
  using _data_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _data_type data;
  using _forbidden_type =
    std::vector<bool, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<bool>>;
  _forbidden_type forbidden;

  // setters for named parameter idiom
  Type & set__step(
    const int32_t & _arg)
  {
    this->step = _arg;
    return *this;
  }
  Type & set__width(
    const int32_t & _arg)
  {
    this->width = _arg;
    return *this;
  }
  Type & set__height(
    const int32_t & _arg)
  {
    this->height = _arg;
    return *this;
  }
  Type & set__data(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->data = _arg;
    return *this;
  }
  Type & set__forbidden(
    const std::vector<bool, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<bool>> & _arg)
  {
    this->forbidden = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    environment_msgs::msg::EnvironmentState_<ContainerAllocator> *;
  using ConstRawPtr =
    const environment_msgs::msg::EnvironmentState_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<environment_msgs::msg::EnvironmentState_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<environment_msgs::msg::EnvironmentState_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      environment_msgs::msg::EnvironmentState_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<environment_msgs::msg::EnvironmentState_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      environment_msgs::msg::EnvironmentState_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<environment_msgs::msg::EnvironmentState_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<environment_msgs::msg::EnvironmentState_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<environment_msgs::msg::EnvironmentState_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__environment_msgs__msg__EnvironmentState
    std::shared_ptr<environment_msgs::msg::EnvironmentState_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__environment_msgs__msg__EnvironmentState
    std::shared_ptr<environment_msgs::msg::EnvironmentState_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const EnvironmentState_ & other) const
  {
    if (this->step != other.step) {
      return false;
    }
    if (this->width != other.width) {
      return false;
    }
    if (this->height != other.height) {
      return false;
    }
    if (this->data != other.data) {
      return false;
    }
    if (this->forbidden != other.forbidden) {
      return false;
    }
    return true;
  }
  bool operator!=(const EnvironmentState_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct EnvironmentState_

// alias to use template instance with default allocator
using EnvironmentState =
  environment_msgs::msg::EnvironmentState_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace environment_msgs

#endif  // ENVIRONMENT_MSGS__MSG__DETAIL__ENVIRONMENT_STATE__STRUCT_HPP_
