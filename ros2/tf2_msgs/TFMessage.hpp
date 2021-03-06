// This file was generated by the tool gen.

#ifndef _TF2_MSGS_TFMESSAGE_H_
#define _TF2_MSGS_TFMESSAGE_H_

#include "../topic.hpp"

// Manualy include list
// geometry_msgs::TransformStamped
// suggest
#include "geometry_msgs/TransformStamped.hpp"

namespace tf2_msgs
{

class TFMessage: public ros2::Topic<TFMessage>
{
public:
    using SharedPtr = std::shared_ptr<TFMessage>;

    std::vector<geometry_msgs::TransformStamped> transforms;

    TFMessage()
        : Topic("tf2_msgs::msg::dds_::TFMessage_", "TFMessage", TF2_MSGS_TFMESSAGE_ID)
    {
    }

    bool serialize(void* msg_buf, TFMessage* topic)
    {
        ucdrBuffer* writer = (ucdrBuffer*)msg_buf;
        for(size_t i = 0; i < topic->transforms.size(); i++)
        {
            (void) transforms[i].serialize(writer, &topic->transforms[i]);
        }

        return !writer->error;
    }

    bool deserialize(void* msg_buf, TFMessage* topic)
    {
        ucdrBuffer* reader = (ucdrBuffer*)msg_buf;
        for(size_t i = 0; i < topic->transforms.size(); i++)
        {
            (void) transforms[i].deserialize(reader, &topic->transforms[i]);
        }

        return !reader->error;
    }

    uint32_t size_of_topic(const TFMessage* topic, uint32_t size)
    {
        (void) (topic);

        uint32_t previousSize = size;
        for(size_t i = 0; i < topic->transforms.size(); i++)
        {
            size += transforms[i].size_of_topic(&topic->transforms[i], size);
        }

        return size - previousSize;
    }

};

} // namespace tf2_msgs

#endif // _TF2_MSGS_TFMESSAGE_H_