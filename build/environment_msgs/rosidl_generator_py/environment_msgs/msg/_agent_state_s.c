// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from environment_msgs:msg/AgentState.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "environment_msgs/msg/detail/agent_state__struct.h"
#include "environment_msgs/msg/detail/agent_state__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool environment_msgs__msg__agent_state__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
    if (class_attr == NULL) {
      return false;
    }
    PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
    if (name_attr == NULL) {
      Py_DECREF(class_attr);
      return false;
    }
    PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
    if (module_attr == NULL) {
      Py_DECREF(name_attr);
      Py_DECREF(class_attr);
      return false;
    }

    // PyUnicode_1BYTE_DATA is just a cast
    assert(strncmp("environment_msgs.msg._agent_state", (char *)PyUnicode_1BYTE_DATA(module_attr), 33) == 0);
    assert(strncmp("AgentState", (char *)PyUnicode_1BYTE_DATA(name_attr), 10) == 0);

    Py_DECREF(module_attr);
    Py_DECREF(name_attr);
    Py_DECREF(class_attr);
  }
  environment_msgs__msg__AgentState * ros_message = _ros_message;
  {  // agent_id
    PyObject * field = PyObject_GetAttrString(_pymsg, "agent_id");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->agent_id = (int32_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // i
    PyObject * field = PyObject_GetAttrString(_pymsg, "i");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->i = (int32_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // j
    PyObject * field = PyObject_GetAttrString(_pymsg, "j");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->j = (int32_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // intent_i
    PyObject * field = PyObject_GetAttrString(_pymsg, "intent_i");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->intent_i = (int32_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // intent_j
    PyObject * field = PyObject_GetAttrString(_pymsg, "intent_j");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->intent_j = (int32_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * environment_msgs__msg__agent_state__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of AgentState */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("environment_msgs.msg._agent_state");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "AgentState");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  environment_msgs__msg__AgentState * ros_message = (environment_msgs__msg__AgentState *)raw_ros_message;
  {  // agent_id
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->agent_id);
    {
      int rc = PyObject_SetAttrString(_pymessage, "agent_id", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // i
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->i);
    {
      int rc = PyObject_SetAttrString(_pymessage, "i", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // j
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->j);
    {
      int rc = PyObject_SetAttrString(_pymessage, "j", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // intent_i
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->intent_i);
    {
      int rc = PyObject_SetAttrString(_pymessage, "intent_i", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // intent_j
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->intent_j);
    {
      int rc = PyObject_SetAttrString(_pymessage, "intent_j", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
