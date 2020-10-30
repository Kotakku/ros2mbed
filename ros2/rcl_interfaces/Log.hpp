#ifndef _RCL_INTERFACES_LOG_H_
#define _RCL_INTERFACES_LOG_H_

#include "../topic.hpp"

// Manualy include list
// builtin_interfaces::Time
#include "builtin_interfaces/Time.hpp"

namespace rcl_interfaces
{

class Log: public ros2::Topic<Log>
{
public:
    builtin_interfaces::Time stamp;
    uint8_t level;
    char name[255];
    char msg[255];
    char file[255];
    char function[255];
    uint32_t line;

    Log()
        : Topic("rcl_interfaces::msg::dds_::Log_", "Log", RCL_INTERFACES_LOG_ID),
        level(0),
        line(0)
    {
        memset(name, 0, sizeof(name));
        memset(msg, 0, sizeof(msg));
        memset(file, 0, sizeof(file));
        memset(function, 0, sizeof(function));
    }

    bool serialize(void* msg_buf, const Log* topic)
    {
        ucdrBuffer* writer = (ucdrBuffer*)msg_buf;
        (void) stamp.serialize(writer, &topic->stamp);
        (void) ucdr_serialize_uint8_t(writer, topic->level);
        (void) ucdr_serialize_string(writer, topic->name);
        (void) ucdr_serialize_string(writer, topic->msg);
        (void) ucdr_serialize_string(writer, topic->file);
        (void) ucdr_serialize_string(writer, topic->function);
        (void) ucdr_serialize_uint32_t(writer, topic->line);

        return !writer->error;
    }

    bool deserialize(void* msg_buf, Log* topic)
    {
        ucdrBuffer* reader = (ucdrBuffer*)msg_buf;
        (void) stamp.deserialize(reader, &topic->stamp);
        (void) ucdr_deserialize_uint8_t(reader, &topic->level);
        (void) ucdr_deserialize_string(reader, topic->name, sizeof(topic->name));
        (void) ucdr_deserialize_string(reader, topic->msg, sizeof(topic->msg));
        (void) ucdr_deserialize_string(reader, topic->file, sizeof(topic->file));
        (void) ucdr_deserialize_string(reader, topic->function, sizeof(topic->function));
        (void) ucdr_deserialize_uint32_t(reader, &topic->line);

        return !reader->error;
    }

    uint32_t size_of_topic(const Log* topic, uint32_t size)
    {
        (void) (topic);

        uint32_t previousSize = size;
        size += stamp.size_of_topic(&topic->stamp, size);
        size += ucdr_alignment(size, 1) + 1;
        size += ucdr_alignment(size, 4) + 4 + (uint32_t)(strlen(topic->name) + 1);
        size += ucdr_alignment(size, 4) + 4 + (uint32_t)(strlen(topic->msg) + 1);
        size += ucdr_alignment(size, 4) + 4 + (uint32_t)(strlen(topic->file) + 1);
        size += ucdr_alignment(size, 4) + 4 + (uint32_t)(strlen(topic->function) + 1);
        size += ucdr_alignment(size, 4) + 4;

        return size - previousSize;
    }

};

} // namespace rcl_interfaces

#endif // _RCL_INTERFACES_LOG_H_