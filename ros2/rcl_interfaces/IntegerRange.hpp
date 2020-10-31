#ifndef _RCL_INTERFACES_INTEGERRANGE_H_
#define _RCL_INTERFACES_INTEGERRANGE_H_

#include "../topic.hpp"

// Manualy include list

namespace rcl_interfaces
{

class IntegerRange: public ros2::Topic<IntegerRange>
{
public:
    using SharedPtr = std::shared_ptr<IntegerRange>;
    
    int64_t from_value;
    int64_t to_value;
    uint64_t step;

    IntegerRange()
        : Topic("rcl_interfaces::msg::dds_::IntegerRange_", "IntegerRange", RCL_INTERFACES_INTEGERRANGE_ID),
        from_value(0),
        to_value(0),
        step(0)
    {
    }

    bool serialize(void* msg_buf, IntegerRange* topic)
    {
        ucdrBuffer* writer = (ucdrBuffer*)msg_buf;
        (void) ucdr_serialize_int64_t(writer, topic->from_value);
        (void) ucdr_serialize_int64_t(writer, topic->to_value);
        (void) ucdr_serialize_uint64_t(writer, topic->step);

        return !writer->error;
    }

    bool deserialize(void* msg_buf, IntegerRange* topic)
    {
        ucdrBuffer* reader = (ucdrBuffer*)msg_buf;
        (void) ucdr_deserialize_int64_t(reader, &topic->from_value);
        (void) ucdr_deserialize_int64_t(reader, &topic->to_value);
        (void) ucdr_deserialize_uint64_t(reader, &topic->step);

        return !reader->error;
    }

    uint32_t size_of_topic(const IntegerRange* topic, uint32_t size)
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

#endif // _RCL_INTERFACES_INTEGERRANGE_H_