// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from environment_msgs:msg/PredictedMap.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "environment_msgs/msg/predicted_map.hpp"


#ifndef ENVIRONMENT_MSGS__MSG__DETAIL__PREDICTED_MAP__BUILDER_HPP_
#define ENVIRONMENT_MSGS__MSG__DETAIL__PREDICTED_MAP__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "environment_msgs/msg/detail/predicted_map__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace environment_msgs
{

namespace msg
{

namespace builder
{

class Init_PredictedMap_data
{
public:
  explicit Init_PredictedMap_data(::environment_msgs::msg::PredictedMap & msg)
  : msg_(msg)
  {}
  ::environment_msgs::msg::PredictedMap data(::environment_msgs::msg::PredictedMap::_data_type arg)
  {
    msg_.data = std::move(arg);
    return std::move(msg_);
  }

private:
  ::environment_msgs::msg::PredictedMap msg_;
};

class Init_PredictedMap_width
{
public:
  explicit Init_PredictedMap_width(::environment_msgs::msg::PredictedMap & msg)
  : msg_(msg)
  {}
  Init_PredictedMap_data width(::environment_msgs::msg::PredictedMap::_width_type arg)
  {
    msg_.width = std::move(arg);
    return Init_PredictedMap_data(msg_);
  }

private:
  ::environment_msgs::msg::PredictedMap msg_;
};

class Init_PredictedMap_height
{
public:
  Init_PredictedMap_height()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PredictedMap_width height(::environment_msgs::msg::PredictedMap::_height_type arg)
  {
    msg_.height = std::move(arg);
    return Init_PredictedMap_width(msg_);
  }

private:
  ::environment_msgs::msg::PredictedMap msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::environment_msgs::msg::PredictedMap>()
{
  return environment_msgs::msg::builder::Init_PredictedMap_height();
}

}  // namespace environment_msgs

#endif  // ENVIRONMENT_MSGS__MSG__DETAIL__PREDICTED_MAP__BUILDER_HPP_
