// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from environment_msgs:msg/AgentState.idl
// generated code does not contain a copyright notice

#include "environment_msgs/msg/detail/agent_state__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_environment_msgs
const rosidl_type_hash_t *
environment_msgs__msg__AgentState__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x3e, 0x72, 0x8c, 0xb0, 0xc7, 0xa5, 0x80, 0x23,
      0x4a, 0x07, 0xa9, 0xe0, 0x74, 0xaa, 0x7f, 0x49,
      0x92, 0x64, 0x14, 0x23, 0x89, 0x79, 0x64, 0xbc,
      0x82, 0x98, 0x3f, 0x97, 0xd4, 0x31, 0x44, 0x10,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char environment_msgs__msg__AgentState__TYPE_NAME[] = "environment_msgs/msg/AgentState";

// Define type names, field names, and default values
static char environment_msgs__msg__AgentState__FIELD_NAME__agent_id[] = "agent_id";
static char environment_msgs__msg__AgentState__FIELD_NAME__i[] = "i";
static char environment_msgs__msg__AgentState__FIELD_NAME__j[] = "j";
static char environment_msgs__msg__AgentState__FIELD_NAME__intent_i[] = "intent_i";
static char environment_msgs__msg__AgentState__FIELD_NAME__intent_j[] = "intent_j";

static rosidl_runtime_c__type_description__Field environment_msgs__msg__AgentState__FIELDS[] = {
  {
    {environment_msgs__msg__AgentState__FIELD_NAME__agent_id, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {environment_msgs__msg__AgentState__FIELD_NAME__i, 1, 1},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {environment_msgs__msg__AgentState__FIELD_NAME__j, 1, 1},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {environment_msgs__msg__AgentState__FIELD_NAME__intent_i, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {environment_msgs__msg__AgentState__FIELD_NAME__intent_j, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
environment_msgs__msg__AgentState__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {environment_msgs__msg__AgentState__TYPE_NAME, 31, 31},
      {environment_msgs__msg__AgentState__FIELDS, 5, 5},
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
  "int32 intent_i\n"
  "int32 intent_j";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
environment_msgs__msg__AgentState__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {environment_msgs__msg__AgentState__TYPE_NAME, 31, 31},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 61, 61},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
environment_msgs__msg__AgentState__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *environment_msgs__msg__AgentState__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
