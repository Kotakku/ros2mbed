#ifndef _RCL_INTERFACES_PARAMETEREVENT_H_
#define _RCL_INTERFACES_PARAMETEREVENT_H_

#include "../topic.hpp"

// Manualy include list
// builtin_interfaces::Time
// rcl_interfaces::Parameter
// rcl_interfaces::Parameter
// rcl_interfaces::Parameter
#include "builtin_interfaces/Time.hpp"
#include "rcl_interfaces/Parameter.hpp"

namespace rcl_interfaces
{

class ParameterEvent: public ros2::Topic<ParameterEvent>
{
public:
    builtin_interfaces::Time stamp;
    char node[255];
    rcl_interfaces::Parameter new_parameters[10];
    rcl_interfaces::Parameter changed_parameters[10];
    rcl_interfaces::Parameter deleted_parameters[10];

    ParameterEvent()
        : Topic("rcl_interfaces::msg::dds_::ParameterEvent_", "ParameterEvent", RCL_INTERFACES_PARAMETEREVENT_ID)

    {
        memset(node, 0, sizeof(node));
    }

    bool serialize(void* msg_buf, const ParameterEvent* topic)
    {
        ucdrBuffer* writer = (ucdrBuffer*)msg_buf;
        (void) stamp.serialize(writer, &topic->stamp);
        (void) ucdr_serialize_string(writer, topic->node);
        for(uint8_t i = 0; i < sizeof(new_parameters)/sizeof(rcl_interfaces::Parameter); i++)
        {
            (void) new_parameters[i].serialize(writer, &topic->new_parameters[i]);
        }
        for(uint8_t i = 0; i < sizeof(changed_parameters)/sizeof(rcl_interfaces::Parameter); i++)
        {
            (void) changed_parameters[i].serialize(writer, &topic->changed_parameters[i]);
        }
        for(uint8_t i = 0; i < sizeof(deleted_parameters)/sizeof(rcl_interfaces::Parameter); i++)
        {
            (void) deleted_parameters[i].serialize(writer, &topic->deleted_parameters[i]);
        }

        return !writer->error;
    }

    bool deserialize(void* msg_buf, ParameterEvent* topic)
    {
        ucdrBuffer* reader = (ucdrBuffer*)msg_buf;
        (void) stamp.deserialize(reader, &topic->stamp);
        (void) ucdr_deserialize_string(reader, topic->node, sizeof(topic->node));
        for(uint8_t i = 0; i < sizeof(new_parameters)/sizeof(rcl_interfaces::Parameter); i++)
        {
            (void) new_parameters[i].deserialize(reader, &topic->new_parameters[i]);
        }
        for(uint8_t i = 0; i < sizeof(changed_parameters)/sizeof(rcl_interfaces::Parameter); i++)
        {
            (void) changed_parameters[i].deserialize(reader, &topic->changed_parameters[i]);
        }
        for(uint8_t i = 0; i < sizeof(deleted_parameters)/sizeof(rcl_interfaces::Parameter); i++)
        {
            (void) deleted_parameters[i].deserialize(reader, &topic->deleted_parameters[i]);
        }

        return !reader->error;
    }

    uint32_t size_of_topic(const ParameterEvent* topic, uint32_t size)
    {
        (void) (topic);

        uint32_t previousSize = size;
        size += stamp.size_of_topic(&topic->stamp, size);
        size += ucdr_alignment(size, 4) + 4 + (uint32_t)(strlen(topic->node) + 1);
        for(uint8_t i = 0; i < sizeof(new_parameters)/sizeof(rcl_interfaces::Parameter); i++)
        {
            size += new_parameters[i].size_of_topic(&topic->new_parameters[i], size);
        }
        for(uint8_t i = 0; i < sizeof(changed_parameters)/sizeof(rcl_interfaces::Parameter); i++)
        {
            size += changed_parameters[i].size_of_topic(&topic->changed_parameters[i], size);
        }
        for(uint8_t i = 0; i < sizeof(deleted_parameters)/sizeof(rcl_interfaces::Parameter); i++)
        {
            size += deleted_parameters[i].size_of_topic(&topic->deleted_parameters[i], size);
        }

        return size - previousSize;
    }

};

} // namespace rcl_interfaces

#endif // _RCL_INTERFACES_PARAMETEREVENT_H_