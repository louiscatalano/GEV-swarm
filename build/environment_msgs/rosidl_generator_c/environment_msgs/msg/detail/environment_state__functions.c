// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from environment_msgs:msg/EnvironmentState.idl
// generated code does not contain a copyright notice
#include "environment_msgs/msg/detail/environment_state__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `data`
// Member `forbidden`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
environment_msgs__msg__EnvironmentState__init(environment_msgs__msg__EnvironmentState * msg)
{
  if (!msg) {
    return false;
  }
  // step
  // width
  // height
  // data
  if (!rosidl_runtime_c__float__Sequence__init(&msg->data, 0)) {
    environment_msgs__msg__EnvironmentState__fini(msg);
    return false;
  }
  // forbidden
  if (!rosidl_runtime_c__boolean__Sequence__init(&msg->forbidden, 0)) {
    environment_msgs__msg__EnvironmentState__fini(msg);
    return false;
  }
  return true;
}

void
environment_msgs__msg__EnvironmentState__fini(environment_msgs__msg__EnvironmentState * msg)
{
  if (!msg) {
    return;
  }
  // step
  // width
  // height
  // data
  rosidl_runtime_c__float__Sequence__fini(&msg->data);
  // forbidden
  rosidl_runtime_c__boolean__Sequence__fini(&msg->forbidden);
}

bool
environment_msgs__msg__EnvironmentState__are_equal(const environment_msgs__msg__EnvironmentState * lhs, const environment_msgs__msg__EnvironmentState * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // step
  if (lhs->step != rhs->step) {
    return false;
  }
  // width
  if (lhs->width != rhs->width) {
    return false;
  }
  // height
  if (lhs->height != rhs->height) {
    return false;
  }
  // data
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->data), &(rhs->data)))
  {
    return false;
  }
  // forbidden
  if (!rosidl_runtime_c__boolean__Sequence__are_equal(
      &(lhs->forbidden), &(rhs->forbidden)))
  {
    return false;
  }
  return true;
}

bool
environment_msgs__msg__EnvironmentState__copy(
  const environment_msgs__msg__EnvironmentState * input,
  environment_msgs__msg__EnvironmentState * output)
{
  if (!input || !output) {
    return false;
  }
  // step
  output->step = input->step;
  // width
  output->width = input->width;
  // height
  output->height = input->height;
  // data
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->data), &(output->data)))
  {
    return false;
  }
  // forbidden
  if (!rosidl_runtime_c__boolean__Sequence__copy(
      &(input->forbidden), &(output->forbidden)))
  {
    return false;
  }
  return true;
}

environment_msgs__msg__EnvironmentState *
environment_msgs__msg__EnvironmentState__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  environment_msgs__msg__EnvironmentState * msg = (environment_msgs__msg__EnvironmentState *)allocator.allocate(sizeof(environment_msgs__msg__EnvironmentState), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(environment_msgs__msg__EnvironmentState));
  bool success = environment_msgs__msg__EnvironmentState__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
environment_msgs__msg__EnvironmentState__destroy(environment_msgs__msg__EnvironmentState * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    environment_msgs__msg__EnvironmentState__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
environment_msgs__msg__EnvironmentState__Sequence__init(environment_msgs__msg__EnvironmentState__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  environment_msgs__msg__EnvironmentState * data = NULL;

  if (size) {
    data = (environment_msgs__msg__EnvironmentState *)allocator.zero_allocate(size, sizeof(environment_msgs__msg__EnvironmentState), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = environment_msgs__msg__EnvironmentState__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        environment_msgs__msg__EnvironmentState__fini(&data[i - 1]);
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
environment_msgs__msg__EnvironmentState__Sequence__fini(environment_msgs__msg__EnvironmentState__Sequence * array)
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
      environment_msgs__msg__EnvironmentState__fini(&array->data[i]);
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

environment_msgs__msg__EnvironmentState__Sequence *
environment_msgs__msg__EnvironmentState__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  environment_msgs__msg__EnvironmentState__Sequence * array = (environment_msgs__msg__EnvironmentState__Sequence *)allocator.allocate(sizeof(environment_msgs__msg__EnvironmentState__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = environment_msgs__msg__EnvironmentState__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
environment_msgs__msg__EnvironmentState__Sequence__destroy(environment_msgs__msg__EnvironmentState__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    environment_msgs__msg__EnvironmentState__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
environment_msgs__msg__EnvironmentState__Sequence__are_equal(const environment_msgs__msg__EnvironmentState__Sequence * lhs, const environment_msgs__msg__EnvironmentState__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!environment_msgs__msg__EnvironmentState__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
environment_msgs__msg__EnvironmentState__Sequence__copy(
  const environment_msgs__msg__EnvironmentState__Sequence * input,
  environment_msgs__msg__EnvironmentState__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(environment_msgs__msg__EnvironmentState);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    environment_msgs__msg__EnvironmentState * data =
      (environment_msgs__msg__EnvironmentState *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!environment_msgs__msg__EnvironmentState__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          environment_msgs__msg__EnvironmentState__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!environment_msgs__msg__EnvironmentState__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
