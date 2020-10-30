#ifndef _RCL_INTERFACES_PARAMETERDESCRIPTOR_H_
#define _RCL_INTERFACES_PARAMETERDESCRIPTOR_H_

#include "../topic.hpp"

// Manualy include list
#include "rcl_interfaces/FloatingPointRange.hpp"
#include "rcl_interfaces/IntegerRange.hpp"


namespace rcl_interfaces
{

class ParameterDescriptor: public ros2::Topic<ParameterDescriptor>
{
public:
    char name[255];
    uint8_t type;
    char description[255];
    char additional_constraints[255];
    bool read_only;
    rcl_interfaces::FloatingPointRange floating_point_range[10];
    rcl_interfaces::IntegerRange integer_range[10];

    ParameterDescriptor()
        : Topic("rcl_interfaces::msg::dds_::ParameterDescriptor_", "ParameterDescriptor", RCL_INTERFACES_PARAMETERDESCRIPTOR_ID),
        type(0),
        read_only(false)
    {
        memset(name, 0, sizeof(name));
        memset(description, 0, sizeof(description));
        memset(additional_constraints, 0, sizeof(additional_constraints));
    }

    bool serialize(void* msg_buf, const ParameterDescriptor* topic)
    {
        ucdrBuffer* writer = (ucdrBuffer*)msg_buf;
        (void) ucdr_serialize_string(writer, topic->name);
        (void) ucdr_serialize_uint8_t(writer, topic->type);
        (void) ucdr_serialize_string(writer, topic->description);
        (void) ucdr_serialize_string(writer, topic->additional_constraints);
        (void) ucdr_serialize_bool(writer, topic->read_only);
        for(uint8_t i = 0; i < sizeof(floating_point_range)/sizeof(rcl_interfaces::FloatingPointRange); i++)
        {
            (void) floating_point_range[i].serialize(writer, &topic->floating_point_range[i]);
        }
        for(uint8_t i = 0; i < sizeof(integer_range)/sizeof(rcl_interfaces::IntegerRange); i++)
        {
            (void) integer_range[i].serialize(writer, &topic->integer_range[i]);
        }

        return !writer->error;
    }

    bool deserialize(void* msg_buf, ParameterDescriptor* topic)
    {
        ucdrBuffer* reader = (ucdrBuffer*)msg_buf;
        (void) ucdr_deserialize_string(reader, topic->name, sizeof(topic->name));
        (void) ucdr_deserialize_uint8_t(reader, &topic->type);
        (void) ucdr_deserialize_string(reader, topic->description, sizeof(topic->description));
        (void) ucdr_deserialize_string(reader, topic->additional_constraints, sizeof(topic->additional_constraints));
        (void) ucdr_deserialize_bool(reader, &topic->read_only);
        for(uint8_t i = 0; i < sizeof(floating_point_range)/sizeof(rcl_interfaces::FloatingPointRange); i++)
        {
            (void) floating_point_range[i].deserialize(reader, &topic->floating_point_range[i]);
        }
        for(uint8_t i = 0; i < sizeof(integer_range)/sizeof(rcl_interfaces::IntegerRange); i++)
        {
            (void) integer_range[i].deserialize(reader, &topic->integer_range[i]);
        }

        return !reader->error;
    }

    uint32_t size_of_topic(const ParameterDescriptor* topic, uint32_t size)
    {
        (void) (topic);

        uint32_t previousSize = size;
        size += ucdr_alignment(size, 4) + 4 + (uint32_t)(strlen(topic->name) + 1);
        size += ucdr_alignment(size, 1) + 1;
        size += ucdr_alignment(size, 4) + 4 + (uint32_t)(strlen(topic->description) + 1);
        size += ucdr_alignment(size, 4) + 4 + (uint32_t)(strlen(topic->additional_constraints) + 1);
        size += ucdr_alignment(size, 1) + 1;
        for(uint8_t i = 0; i < sizeof(floating_point_range)/sizeof(rcl_interfaces::FloatingPointRange); i++)
        {
            size += floating_point_range[i].size_of_topic(&topic->floating_point_range[i], size);
        }
        for(uint8_t i = 0; i < sizeof(integer_range)/sizeof(rcl_interfaces::IntegerRange); i++)
        {
            size += integer_range[i].size_of_topic(&topic->integer_range[i], size);
        }

        return size - previousSize;
    }

};

} // namespace rcl_interfaces

#endif // _RCL_INTERFACES_PARAMETERDESCRIPTOR_H_