#ifndef _RCL_INTERFACES_FLOATINGPOINTRANGE_H_
#define _RCL_INTERFACES_FLOATINGPOINTRANGE_H_

#include "../topic.hpp"

// Manualy include list

namespace rcl_interfaces
{

class FloatingPointRange: public ros2::Topic<FloatingPointRange>
{
public:
    double from_value;
    double to_value;
    double step;

    FloatingPointRange()
        : Topic("rcl_interfaces::msg::dds_::FloatingPointRange_", "FloatingPointRange", RCL_INTERFACES_FLOATINGPOINTRANGE_ID),
        from_value(0),
        to_value(0),
        step(0)
    {
    }

    bool serialize(void* msg_buf, const FloatingPointRange* topic)
    {
        ucdrBuffer* writer = (ucdrBuffer*)msg_buf;
        (void) ucdr_serialize_double(writer, topic->from_value);
        (void) ucdr_serialize_double(writer, topic->to_value);
        (void) ucdr_serialize_double(writer, topic->step);

        return !writer->error;
    }

    bool deserialize(void* msg_buf, FloatingPointRange* topic)
    {
        ucdrBuffer* reader = (ucdrBuffer*)msg_buf;
        (void) ucdr_deserialize_double(reader, &topic->from_value);
        (void) ucdr_deserialize_double(reader, &topic->to_value);
        (void) ucdr_deserialize_double(reader, &topic->step);

        return !reader->error;
    }

    uint32_t size_of_topic(const FloatingPointRange* topic, uint32_t size)
    {
        (void) (topic);

        uint32_t previousSize = size;
        size += ucdr_alignment(size, 8) + 8;
        size += ucdr_alignment(size, 8) + 8;
        size += ucdr_alignment(size, 8) + 8;

        return size - previousSize;
    }

};

} // namespace rcl_interfaces

#endif // _RCL_INTERFACES_FLOATINGPOINTRANGE_H_