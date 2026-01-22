// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from environment_msgs:msg/PredictedMap.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "environment_msgs/msg/predicted_map.hpp"


#ifndef ENVIRONMENT_MSGS__MSG__DETAIL__PREDICTED_MAP__TRAITS_HPP_
#define ENVIRONMENT_MSGS__MSG__DETAIL__PREDICTED_MAP__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "environment_msgs/msg/detail/predicted_map__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace environment_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const PredictedMap & msg,
  std::ostream & out)
{
  out << "{";
  // member: height
  {
    out << "height: ";
    rosidl_generator_traits::value_to_yaml(msg.height, out);
    out << ", ";
  }

  // member: width
  {
    out << "width: ";
    rosidl_generator_traits::value_to_yaml(msg.width, out);
    out << ", ";
  }

  // member: data
  {
    if (msg.data.size() == 0) {
      out << "data: []";
    } else {
      out << "data: [";
      size_t pending_items = msg.data.size();
      for (auto item : msg.data) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const PredictedMap & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: height
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "height: ";
    rosidl_generator_traits::value_to_yaml(msg.height, out);
    out << "\n";
  }

  // member: width
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "width: ";
    rosidl_generator_traits::value_to_yaml(msg.width, out);
    out << "\n";
  }

  // member: data
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.data.size() == 0) {
      out << "data: []\n";
    } else {
      out << "data:\n";
      for (auto item : msg.data) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const PredictedMap & msg, bool use_flow_style = false)
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
  const environment_msgs::msg::PredictedMap & msg,
  std::ostream & out, size_t indentation = 0)
{
  environment_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use environment_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const environment_msgs::msg::PredictedMap & msg)
{
  return environment_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<environment_msgs::msg::PredictedMap>()
{
  return "environment_msgs::msg::PredictedMap";
}

template<>
inline const char * name<environment_msgs::msg::PredictedMap>()
{
  return "environment_msgs/msg/PredictedMap";
}

template<>
struct has_fixed_size<environment_msgs::msg::PredictedMap>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<environment_msgs::msg::PredictedMap>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<environment_msgs::msg::PredictedMap>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ENVIRONMENT_MSGS__MSG__DETAIL__PREDICTED_MAP__TRAITS_HPP_
