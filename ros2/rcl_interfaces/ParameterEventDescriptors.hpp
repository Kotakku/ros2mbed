#ifndef _RCL_INTERFACES_PARAMETEREVENTDESCRIPTORS_H_
#define _RCL_INTERFACES_PARAMETEREVENTDESCRIPTORS_H_

#include "../topic.hpp"

// Manualy include list
// rcl_interfaces::ParameterDescriptor
// rcl_interfaces::ParameterDescriptor
// rcl_interfaces::ParameterDescriptor
#include "rcl_interfaces/ParameterDescriptor.hpp"

namespace rcl_interfaces
{

class ParameterEventDescriptors: public ros2::Topic<ParameterEventDescriptors>
{
public:
    rcl_interfaces::ParameterDescriptor new_parameters[10];
    rcl_interfaces::ParameterDescriptor changed_parameters[10];
    rcl_interfaces::ParameterDescriptor deleted_parameters[10];

    ParameterEventDescriptors()
        : Topic("rcl_interfaces::msg::dds_::ParameterEventDescriptors_", "ParameterEventDescriptors", RCL_INTERFACES_PARAMETEREVENTDESCRIPTORS_ID)
    {
    }

    bool serialize(void* msg_buf, ParameterEventDescriptors* topic)
    {
        ucdrBuffer* writer = (ucdrBuffer*)msg_buf;
        for(uint8_t i = 0; i < sizeof(new_parameters)/sizeof(rcl_interfaces::ParameterDescriptor); i++)
        {
            (void) new_parameters[i].serialize(writer, &topic->new_parameters[i]);
        }
        for(uint8_t i = 0; i < sizeof(changed_parameters)/sizeof(rcl_interfaces::ParameterDescriptor); i++)
        {
            (void) changed_parameters[i].serialize(writer, &topic->changed_parameters[i]);
        }
        for(uint8_t i = 0; i < sizeof(deleted_parameters)/sizeof(rcl_interfaces::ParameterDescriptor); i++)
        {
            (void) deleted_parameters[i].serialize(writer, &topic->deleted_parameters[i]);
        }

        return !writer->error;
    }

    bool deserialize(void* msg_buf, ParameterEventDescriptors* topic)
    {
        ucdrBuffer* reader = (ucdrBuffer*)msg_buf;
        for(uint8_t i = 0; i < sizeof(new_parameters)/sizeof(rcl_interfaces::ParameterDescriptor); i++)
        {
            (void) new_parameters[i].deserialize(reader, &topic->new_parameters[i]);
        }
        for(uint8_t i = 0; i < sizeof(changed_parameters)/sizeof(rcl_interfaces::ParameterDescriptor); i++)
        {
            (void) changed_parameters[i].deserialize(reader, &topic->changed_parameters[i]);
        }
        for(uint8_t i = 0; i < sizeof(deleted_parameters)/sizeof(rcl_interfaces::ParameterDescriptor); i++)
        {
            (void) deleted_parameters[i].deserialize(reader, &topic->deleted_parameters[i]);
        }

        return !reader->error;
    }

    uint32_t size_of_topic(const ParameterEventDescriptors* topic, uint32_t size)
    {
        (void) (topic);

        uint32_t previousSize = size;
        for(uint8_t i = 0; i < sizeof(new_parameters)/sizeof(rcl_interfaces::ParameterDescriptor); i++)
        {
            size += new_parameters[i].size_of_topic(&topic->new_parameters[i], size);
        }
        for(uint8_t i = 0; i < sizeof(changed_parameters)/sizeof(rcl_interfaces::ParameterDescriptor); i++)
        {
            size += changed_parameters[i].size_of_topic(&topic->changed_parameters[i], size);
        }
        for(uint8_t i = 0; i < sizeof(deleted_parameters)/sizeof(rcl_interfaces::ParameterDescriptor); i++)
        {
            size += deleted_parameters[i].size_of_topic(&topic->deleted_parameters[i], size);
        }

        return size - previousSize;
    }

};

} // namespace rcl_interfaces

#endif // _RCL_INTERFACES_PARAMETEREVENTDESCRIPTORS_H_