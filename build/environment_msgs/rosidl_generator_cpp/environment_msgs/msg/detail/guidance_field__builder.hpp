// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from environment_msgs:msg/GuidanceField.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "environment_msgs/msg/guidance_field.hpp"


#ifndef ENVIRONMENT_MSGS__MSG__DETAIL__GUIDANCE_FIELD__BUILDER_HPP_
#define ENVIRONMENT_MSGS__MSG__DETAIL__GUIDANCE_FIELD__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "environment_msgs/msg/detail/guidance_field__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace environment_msgs
{

namespace msg
{

namespace builder
{

class Init_GuidanceField_data
{
public:
  explicit Init_GuidanceField_data(::environment_msgs::msg::GuidanceField & msg)
  : msg_(msg)
  {}
  ::environment_msgs::msg::GuidanceField data(::environment_msgs::msg::GuidanceField::_data_type arg)
  {
    msg_.data = std::move(arg);
    return std::move(msg_);
  }

private:
  ::environment_msgs::msg::GuidanceField msg_;
};

class Init_GuidanceField_height
{
public:
  explicit Init_GuidanceField_height(::environment_msgs::msg::GuidanceField & msg)
  : msg_(msg)
  {}
  Init_GuidanceField_data height(::environment_msgs::msg::GuidanceField::_height_type arg)
  {
    msg_.height = std::move(arg);
    return Init_GuidanceField_data(msg_);
  }

private:
  ::environment_msgs::msg::GuidanceField msg_;
};

class Init_GuidanceField_width
{
public:
  Init_GuidanceField_width()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GuidanceField_height width(::environment_msgs::msg::GuidanceField::_width_type arg)
  {
    msg_.width = std::move(arg);
    return Init_GuidanceField_height(msg_);
  }

private:
  ::environment_msgs::msg::GuidanceField msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::environment_msgs::msg::GuidanceField>()
{
  return environment_msgs::msg::builder::Init_GuidanceField_width();
}

}  // namespace environment_msgs

#endif  // ENVIRONMENT_MSGS__MSG__DETAIL__GUIDANCE_FIELD__BUILDER_HPP_
