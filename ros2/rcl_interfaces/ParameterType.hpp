#ifndef _RCL_INTERFACES_PARAMETERTYPE_H_
#define _RCL_INTERFACES_PARAMETERTYPE_H_

#include "../topic.hpp"

// Manualy include list

namespace rcl_interfaces
{

enum
{
    PARAMETER_NOT_SET = 0,
    PARAMETER_BOOL = 1,
    PARAMETER_INTEGER = 2,
    PARAMETER_DOUBLE = 3,
    PARAMETER_STRING = 4,
    PARAMETER_BYTE_ARRAY = 5,
    PARAMETER_BOOL_ARRAY = 6,
    PARAMETER_INTEGER_ARRAY = 7,
    PARAMETER_DOUBLE_ARRAY = 8,
    PARAMETER_STRING_ARRAY = 9
};

class ParameterType: public ros2::Topic<ParameterType>
{
public:
    uint8_t structure_needs_at_least_one_member;

    ParameterType()
        : Topic("rcl_interfaces::msg::dds_::ParameterType_", "ParameterType", RCL_INTERFACES_PARAMETERTYPE_ID),
        structure_needs_at_least_one_member(0)
    {
    }

    bool serialize(void* msg_buf, ParameterType* topic)
    {
        ucdrBuffer* writer = (ucdrBuffer*)msg_buf;
        (void) ucdr_serialize_uint8_t(writer, topic->structure_needs_at_least_one_member);

        return !writer->error;
    }

    bool deserialize(void* msg_buf, ParameterType* topic)
    {
        ucdrBuffer* reader = (ucdrBuffer*)msg_buf;
        (void) ucdr_deserialize_uint8_t(reader, &topic->structure_needs_at_least_one_member);

        return !reader->error;
    }

    uint32_t size_of_topic(const ParameterType* topic, uint32_t size)
    {
        (void) (topic);

        uint32_t previousSize = size;
        size += ucdr_alignment(size, 1) + 1;

        return size - previousSize;
    }

};

} // namespace rcl_interfaces

#endif // _RCL_INTERFACES_PARAMETERTYPE_H_