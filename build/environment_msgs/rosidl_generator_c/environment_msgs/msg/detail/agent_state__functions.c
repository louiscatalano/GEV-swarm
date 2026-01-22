// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from environment_msgs:msg/AgentState.idl
// generated code does not contain a copyright notice
#include "environment_msgs/msg/detail/agent_state__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
environment_msgs__msg__AgentState__init(environment_msgs__msg__AgentState * msg)
{
  if (!msg) {
    return false;
  }
  // agent_id
  // i
  // j
  // intent_i
  // intent_j
  return true;
}

void
environment_msgs__msg__AgentState__fini(environment_msgs__msg__AgentState * msg)
{
  if (!msg) {
    return;
  }
  // agent_id
  // i
  // j
  // intent_i
  // intent_j
}

bool
environment_msgs__msg__AgentState__are_equal(const environment_msgs__msg__AgentState * lhs, const environment_msgs__msg__AgentState * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // agent_id
  if (lhs->agent_id != rhs->agent_id) {
    return false;
  }
  // i
  if (lhs->i != rhs->i) {
    return false;
  }
  // j
  if (lhs->j != rhs->j) {
    return false;
  }
  // intent_i
  if (lhs->intent_i != rhs->intent_i) {
    return false;
  }
  // intent_j
  if (lhs->intent_j != rhs->intent_j) {
    return false;
  }
  return true;
}

bool
environment_msgs__msg__AgentState__copy(
  const environment_msgs__msg__AgentState * input,
  environment_msgs__msg__AgentState * output)
{
  if (!input || !output) {
    return false;
  }
  // agent_id
  output->agent_id = input->agent_id;
  // i
  output->i = input->i;
  // j
  output->j = input->j;
  // intent_i
  output->intent_i = input->intent_i;
  // intent_j
  output->intent_j = input->intent_j;
  return true;
}

environment_msgs__msg__AgentState *
environment_msgs__msg__AgentState__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  environment_msgs__msg__AgentState * msg = (environment_msgs__msg__AgentState *)allocator.allocate(sizeof(environment_msgs__msg__AgentState), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(environment_msgs__msg__AgentState));
  bool success = environment_msgs__msg__AgentState__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
environment_msgs__msg__AgentState__destroy(environment_msgs__msg__AgentState * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    environment_msgs__msg__AgentState__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
environment_msgs__msg__AgentState__Sequence__init(environment_msgs__msg__AgentState__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  environment_msgs__msg__AgentState * data = NULL;

  if (size) {
    data = (environment_msgs__msg__AgentState *)allocator.zero_allocate(size, sizeof(environment_msgs__msg__AgentState), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = environment_msgs__msg__AgentState__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        environment_msgs__msg__AgentState__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
environment_msgs__msg__AgentState__Sequence__fini(environment_msgs__msg__AgentState__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      environment_msgs__msg__AgentState__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

environment_msgs__msg__AgentState__Sequence *
environment_msgs__msg__AgentState__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  environment_msgs__msg__AgentState__Sequence * array = (environment_msgs__msg__AgentState__Sequence *)allocator.allocate(sizeof(environment_msgs__msg__AgentState__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = environment_msgs__msg__AgentState__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
environment_msgs__msg__AgentState__Sequence__destroy(environment_msgs__msg__AgentState__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    environment_msgs__msg__AgentState__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
environment_msgs__msg__AgentState__Sequence__are_equal(const environment_msgs__msg__AgentState__Sequence * lhs, const environment_msgs__msg__AgentState__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!environment_msgs__msg__AgentState__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
environment_msgs__msg__AgentState__Sequence__copy(
  const environment_msgs__msg__AgentState__Sequence * input,
  environment_msgs__msg__AgentState__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(environment_msgs__msg__AgentState);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    environment_msgs__msg__AgentState * data =
      (environment_msgs__msg__AgentState *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!environment_msgs__msg__AgentState__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          environment_msgs__msg__AgentState__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!environment_msgs__msg__AgentState__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
