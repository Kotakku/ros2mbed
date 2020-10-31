#ifndef _NAV_MSGS_ODOMETRY_H_
#define _NAV_MSGS_ODOMETRY_H_

#include "../topic.hpp"

// Manualy include list
// std_msgs::Header
// suggest
#include "std_msgs/Header.hpp"
// geometry_msgs::PoseWithCovariance
// suggest
#include "geometry_msgs/PoseWithCovariance.hpp"
// geometry_msgs::TwistWithCovariance
// suggest
#include "geometry_msgs/TwistWithCovariance.hpp"

namespace nav_msgs
{

class Odometry: public ros2::Topic<Odometry>
{
public:
    std_msgs::Header header;
    std::string child_frame_id;
    geometry_msgs::PoseWithCovariance pose;
    geometry_msgs::TwistWithCovariance twist;

    Odometry()
        : Topic("nav_msgs::msg::dds_::Odometry_", "Odometry", NAV_MSGS_ODOMETRY_ID)
    {
    }

    bool serialize(void* msg_buf, Odometry* topic)
    {
        ucdrBuffer* writer = (ucdrBuffer*)msg_buf;
        (void) header.serialize(writer, &topic->header);
        (void) ucdr_serialize_string(writer, topic->child_frame_id.data());
        (void) pose.serialize(writer, &topic->pose);
        (void) twist.serialize(writer, &topic->twist);

        return !writer->error;
    }

    bool deserialize(void* msg_buf, Odometry* topic)
    {
        ucdrBuffer* reader = (ucdrBuffer*)msg_buf;
        (void) header.deserialize(reader, &topic->header);
        (void) ucdr_deserialize_string(reader, topic->child_frame_id.data(), topic->child_frame_id.capacity());
        (void) pose.deserialize(reader, &topic->pose);
        (void) twist.deserialize(reader, &topic->twist);

        return !reader->error;
    }

    uint32_t size_of_topic(const Odometry* topic, uint32_t size)
    {
        (void) (topic);

        uint32_t previousSize = size;
        size += header.size_of_topic(&topic->header, size);
        size += ucdr_alignment(size, 4) + 4 + (uint32_t)(topic->child_frame_id.length() + 1);
        size += pose.size_of_topic(&topic->pose, size);
        size += twist.size_of_topic(&topic->twist, size);

        return size - previousSize;
    }

};

} // namespace nav_msgs

#endif // _NAV_MSGS_ODOMETRY_H_