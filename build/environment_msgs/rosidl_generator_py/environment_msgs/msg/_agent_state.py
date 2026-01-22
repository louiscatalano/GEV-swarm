# generated from rosidl_generator_py/resource/_idl.py.em
# with input from environment_msgs:msg/AgentState.idl
# generated code does not contain a copyright notice

# This is being done at the module level and not on the instance level to avoid looking
# for the same variable multiple times on each instance. This variable is not supposed to
# change during runtime so it makes sense to only look for it once.
from os import getenv

ros_python_check_fields = getenv('ROS_PYTHON_CHECK_FIELDS', default='')


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_AgentState(type):
    """Metaclass of message 'AgentState'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('environment_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'environment_msgs.msg.AgentState')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__agent_state
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__agent_state
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__agent_state
            cls._TYPE_SUPPORT = module.type_support_msg__msg__agent_state
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__agent_state

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class AgentState(metaclass=Metaclass_AgentState):
    """Message class 'AgentState'."""

    __slots__ = [
        '_agent_id',
        '_i',
        '_j',
        '_intent_i',
        '_intent_j',
        '_check_fields',
    ]

    _fields_and_field_types = {
        'agent_id': 'int32',
        'i': 'int32',
        'j': 'int32',
        'intent_i': 'int32',
        'intent_j': 'int32',
    }

    # This attribute is used to store an rosidl_parser.definition variable
    # related to the data type of each of the components the message.
    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        if 'check_fields' in kwargs:
            self._check_fields = kwargs['check_fields']
        else:
            self._check_fields = ros_python_check_fields == '1'
        if self._check_fields:
            assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
                'Invalid arguments passed to constructor: %s' % \
                ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.agent_id = kwargs.get('agent_id', int())
        self.i = kwargs.get('i', int())
        self.j = kwargs.get('j', int())
        self.intent_i = kwargs.get('intent_i', int())
        self.intent_j = kwargs.get('intent_j', int())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.get_fields_and_field_types().keys(), self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    if self._check_fields:
                        assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.agent_id != other.agent_id:
            return False
        if self.i != other.i:
            return False
        if self.j != other.j:
            return False
        if self.intent_i != other.intent_i:
            return False
        if self.intent_j != other.intent_j:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def agent_id(self):
        """Message field 'agent_id'."""
        return self._agent_id

    @agent_id.setter
    def agent_id(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'agent_id' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'agent_id' field must be an integer in [-2147483648, 2147483647]"
        self._agent_id = value

    @builtins.property
    def i(self):
        """Message field 'i'."""
        return self._i

    @i.setter
    def i(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'i' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'i' field must be an integer in [-2147483648, 2147483647]"
        self._i = value

    @builtins.property
    def j(self):
        """Message field 'j'."""
        return self._j

    @j.setter
    def j(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'j' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'j' field must be an integer in [-2147483648, 2147483647]"
        self._j = value

    @builtins.property
    def intent_i(self):
        """Message field 'intent_i'."""
        return self._intent_i

    @intent_i.setter
    def intent_i(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'intent_i' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'intent_i' field must be an integer in [-2147483648, 2147483647]"
        self._intent_i = value

    @builtins.property
    def intent_j(self):
        """Message field 'intent_j'."""
        return self._intent_j

    @intent_j.setter
    def intent_j(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'intent_j' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'intent_j' field must be an integer in [-2147483648, 2147483647]"
        self._intent_j = value
