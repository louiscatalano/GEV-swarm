// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from environment_msgs:msg/EnvironmentState.idl
// generated code does not contain a copyright notice

#include "environment_msgs/msg/detail/environment_state__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_environment_msgs
const rosidl_type_hash_t *
environment_msgs__msg__EnvironmentState__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x45, 0xff, 0x79, 0xdd, 0xe8, 0x09, 0x98, 0xd9,
      0x63, 0x9b, 0x84, 0xa4, 0x23, 0x79, 0x32, 0x3b,
      0xe5, 0xe9, 0xc3, 0x09, 0x88, 0x73, 0xe8, 0x53,
      0x8e, 0x58, 0x20, 0xf4, 0x62, 0x91, 0x22, 0xd4,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char environment_msgs__msg__EnvironmentState__TYPE_NAME[] = "environment_msgs/msg/EnvironmentState";

// Define type names, field names, and default values
static char environment_msgs__msg__EnvironmentState__FIELD_NAME__step[] = "step";
static char environment_msgs__msg__EnvironmentState__FIELD_NAME__width[] = "width";
static char environment_msgs__msg__EnvironmentState__FIELD_NAME__height[] = "height";
static char environment_msgs__msg__EnvironmentState__FIELD_NAME__data[] = "data";
static char environment_msgs__msg__EnvironmentState__FIELD_NAME__forbidden[] = "forbidden";

static rosidl_runtime_c__type_description__Field environment_msgs__msg__EnvironmentState__FIELDS[] = {
  {
    {environment_msgs__msg__EnvironmentState__FIELD_NAME__step, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {environment_msgs__msg__EnvironmentState__FIELD_NAME__width, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {environment_msgs__msg__EnvironmentState__FIELD_NAME__height, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {environment_msgs__msg__EnvironmentState__FIELD_NAME__data, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT_UNBOUNDED_SEQUENCE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {environment_msgs__msg__EnvironmentState__FIELD_NAME__forbidden, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN_UNBOUNDED_SEQUENCE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
environment_msgs__msg__EnvironmentState__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {environment_msgs__msg__EnvironmentState__TYPE_NAME, 37, 37},
      {environment_msgs__msg__EnvironmentState__FIELDS, 5, 5},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "int32 step\n"
  "int32 width\n"
  "int32 height\n"
  "float32[] data\n"
  "bool[] forbidden";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
environment_msgs__msg__EnvironmentState__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {environment_msgs__msg__EnvironmentState__TYPE_NAME, 37, 37},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 68, 68},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
environment_msgs__msg__EnvironmentState__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *environment_msgs__msg__EnvironmentState__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
