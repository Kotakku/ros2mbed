// This file was generated by the tool gen.

#ifndef _STD_MSGS_BYTE_H_
#define _STD_MSGS_BYTE_H_

#include "../topic.hpp"

// Manualy include list

namespace std_msgs
{

class Byte: public ros2::Topic<Byte>
{
public:
    using SharedPtr = std::shared_ptr<Byte>;

    uint8_t data;

    Byte()
        : Topic("std_msgs::msg::dds_::Byte_", "Byte", STD_MSGS_BYTE_ID),
        data(0)
    {
    }

    bool serialize(void* msg_buf, Byte* topic)
    {
        ucdrBuffer* writer = (ucdrBuffer*)msg_buf;
        (void) ucdr_serialize_uint8_t(writer, topic->data);

        return !writer->error;
    }

    bool deserialize(void* msg_buf, Byte* topic)
    {
        ucdrBuffer* reader = (ucdrBuffer*)msg_buf;
        (void) ucdr_deserialize_uint8_t(reader, &topic->data);

        return !reader->error;
    }

    uint32_t size_of_topic(const Byte* topic, uint32_t size)
    {
        (void) (topic);

        uint32_t previousSize = size;
        size += ucdr_alignment(size, 1) + 1;

        return size - previousSize;
    }

};

} // namespace std_msgs

#endif // _STD_MSGS_BYTE_H_