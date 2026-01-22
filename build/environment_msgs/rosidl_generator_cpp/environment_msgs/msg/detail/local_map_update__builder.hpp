// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from environment_msgs:msg/LocalMapUpdate.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "environment_msgs/msg/local_map_update.hpp"


#ifndef ENVIRONMENT_MSGS__MSG__DETAIL__LOCAL_MAP_UPDATE__BUILDER_HPP_
#define ENVIRONMENT_MSGS__MSG__DETAIL__LOCAL_MAP_UPDATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "environment_msgs/msg/detail/local_map_update__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace environment_msgs
{

namespace msg
{

namespace builder
{

class Init_LocalMapUpdate_value
{
public:
  explicit Init_LocalMapUpdate_value(::environment_msgs::msg::LocalMapUpdate & msg)
  : msg_(msg)
  {}
  ::environment_msgs::msg::LocalMapUpdate value(::environment_msgs::msg::LocalMapUpdate::_value_type arg)
  {
    msg_.value = std::move(arg);
    return std::move(msg_);
  }

private:
  ::environment_msgs::msg::LocalMapUpdate msg_;
};

class Init_LocalMapUpdate_j
{
public:
  explicit Init_LocalMapUpdate_j(::environment_msgs::msg::LocalMapUpdate & msg)
  : msg_(msg)
  {}
  Init_LocalMapUpdate_value j(::environment_msgs::msg::LocalMapUpdate::_j_type arg)
  {
    msg_.j = std::move(arg);
    return Init_LocalMapUpdate_value(msg_);
  }

private:
  ::environment_msgs::msg::LocalMapUpdate msg_;
};

class Init_LocalMapUpdate_i
{
public:
  explicit Init_LocalMapUpdate_i(::environment_msgs::msg::LocalMapUpdate & msg)
  : msg_(msg)
  {}
  Init_LocalMapUpdate_j i(::environment_msgs::msg::LocalMapUpdate::_i_type arg)
  {
    msg_.i = std::move(arg);
    return Init_LocalMapUpdate_j(msg_);
  }

private:
  ::environment_msgs::msg::LocalMapUpdate msg_;
};

class Init_LocalMapUpdate_agent_id
{
public:
  Init_LocalMapUpdate_agent_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LocalMapUpdate_i agent_id(::environment_msgs::msg::LocalMapUpdate::_agent_id_type arg)
  {
    msg_.agent_id = std::move(arg);
    return Init_LocalMapUpdate_i(msg_);
  }

private:
  ::environment_msgs::msg::LocalMapUpdate msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::environment_msgs::msg::LocalMapUpdate>()
{
  return environment_msgs::msg::builder::Init_LocalMapUpdate_agent_id();
}

}  // namespace environment_msgs

#endif  // ENVIRONMENT_MSGS__MSG__DETAIL__LOCAL_MAP_UPDATE__BUILDER_HPP_
