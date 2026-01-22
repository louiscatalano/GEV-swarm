// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from environment_msgs:msg/PredictedMap.idl
// generated code does not contain a copyright notice

#include "environment_msgs/msg/detail/predicted_map__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_environment_msgs
const rosidl_type_hash_t *
environment_msgs__msg__PredictedMap__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x2c, 0xc5, 0xc3, 0xb6, 0x02, 0x8f, 0x6c, 0x93,
      0x92, 0xc5, 0xad, 0x7c, 0x55, 0xe5, 0xa0, 0xed,
      0x5f, 0xc1, 0x51, 0x61, 0x58, 0x04, 0x3a, 0x0a,
      0xdd, 0x71, 0x57, 0x52, 0x5a, 0x96, 0xa3, 0xa5,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char environment_msgs__msg__PredictedMap__TYPE_NAME[] = "environment_msgs/msg/PredictedMap";

// Define type names, field names, and default values
static char environment_msgs__msg__PredictedMap__FIELD_NAME__height[] = "height";
static char environment_msgs__msg__PredictedMap__FIELD_NAME__width[] = "width";
static char environment_msgs__msg__PredictedMap__FIELD_NAME__data[] = "data";

static rosidl_runtime_c__type_description__Field environment_msgs__msg__PredictedMap__FIELDS[] = {
  {
    {environment_msgs__msg__PredictedMap__FIELD_NAME__height, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {environment_msgs__msg__PredictedMap__FIELD_NAME__width, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {environment_msgs__msg__PredictedMap__FIELD_NAME__data, 4, 4},
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
environment_msgs__msg__PredictedMap__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {environment_msgs__msg__PredictedMap__TYPE_NAME, 33, 33},
      {environment_msgs__msg__PredictedMap__FIELDS, 3, 3},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "int32 height\n"
  "int32 width\n"
  "float32[] data";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
environment_msgs__msg__PredictedMap__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {environment_msgs__msg__PredictedMap__TYPE_NAME, 33, 33},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 40, 40},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
environment_msgs__msg__PredictedMap__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *environment_msgs__msg__PredictedMap__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
