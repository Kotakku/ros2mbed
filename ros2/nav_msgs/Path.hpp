// This file was generated by the tool gen.

#ifndef _NAV_MSGS_PATH_H_
#define _NAV_MSGS_PATH_H_

#include "../topic.hpp"

// Manualy include list
// std_msgs::Header
// suggest
#include "std_msgs/Header.hpp"
// geometry_msgs::PoseStamped
// suggest
#include "geometry_msgs/PoseStamped.hpp"

namespace nav_msgs
{

class Path: public ros2::Topic<Path>
{
public:
    using SharedPtr = std::shared_ptr<Path>;

    std_msgs::Header header;
    std::vector<geometry_msgs::PoseStamped> poses;

    Path()
        : Topic("nav_msgs::msg::dds_::Path_", "Path", NAV_MSGS_PATH_ID)
    {
    }

    bool serialize(void* msg_buf, Path* topic)
    {
        ucdrBuffer* writer = (ucdrBuffer*)msg_buf;
        (void) header.serialize(writer, &topic->header);
        for(size_t i = 0; i < topic->poses.size(); i++)
        {
            (void) poses[i].serialize(writer, &topic->poses[i]);
        }

        return !writer->error;
    }

    bool deserialize(void* msg_buf, Path* topic)
    {
        ucdrBuffer* reader = (ucdrBuffer*)msg_buf;
        (void) header.deserialize(reader, &topic->header);
        for(size_t i = 0; i < topic->poses.size(); i++)
        {
            (void) poses[i].deserialize(reader, &topic->poses[i]);
        }

        return !reader->error;
    }

    uint32_t size_of_topic(const Path* topic, uint32_t size)
    {
        (void) (topic);

        uint32_t previousSize = size;
        size += header.size_of_topic(&topic->header, size);
        for(size_t i = 0; i < topic->poses.size(); i++)
        {
            size += poses[i].size_of_topic(&topic->poses[i], size);
        }

        return size - previousSize;
    }

};

} // namespace nav_msgs

#endif // _NAV_MSGS_PATH_H_