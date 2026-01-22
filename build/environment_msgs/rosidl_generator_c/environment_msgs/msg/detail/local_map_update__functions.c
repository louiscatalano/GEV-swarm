// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from environment_msgs:msg/LocalMapUpdate.idl
// generated code does not contain a copyright notice
#include "environment_msgs/msg/detail/local_map_update__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
environment_msgs__msg__LocalMapUpdate__init(environment_msgs__msg__LocalMapUpdate * msg)
{
  if (!msg) {
    return false;
  }
  // agent_id
  // i
  // j
  // value
  return true;
}

void
environment_msgs__msg__LocalMapUpdate__fini(environment_msgs__msg__LocalMapUpdate * msg)
{
  if (!msg) {
    return;
  }
  // agent_id
  // i
  // j
  // value
}

bool
environment_msgs__msg__LocalMapUpdate__are_equal(const environment_msgs__msg__LocalMapUpdate * lhs, const environment_msgs__msg__LocalMapUpdate * rhs)
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
  // value
  if (lhs->value != rhs->value) {
    return false;
  }
  return true;
}

bool
environment_msgs__msg__LocalMapUpdate__copy(
  const environment_msgs__msg__LocalMapUpdate * input,
  environment_msgs__msg__LocalMapUpdate * output)
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
  // value
  output->value = input->value;
  return true;
}

environment_msgs__msg__LocalMapUpdate *
environment_msgs__msg__LocalMapUpdate__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  environment_msgs__msg__LocalMapUpdate * msg = (environment_msgs__msg__LocalMapUpdate *)allocator.allocate(sizeof(environment_msgs__msg__LocalMapUpdate), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(environment_msgs__msg__LocalMapUpdate));
  bool success = environment_msgs__msg__LocalMapUpdate__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
environment_msgs__msg__LocalMapUpdate__destroy(environment_msgs__msg__LocalMapUpdate * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    environment_msgs__msg__LocalMapUpdate__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
environment_msgs__msg__LocalMapUpdate__Sequence__init(environment_msgs__msg__LocalMapUpdate__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  environment_msgs__msg__LocalMapUpdate * data = NULL;

  if (size) {
    data = (environment_msgs__msg__LocalMapUpdate *)allocator.zero_allocate(size, sizeof(environment_msgs__msg__LocalMapUpdate), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = environment_msgs__msg__LocalMapUpdate__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        environment_msgs__msg__LocalMapUpdate__fini(&data[i - 1]);
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
environment_msgs__msg__LocalMapUpdate__Sequence__fini(environment_msgs__msg__LocalMapUpdate__Sequence * array)
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
      environment_msgs__msg__LocalMapUpdate__fini(&array->data[i]);
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

environment_msgs__msg__LocalMapUpdate__Sequence *
environment_msgs__msg__LocalMapUpdate__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  environment_msgs__msg__LocalMapUpdate__Sequence * array = (environment_msgs__msg__LocalMapUpdate__Sequence *)allocator.allocate(sizeof(environment_msgs__msg__LocalMapUpdate__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = environment_msgs__msg__LocalMapUpdate__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
environment_msgs__msg__LocalMapUpdate__Sequence__destroy(environment_msgs__msg__LocalMapUpdate__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    environment_msgs__msg__LocalMapUpdate__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
environment_msgs__msg__LocalMapUpdate__Sequence__are_equal(const environment_msgs__msg__LocalMapUpdate__Sequence * lhs, const environment_msgs__msg__LocalMapUpdate__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!environment_msgs__msg__LocalMapUpdate__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
environment_msgs__msg__LocalMapUpdate__Sequence__copy(
  const environment_msgs__msg__LocalMapUpdate__Sequence * input,
  environment_msgs__msg__LocalMapUpdate__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(environment_msgs__msg__LocalMapUpdate);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    environment_msgs__msg__LocalMapUpdate * data =
      (environment_msgs__msg__LocalMapUpdate *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!environment_msgs__msg__LocalMapUpdate__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          environment_msgs__msg__LocalMapUpdate__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!environment_msgs__msg__LocalMapUpdate__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
