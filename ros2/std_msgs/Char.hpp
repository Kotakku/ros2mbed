// This file was generated by the tool gen.

#ifndef _STD_MSGS_CHAR_H_
#define _STD_MSGS_CHAR_H_

#include "../topic.hpp"

// Manualy include list

namespace std_msgs
{

class Char: public ros2::Topic<Char>
{
public:
    using SharedPtr = std::shared_ptr<Char>;

    uint8_t data;

    Char()
        : Topic("std_msgs::msg::dds_::Char_", "Char", STD_MSGS_CHAR_ID),
        data(0)
    {
    }

    bool serialize(void* msg_buf, Char* topic)
    {
        ucdrBuffer* writer = (ucdrBuffer*)msg_buf;
        (void) ucdr_serialize_uint8_t(writer, topic->data);

        return !writer->error;
    }

    bool deserialize(void* msg_buf, Char* topic)
    {
        ucdrBuffer* reader = (ucdrBuffer*)msg_buf;
        (void) ucdr_deserialize_uint8_t(reader, &topic->data);

        return !reader->error;
    }

    uint32_t size_of_topic(const Char* topic, uint32_t size)
    {
        (void) (topic);

        uint32_t previousSize = size;
        size += ucdr_alignment(size, 1) + 1;

        return size - previousSize;
    }

};

} // namespace std_msgs

#endif // _STD_MSGS_CHAR_H_