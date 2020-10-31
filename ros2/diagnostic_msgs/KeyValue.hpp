#ifndef _DIAGNOSTIC_MSGS_KEYVALUE_H_
#define _DIAGNOSTIC_MSGS_KEYVALUE_H_

#include "../topic.hpp"

// Manualy include list

namespace diagnostic_msgs
{

class KeyValue: public ros2::Topic<KeyValue>
{
public:
    std::string key;
    std::string value;

    KeyValue()
        : Topic("diagnostic_msgs::msg::dds_::KeyValue_", "KeyValue", DIAGNOSTIC_MSGS_KEYVALUE_ID)
    {
    }

    bool serialize(void* msg_buf, KeyValue* topic)
    {
        ucdrBuffer* writer = (ucdrBuffer*)msg_buf;
        (void) ucdr_serialize_string(writer, topic->key.data());
        (void) ucdr_serialize_string(writer, topic->value.data());

        return !writer->error;
    }

    bool deserialize(void* msg_buf, KeyValue* topic)
    {
        ucdrBuffer* reader = (ucdrBuffer*)msg_buf;
        (void) ucdr_deserialize_string(reader, topic->key.data(), topic->key.capacity());
        (void) ucdr_deserialize_string(reader, topic->value.data(), topic->value.capacity());

        return !reader->error;
    }

    uint32_t size_of_topic(const KeyValue* topic, uint32_t size)
    {
        (void) (topic);

        uint32_t previousSize = size;
        size += ucdr_alignment(size, 4) + 4 + (uint32_t)(topic->key.length() + 1);
        size += ucdr_alignment(size, 4) + 4 + (uint32_t)(topic->value.length() + 1);

        return size - previousSize;
    }

};

} // namespace diagnostic_msgs

#endif // _DIAGNOSTIC_MSGS_KEYVALUE_H_