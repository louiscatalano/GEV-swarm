// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from environment_msgs:msg/LocalMapUpdate.idl
// generated code does not contain a copyright notice

#include "environment_msgs/msg/detail/local_map_update__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_environment_msgs
const rosidl_type_hash_t *
environment_msgs__msg__LocalMapUpdate__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xf8, 0xab, 0xc6, 0x19, 0x48, 0x60, 0xf2, 0xcb,
      0xc9, 0x41, 0xa4, 0xab, 0xfd, 0x63, 0x96, 0xdd,
      0xcd, 0x07, 0x3d, 0xf0, 0xe7, 0x92, 0x1f, 0x1a,
      0x36, 0x56, 0xfd, 0xad, 0x22, 0xf6, 0xe7, 0xe0,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char environment_msgs__msg__LocalMapUpdate__TYPE_NAME[] = "environment_msgs/msg/LocalMapUpdate";

// Define type names, field names, and default values
static char environment_msgs__msg__LocalMapUpdate__FIELD_NAME__agent_id[] = "agent_id";
static char environment_msgs__msg__LocalMapUpdate__FIELD_NAME__i[] = "i";
static char environment_msgs__msg__LocalMapUpdate__FIELD_NAME__j[] = "j";
static char environment_msgs__msg__LocalMapUpdate__FIELD_NAME__value[] = "value";

static rosidl_runtime_c__type_description__Field environment_msgs__msg__LocalMapUpdate__FIELDS[] = {
  {
    {environment_msgs__msg__LocalMapUpdate__FIELD_NAME__agent_id, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {environment_msgs__msg__LocalMapUpdate__FIELD_NAME__i, 1, 1},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {environment_msgs__msg__LocalMapUpdate__FIELD_NAME__j, 1, 1},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {environment_msgs__msg__LocalMapUpdate__FIELD_NAME__value, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
environment_msgs__msg__LocalMapUpdate__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {environment_msgs__msg__LocalMapUpdate__TYPE_NAME, 35, 35},
      {environment_msgs__msg__LocalMapUpdate__FIELDS, 4, 4},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "int32 agent_id\n"
  "int32 i\n"
  "int32 j\n"
  "float32 value";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
environment_msgs__msg__LocalMapUpdate__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {environment_msgs__msg__LocalMapUpdate__TYPE_NAME, 35, 35},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 45, 45},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
environment_msgs__msg__LocalMapUpdate__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *environment_msgs__msg__LocalMapUpdate__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
