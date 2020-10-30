#ifndef _GEOMETRY_MSGS_POSESTAMPED_H_
#define _GEOMETRY_MSGS_POSESTAMPED_H_

#include "../topic.hpp"

// Manualy include list
// std_msgs::Header
// suggest
#include "std_msgs/Header.hpp"
// geometry_msgs::Pose
// suggest
#include "geometry_msgs/Pose.hpp"

namespace geometry_msgs
{

class PoseStamped: public ros2::Topic<PoseStamped>
{
public:
    std_msgs::Header header;
    geometry_msgs::Pose pose;

    PoseStamped()
        : Topic("geometry_msgs::msg::dds_::PoseStamped_", "PoseStamped", GEOMETRY_MSGS_POSESTAMPED_ID)
    {
    }

    bool serialize(void* msg_buf, const PoseStamped* topic)
    {
        ucdrBuffer* writer = (ucdrBuffer*)msg_buf;
        (void) header.serialize(writer, &topic->header);
        (void) pose.serialize(writer, &topic->pose);

        return !writer->error;
    }

    bool deserialize(void* msg_buf, PoseStamped* topic)
    {
        ucdrBuffer* reader = (ucdrBuffer*)msg_buf;
        (void) header.deserialize(reader, &topic->header);
        (void) pose.deserialize(reader, &topic->pose);

        return !reader->error;
    }

    uint32_t size_of_topic(const PoseStamped* topic, uint32_t size)
    {
        (void) (topic);

        uint32_t previousSize = size;
        size += header.size_of_topic(&topic->header, size);
        size += pose.size_of_topic(&topic->pose, size);

        return size - previousSize;
    }

};

} // namespace geometry_msgs

#endif // _GEOMETRY_MSGS_POSESTAMPED_H_