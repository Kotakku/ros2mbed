// This file was generated by the tool gen.

#ifndef _STD_MSGS_MULTIARRAYDIMENSION_H_
#define _STD_MSGS_MULTIARRAYDIMENSION_H_

#include "../topic.hpp"

// Manualy include list

namespace std_msgs
{

class MultiArrayDimension: public ros2::Topic<MultiArrayDimension>
{
public:
    using SharedPtr = std::shared_ptr<MultiArrayDimension>;

    std::string label;
    uint32_t size;
    uint32_t stride;

    MultiArrayDimension()
        : Topic("std_msgs::msg::dds_::MultiArrayDimension_", "MultiArrayDimension", STD_MSGS_MULTIARRAYDIMENSION_ID),
        size(0),
        stride(0)
    {
    }

    bool serialize(void* msg_buf, MultiArrayDimension* topic)
    {
        ucdrBuffer* writer = (ucdrBuffer*)msg_buf;
        (void) ucdr_serialize_string(writer, topic->label);
        (void) ucdr_serialize_uint32_t(writer, topic->size);
        (void) ucdr_serialize_uint32_t(writer, topic->stride);

        return !writer->error;
    }

    bool deserialize(void* msg_buf, MultiArrayDimension* topic)
    {
        ucdrBuffer* reader = (ucdrBuffer*)msg_buf;
        (void) ucdr_deserialize_string(reader, topic->label);
        (void) ucdr_deserialize_uint32_t(reader, &topic->size);
        (void) ucdr_deserialize_uint32_t(reader, &topic->stride);

        return !reader->error;
    }

    uint32_t size_of_topic(const MultiArrayDimension* topic, uint32_t size)
    {
        (void) (topic);

        uint32_t previousSize = size;
        size += ucdr_alignment(size, 4) + 4 + (uint32_t)(topic->label.length());
        size += ucdr_alignment(size, 4) + 4;
        size += ucdr_alignment(size, 4) + 4;

        return size - previousSize;
    }

};

} // namespace std_msgs

#endif // _STD_MSGS_MULTIARRAYDIMENSION_H_