#ifndef _RCL_INTERFACES_LOG_H_
#define _RCL_INTERFACES_LOG_H_

#include "../topic.hpp"

// Manualy include list
// builtin_interfaces::Time
#include "builtin_interfaces/Time.hpp"

namespace rcl_interfaces
{

enum Log_Constants
{
    DEBUG = 10,
    INFO = 20,
    WARN = 30,
    ERROR = 40,
    FATAL = 50
};

class Log: public ros2::Topic<Log>
{
public:
    using SharedPtr = std::shared_ptr<Log>;

    builtin_interfaces::Time stamp;
    uint8_t level;
    std::string name;
    std::string msg;
    std::string file;
    std::string function;
    uint32_t line;

    Log()
        : Topic("rcl_interfaces::msg::dds_::Log_", "Log", RCL_INTERFACES_LOG_ID),
        level(0),
        line(0)
    {
    }

    bool serialize(void* msg_buf, Log* topic)
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
        (void) ucdr_deserialize_string(reader, topic->name);
        (void) ucdr_deserialize_string(reader, topic->msg);
        (void) ucdr_deserialize_string(reader, topic->file);
        (void) ucdr_deserialize_string(reader, topic->function);
        (void) ucdr_deserialize_uint32_t(reader, &topic->line);

        return !reader->error;
    }

    uint32_t size_of_topic(const Log* topic, uint32_t size)
    {
        (void) (topic);

        uint32_t previousSize = size;
        size += stamp.size_of_topic(&topic->stamp, size);
        size += ucdr_alignment(size, 1) + 1;
        size += ucdr_alignment(size, 4) + 4 + (uint32_t)(topic->name.length());
        size += ucdr_alignment(size, 4) + 4 + (uint32_t)(topic->msg.length());
        size += ucdr_alignment(size, 4) + 4 + (uint32_t)(topic->file.length());
        size += ucdr_alignment(size, 4) + 4 + (uint32_t)(topic->function.length());
        size += ucdr_alignment(size, 4) + 4;

        return size - previousSize;
    }

};

} // namespace rcl_interfaces

#endif // _RCL_INTERFACES_LOG_H_