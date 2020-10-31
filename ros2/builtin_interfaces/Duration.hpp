#ifndef _BUILTIN_INTERFACES_DURATION_H_
#define _BUILTIN_INTERFACES_DURATION_H_

#include "../topic.hpp"

// Manualy include list

namespace builtin_interfaces
{

class Duration: public ros2::Topic<Duration>
{
public:
    using SharedPtr = std::shared_ptr<Duration>;
    
    int32_t sec;
    uint32_t nanosec;

    Duration()
        : Topic("builtin_interfaces::msg::dds_::Duration_", "Duration", BUILTIN_INTERFACES_DURATION_ID),
        sec(0),
        nanosec(0)
    {
    }

    bool serialize(void* msg_buf, Duration* topic)
    {
        ucdrBuffer* writer = (ucdrBuffer*)msg_buf;
        (void) ucdr_serialize_int32_t(writer, topic->sec);
        (void) ucdr_serialize_uint32_t(writer, topic->nanosec);

        return !writer->error;
    }

    bool deserialize(void* msg_buf, Duration* topic)
    {
        ucdrBuffer* reader = (ucdrBuffer*)msg_buf;
        (void) ucdr_deserialize_int32_t(reader, &topic->sec);
        (void) ucdr_deserialize_uint32_t(reader, &topic->nanosec);

        return !reader->error;
    }

    uint32_t size_of_topic(const Duration* topic, uint32_t size)
    {
        (void) (topic);

        uint32_t previousSize = size;
        size += ucdr_alignment(size, 4) + 4;
        size += ucdr_alignment(size, 4) + 4;

        return size - previousSize;
    }

};

} // namespace builtin_interfaces

#endif // _BUILTIN_INTERFACES_DURATION_H_