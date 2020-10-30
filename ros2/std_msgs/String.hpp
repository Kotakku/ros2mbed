#ifndef _STD_MSGS_STRING_H_
#define _STD_MSGS_STRING_H_

#include "../topic.hpp"

// Manualy include list

namespace std_msgs
{

class String: public ros2::Topic<String>
{
public:
    std::string data;

    String()
        : Topic("std_msgs::msg::dds_::String_", "String", STD_MSGS_STRING_ID)
    {
    }

    bool serialize(void* msg_buf, const String* topic)
    {
        ucdrBuffer* writer = (ucdrBuffer*)msg_buf;
        (void) ucdr_serialize_string(writer, topic->data.data());

        return !writer->error;
    }

    bool deserialize(void* msg_buf, String* topic)
    {
        ucdrBuffer* reader = (ucdrBuffer*)msg_buf;
        (void) ucdr_deserialize_string(reader, topic->data.data(), topic->data.capacity());

        return !reader->error;
    }

    uint32_t size_of_topic(const String* topic, uint32_t size)
    {
        (void) (topic);

        uint32_t previousSize = size;
        size += ucdr_alignment(size, 4) + 4 + (uint32_t)(topic->data.length() + 1);

        return size - previousSize;
    }

};

} // namespace std_msgs

#endif // _STD_MSGS_STRING_H_