// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from environment_msgs:msg/EnvironmentState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "environment_msgs/msg/environment_state.hpp"


#ifndef ENVIRONMENT_MSGS__MSG__DETAIL__ENVIRONMENT_STATE__BUILDER_HPP_
#define ENVIRONMENT_MSGS__MSG__DETAIL__ENVIRONMENT_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "environment_msgs/msg/detail/environment_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace environment_msgs
{

namespace msg
{

namespace builder
{

class Init_EnvironmentState_forbidden
{
public:
  explicit Init_EnvironmentState_forbidden(::environment_msgs::msg::EnvironmentState & msg)
  : msg_(msg)
  {}
  ::environment_msgs::msg::EnvironmentState forbidden(::environment_msgs::msg::EnvironmentState::_forbidden_type arg)
  {
    msg_.forbidden = std::move(arg);
    return std::move(msg_);
  }

private:
  ::environment_msgs::msg::EnvironmentState msg_;
};

class Init_EnvironmentState_data
{
public:
  explicit Init_EnvironmentState_data(::environment_msgs::msg::EnvironmentState & msg)
  : msg_(msg)
  {}
  Init_EnvironmentState_forbidden data(::environment_msgs::msg::EnvironmentState::_data_type arg)
  {
    msg_.data = std::move(arg);
    return Init_EnvironmentState_forbidden(msg_);
  }

private:
  ::environment_msgs::msg::EnvironmentState msg_;
};

class Init_EnvironmentState_height
{
public:
  explicit Init_EnvironmentState_height(::environment_msgs::msg::EnvironmentState & msg)
  : msg_(msg)
  {}
  Init_EnvironmentState_data height(::environment_msgs::msg::EnvironmentState::_height_type arg)
  {
    msg_.height = std::move(arg);
    return Init_EnvironmentState_data(msg_);
  }

private:
  ::environment_msgs::msg::EnvironmentState msg_;
};

class Init_EnvironmentState_width
{
public:
  explicit Init_EnvironmentState_width(::environment_msgs::msg::EnvironmentState & msg)
  : msg_(msg)
  {}
  Init_EnvironmentState_height width(::environment_msgs::msg::EnvironmentState::_width_type arg)
  {
    msg_.width = std::move(arg);
    return Init_EnvironmentState_height(msg_);
  }

private:
  ::environment_msgs::msg::EnvironmentState msg_;
};

class Init_EnvironmentState_step
{
public:
  Init_EnvironmentState_step()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_EnvironmentState_width step(::environment_msgs::msg::EnvironmentState::_step_type arg)
  {
    msg_.step = std::move(arg);
    return Init_EnvironmentState_width(msg_);
  }

private:
  ::environment_msgs::msg::EnvironmentState msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::environment_msgs::msg::EnvironmentState>()
{
  return environment_msgs::msg::builder::Init_EnvironmentState_step();
}

}  // namespace environment_msgs

#endif  // ENVIRONMENT_MSGS__MSG__DETAIL__ENVIRONMENT_STATE__BUILDER_HPP_
