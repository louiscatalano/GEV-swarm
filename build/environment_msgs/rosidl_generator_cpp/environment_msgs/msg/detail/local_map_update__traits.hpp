// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from environment_msgs:msg/LocalMapUpdate.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "environment_msgs/msg/local_map_update.hpp"


#ifndef ENVIRONMENT_MSGS__MSG__DETAIL__LOCAL_MAP_UPDATE__TRAITS_HPP_
#define ENVIRONMENT_MSGS__MSG__DETAIL__LOCAL_MAP_UPDATE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "environment_msgs/msg/detail/local_map_update__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace environment_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const LocalMapUpdate & msg,
  std::ostream & out)
{
  out << "{";
  // member: agent_id
  {
    out << "agent_id: ";
    rosidl_generator_traits::value_to_yaml(msg.agent_id, out);
    out << ", ";
  }

  // member: i
  {
    out << "i: ";
    rosidl_generator_traits::value_to_yaml(msg.i, out);
    out << ", ";
  }

  // member: j
  {
    out << "j: ";
    rosidl_generator_traits::value_to_yaml(msg.j, out);
    out << ", ";
  }

  // member: value
  {
    out << "value: ";
    rosidl_generator_traits::value_to_yaml(msg.value, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LocalMapUpdate & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: agent_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "agent_id: ";
    rosidl_generator_traits::value_to_yaml(msg.agent_id, out);
    out << "\n";
  }

  // member: i
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "i: ";
    rosidl_generator_traits::value_to_yaml(msg.i, out);
    out << "\n";
  }

  // member: j
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "j: ";
    rosidl_generator_traits::value_to_yaml(msg.j, out);
    out << "\n";
  }

  // member: value
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "value: ";
    rosidl_generator_traits::value_to_yaml(msg.value, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LocalMapUpdate & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace environment_msgs

namespace rosidl_generator_traits
{

[[deprecated("use environment_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const environment_msgs::msg::LocalMapUpdate & msg,
  std::ostream & out, size_t indentation = 0)
{
  environment_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use environment_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const environment_msgs::msg::LocalMapUpdate & msg)
{
  return environment_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<environment_msgs::msg::LocalMapUpdate>()
{
  return "environment_msgs::msg::LocalMapUpdate";
}

template<>
inline const char * name<environment_msgs::msg::LocalMapUpdate>()
{
  return "environment_msgs/msg/LocalMapUpdate";
}

template<>
struct has_fixed_size<environment_msgs::msg::LocalMapUpdate>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<environment_msgs::msg::LocalMapUpdate>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<environment_msgs::msg::LocalMapUpdate>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ENVIRONMENT_MSGS__MSG__DETAIL__LOCAL_MAP_UPDATE__TRAITS_HPP_
