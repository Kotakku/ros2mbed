// This file was generated by the tool gen.

#ifndef _GEOMETRY_MSGS_TWIST_H_
#define _GEOMETRY_MSGS_TWIST_H_

#include "../topic.hpp"

// Manualy include list
// geometry_msgs::Vector3
// suggest
#include "geometry_msgs/Vector3.hpp"
// geometry_msgs::Vector3
// suggest
#include "geometry_msgs/Vector3.hpp"

namespace geometry_msgs
{

class Twist: public ros2::Topic<Twist>
{
public:
    using SharedPtr = std::shared_ptr<Twist>;

    geometry_msgs::Vector3 linear;
    geometry_msgs::Vector3 angular;

    Twist()
        : Topic("geometry_msgs::msg::dds_::Twist_", "Twist", GEOMETRY_MSGS_TWIST_ID)
    {
    }

    bool serialize(void* msg_buf, Twist* topic)
    {
        ucdrBuffer* writer = (ucdrBuffer*)msg_buf;
        (void) linear.serialize(writer, &topic->linear);
        (void) angular.serialize(writer, &topic->angular);

        return !writer->error;
    }

    bool deserialize(void* msg_buf, Twist* topic)
    {
        ucdrBuffer* reader = (ucdrBuffer*)msg_buf;
        (void) linear.deserialize(reader, &topic->linear);
        (void) angular.deserialize(reader, &topic->angular);

        return !reader->error;
    }

    uint32_t size_of_topic(const Twist* topic, uint32_t size)
    {
        (void) (topic);

        uint32_t previousSize = size;
        size += linear.size_of_topic(&topic->linear, size);
        size += angular.size_of_topic(&topic->angular, size);

        return size - previousSize;
    }

};

} // namespace geometry_msgs

#endif // _GEOMETRY_MSGS_TWIST_H_