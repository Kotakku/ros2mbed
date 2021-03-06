// This file was generated by the tool gen.

#ifndef _GEOMETRY_MSGS_VECTOR3_H_
#define _GEOMETRY_MSGS_VECTOR3_H_

#include "../topic.hpp"

// Manualy include list

namespace geometry_msgs
{

class Vector3: public ros2::Topic<Vector3>
{
public:
    using SharedPtr = std::shared_ptr<Vector3>;

    double x;
    double y;
    double z;

    Vector3()
        : Topic("geometry_msgs::msg::dds_::Vector3_", "Vector3", GEOMETRY_MSGS_VECTOR3_ID),
        x(0),
        y(0),
        z(0)
    {
    }

    bool serialize(void* msg_buf, Vector3* topic)
    {
        ucdrBuffer* writer = (ucdrBuffer*)msg_buf;
        (void) ucdr_serialize_double(writer, topic->x);
        (void) ucdr_serialize_double(writer, topic->y);
        (void) ucdr_serialize_double(writer, topic->z);

        return !writer->error;
    }

    bool deserialize(void* msg_buf, Vector3* topic)
    {
        ucdrBuffer* reader = (ucdrBuffer*)msg_buf;
        (void) ucdr_deserialize_double(reader, &topic->x);
        (void) ucdr_deserialize_double(reader, &topic->y);
        (void) ucdr_deserialize_double(reader, &topic->z);

        return !reader->error;
    }

    uint32_t size_of_topic(const Vector3* topic, uint32_t size)
    {
        (void) (topic);

        uint32_t previousSize = size;
        size += ucdr_alignment(size, 8) + 8;
        size += ucdr_alignment(size, 8) + 8;
        size += ucdr_alignment(size, 8) + 8;

        return size - previousSize;
    }

};

} // namespace geometry_msgs

#endif // _GEOMETRY_MSGS_VECTOR3_H_