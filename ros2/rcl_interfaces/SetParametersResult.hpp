#ifndef _RCL_INTERFACES_SETPARAMETERSRESULT_H_
#define _RCL_INTERFACES_SETPARAMETERSRESULT_H_

#include "../topic.hpp"

// Manualy include list

namespace rcl_interfaces
{

class SetParametersResult: public ros2::Topic<SetParametersResult>
{
public:
    bool successful;
    char reason[255];

    SetParametersResult()
        : Topic("rcl_interfaces::msg::dds_::SetParametersResult_", "SetParametersResult", RCL_INTERFACES_SETPARAMETERSRESULT_ID),
        successful(false)
    {
        memset(reason, 0, sizeof(reason));
    }

    bool serialize(void* msg_buf, const SetParametersResult* topic)
    {
        ucdrBuffer* writer = (ucdrBuffer*)msg_buf;
        (void) ucdr_serialize_bool(writer, topic->successful);
        (void) ucdr_serialize_string(writer, topic->reason);

        return !writer->error;
    }

    bool deserialize(void* msg_buf, SetParametersResult* topic)
    {
        ucdrBuffer* reader = (ucdrBuffer*)msg_buf;
        (void) ucdr_deserialize_bool(reader, &topic->successful);
        (void) ucdr_deserialize_string(reader, topic->reason, sizeof(topic->reason));

        return !reader->error;
    }

    uint32_t size_of_topic(const SetParametersResult* topic, uint32_t size)
    {
        (void) (topic);

        uint32_t previousSize = size;
        size += ucdr_alignment(size, 1) + 1;
        size += ucdr_alignment(size, 4) + 4 + (uint32_t)(strlen(topic->reason) + 1);

        return size - previousSize;
    }

};

} // namespace rcl_interfaces

#endif // _RCL_INTERFACES_SETPARAMETERSRESULT_H_