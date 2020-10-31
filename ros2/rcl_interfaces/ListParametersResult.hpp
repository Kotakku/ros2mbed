#ifndef _RCL_INTERFACES_LISTPARAMETERSRESULT_H_
#define _RCL_INTERFACES_LISTPARAMETERSRESULT_H_

#include "../topic.hpp"

// Manualy include list

/*
namespace rcl_interfaces
{

class ListParametersResult: public ros2::Topic<ListParametersResult>
{
public:
    char names[255][10];
    uint32_t names_size;
    char prefixes[255][10];
    uint32_t prefixes_size;

    ListParametersResult()
        : Topic("rcl_interfaces::msg::dds_::ListParametersResult_", "ListParametersResult", RCL_INTERFACES_LISTPARAMETERSRESULT_ID),
        names_size(1),
        prefixes_size(1)
    {
        memset(names, 0, sizeof(names));
        memset(prefixes, 0, sizeof(prefixes));
    }

    bool serialize(void* msg_buf, ListParametersResult* topic)
    {
        ucdrBuffer* writer = (ucdrBuffer*)msg_buf;
        (void) ucdr_serialize_sequence_string(writer, topic->names, topic->names_size);
        (void) ucdr_serialize_sequence_string(writer, topic->prefixes, topic->prefixes_size);

        return !writer->error;
    }

    bool deserialize(void* msg_buf, ListParametersResult* topic)
    {
        ucdrBuffer* reader = (ucdrBuffer*)msg_buf;
        (void) ucdr_deserialize_sequence_char(reader, topic->names, sizeof(topic->names)/sizeof(char), &topic->names_size);
        (void) ucdr_deserialize_sequence_char(reader, topic->prefixes, sizeof(topic->prefixes)/sizeof(char), &topic->prefixes_size);

        return !reader->error;
    }

    uint32_t size_of_topic(const ListParametersResult* topic, uint32_t size)
    {
        (void) (topic);

        uint32_t previousSize = size;
        size += ucdr_alignment(size, 4) + 4;
        size += ucdr_alignment(size, 1) + (topic->names_size * 1);
        size += ucdr_alignment(size, 4) + 4;
        size += ucdr_alignment(size, 1) + (topic->prefixes_size * 1);

        return size - previousSize;
    }

};

} // namespace rcl_interfaces
*/

#endif // _RCL_INTERFACES_LISTPARAMETERSRESULT_H_