#ifndef _STD_MSGS_HEADER_H_
#define _STD_MSGS_HEADER_H_

#include "../topic.hpp"

// Manualy include list
// builtin_interfaces::Time
// suggest
#include "builtin_interfaces/Time.hpp"

namespace std_msgs
{

class Header: public ros2::Topic<Header>
{
public:
    using SharedPtr = std::shared_ptr<Header>;
    
    builtin_interfaces::Time stamp;
    std::string frame_id;

    Header()
        : Topic("std_msgs::msg::dds_::Header_", "Header", STD_MSGS_HEADER_ID)
    {
    }

    bool serialize(void* msg_buf, Header* topic)
    {
        ucdrBuffer* writer = (ucdrBuffer*)msg_buf;
        (void) stamp.serialize(writer, &topic->stamp);
        (void) ucdr_serialize_string(writer, topic->frame_id.data());

        return !writer->error;
    }

    bool deserialize(void* msg_buf, Header* topic)
    {
        ucdrBuffer* reader = (ucdrBuffer*)msg_buf;
        (void) stamp.deserialize(reader, &topic->stamp);
        (void) ucdr_deserialize_string(reader, topic->frame_id.data(), topic->frame_id.capacity());

        return !reader->error;
    }

    uint32_t size_of_topic(const Header* topic, uint32_t size)
    {
        (void) (topic);

        uint32_t previousSize = size;
        size += stamp.size_of_topic(&topic->stamp, size);
        size += ucdr_alignment(size, 4) + 4 + (uint32_t)(topic->frame_id.length() + 1);

        return size - previousSize;
    }

};

} // namespace std_msgs

#endif // _STD_MSGS_HEADER_H_