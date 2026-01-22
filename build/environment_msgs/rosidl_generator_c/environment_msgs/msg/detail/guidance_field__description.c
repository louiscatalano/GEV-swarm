// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from environment_msgs:msg/GuidanceField.idl
// generated code does not contain a copyright notice

#include "environment_msgs/msg/detail/guidance_field__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_environment_msgs
const rosidl_type_hash_t *
environment_msgs__msg__GuidanceField__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x38, 0x97, 0xee, 0x22, 0x38, 0x05, 0xe8, 0x5c,
      0x3f, 0x07, 0xce, 0xc7, 0x70, 0x2c, 0xdc, 0x80,
      0x59, 0x9a, 0xfc, 0xad, 0x27, 0xe9, 0x8d, 0xa3,
      0xd7, 0xb2, 0xc4, 0x55, 0x8f, 0xd2, 0x57, 0x52,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char environment_msgs__msg__GuidanceField__TYPE_NAME[] = "environment_msgs/msg/GuidanceField";

// Define type names, field names, and default values
static char environment_msgs__msg__GuidanceField__FIELD_NAME__width[] = "width";
static char environment_msgs__msg__GuidanceField__FIELD_NAME__height[] = "height";
static char environment_msgs__msg__GuidanceField__FIELD_NAME__data[] = "data";

static rosidl_runtime_c__type_description__Field environment_msgs__msg__GuidanceField__FIELDS[] = {
  {
    {environment_msgs__msg__GuidanceField__FIELD_NAME__width, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {environment_msgs__msg__GuidanceField__FIELD_NAME__height, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {environment_msgs__msg__GuidanceField__FIELD_NAME__data, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT_UNBOUNDED_SEQUENCE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
environment_msgs__msg__GuidanceField__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {environment_msgs__msg__GuidanceField__TYPE_NAME, 34, 34},
      {environment_msgs__msg__GuidanceField__FIELDS, 3, 3},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "int32 width\n"
  "int32 height\n"
  "float32[] data";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
environment_msgs__msg__GuidanceField__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {environment_msgs__msg__GuidanceField__TYPE_NAME, 34, 34},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 40, 40},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
environment_msgs__msg__GuidanceField__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *environment_msgs__msg__GuidanceField__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
