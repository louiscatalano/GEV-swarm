// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from environment_msgs:msg/AgentState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "environment_msgs/msg/agent_state.hpp"


#ifndef ENVIRONMENT_MSGS__MSG__DETAIL__AGENT_STATE__BUILDER_HPP_
#define ENVIRONMENT_MSGS__MSG__DETAIL__AGENT_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "environment_msgs/msg/detail/agent_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace environment_msgs
{

namespace msg
{

namespace builder
{

class Init_AgentState_intent_j
{
public:
  explicit Init_AgentState_intent_j(::environment_msgs::msg::AgentState & msg)
  : msg_(msg)
  {}
  ::environment_msgs::msg::AgentState intent_j(::environment_msgs::msg::AgentState::_intent_j_type arg)
  {
    msg_.intent_j = std::move(arg);
    return std::move(msg_);
  }

private:
  ::environment_msgs::msg::AgentState msg_;
};

class Init_AgentState_intent_i
{
public:
  explicit Init_AgentState_intent_i(::environment_msgs::msg::AgentState & msg)
  : msg_(msg)
  {}
  Init_AgentState_intent_j intent_i(::environment_msgs::msg::AgentState::_intent_i_type arg)
  {
    msg_.intent_i = std::move(arg);
    return Init_AgentState_intent_j(msg_);
  }

private:
  ::environment_msgs::msg::AgentState msg_;
};

class Init_AgentState_j
{
public:
  explicit Init_AgentState_j(::environment_msgs::msg::AgentState & msg)
  : msg_(msg)
  {}
  Init_AgentState_intent_i j(::environment_msgs::msg::AgentState::_j_type arg)
  {
    msg_.j = std::move(arg);
    return Init_AgentState_intent_i(msg_);
  }

private:
  ::environment_msgs::msg::AgentState msg_;
};

class Init_AgentState_i
{
public:
  explicit Init_AgentState_i(::environment_msgs::msg::AgentState & msg)
  : msg_(msg)
  {}
  Init_AgentState_j i(::environment_msgs::msg::AgentState::_i_type arg)
  {
    msg_.i = std::move(arg);
    return Init_AgentState_j(msg_);
  }

private:
  ::environment_msgs::msg::AgentState msg_;
};

class Init_AgentState_agent_id
{
public:
  Init_AgentState_agent_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_AgentState_i agent_id(::environment_msgs::msg::AgentState::_agent_id_type arg)
  {
    msg_.agent_id = std::move(arg);
    return Init_AgentState_i(msg_);
  }

private:
  ::environment_msgs::msg::AgentState msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::environment_msgs::msg::AgentState>()
{
  return environment_msgs::msg::builder::Init_AgentState_agent_id();
}

}  // namespace environment_msgs

#endif  // ENVIRONMENT_MSGS__MSG__DETAIL__AGENT_STATE__BUILDER_HPP_
