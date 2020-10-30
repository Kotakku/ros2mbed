#ifndef _RCL_INTERFACES_PARAMETERVALUE_H_
#define _RCL_INTERFACES_PARAMETERVALUE_H_

#include "../topic.hpp"

// Manualy include list

namespace rcl_interfaces
{

class ParameterValue: public ros2::Topic<ParameterValue>
{
public:
    uint8_t type;
    bool bool_value;
    int64_t integer_value;
    double double_value;
    std::string string_value;
    std::vector<uint8_t> byte_array_value;
    //std::vector<bool> bool_array_value;
    std::vector<uint8_t> bool_array_value;
    
    std::vector<int64_t> integer_array_value;
    std::vector<double> double_array_value;
    std::vector<std::string> string_array_value;

    ParameterValue()
        : Topic("rcl_interfaces::msg::dds_::ParameterValue_", "ParameterValue", RCL_INTERFACES_PARAMETERVALUE_ID),
        type(0),
        bool_value(false),
        integer_value(0),
        double_value(0)
    {
    }

    bool serialize(void* msg_buf, const ParameterValue* topic)
    {

        //printf("seri 1\n");
        ucdrBuffer* writer = (ucdrBuffer*)msg_buf;
        (void) ucdr_serialize_uint8_t(writer, topic->type);
        (void) ucdr_serialize_bool(writer, topic->bool_value);
        (void) ucdr_serialize_int64_t(writer, topic->integer_value);
        (void) ucdr_serialize_double(writer, topic->double_value);
        //printf("seri 2\n");
        (void) ucdr_serialize_string(writer, topic->string_value.data());
        //printf("seri 3\n");
        (void) ucdr_serialize_sequence_uint8_t(writer, topic->byte_array_value.data(), topic->byte_array_value.size());
        (void) ucdr_serialize_sequence_uint8_t(writer, topic->bool_array_value.data(), topic->bool_array_value.size());
        //printf("seri 4\n");
        (void) ucdr_serialize_sequence_int64_t(writer, topic->integer_array_value.data(), topic->integer_array_value.size());
        /*
        (void) ucdr_serialize_sequence_double(writer, topic->double_array_value.data(), topic->double_array_value.size());
        printf("seri 5\n");
        for(uint8_t i = 0; i < topic->string_array_value.size(); i++)
        {
            printf("seri 6\n");
            (void) ucdr_serialize_string(writer, topic->string_array_value[i].data());
        }
        */
        printf("seri e\n");

        return !writer->error;
    }

    bool deserialize(void* msg_buf, ParameterValue* topic)
    {
        //printf("deseri 1\n");

        ucdrBuffer* reader = (ucdrBuffer*)msg_buf;
        (void) ucdr_deserialize_uint8_t(reader, &topic->type);
        (void) ucdr_deserialize_bool(reader, &topic->bool_value);
        (void) ucdr_deserialize_int64_t(reader, &topic->integer_value);
        (void) ucdr_deserialize_double(reader, &topic->double_value);

        //printf("deseri 2\n");
        (void) ucdr_deserialize_string(reader, topic->string_value.data(), topic->string_value.capacity());
        {
            uint32_t length;
            (void) ucdr_deserialize_sequence_uint8_t(reader, topic->byte_array_value.data(), topic->byte_array_value.capacity(), &length);
            topic->byte_array_value.resize(length);
        }

        //printf("deseri 3\n");
        {
            uint32_t length;
            (void) ucdr_deserialize_sequence_uint8_t(reader, topic->bool_array_value.data(), topic->bool_array_value.capacity(), &length);
            topic->bool_array_value.resize(length);
        }
        //printf("deseri 4\n");
        {
            uint32_t length;
            (void) ucdr_deserialize_sequence_int64_t(reader, topic->integer_array_value.data(), topic->integer_array_value.capacity(), &length);
            topic->integer_array_value.resize(length);
        }
        //printf("deseri 5\n");
        /*
        {
            uint32_t length;
            (void) ucdr_deserialize_sequence_double(reader, topic->double_array_value.data(), topic->double_array_value.capacity(), &length);
            topic->integer_array_value.resize(length);
        }*/
        //printf("deseri 6\n");

        /*
        {
            (void) ucdr_deserialize_string(reader, topic->string_array_value.data(), topic->string_array_value.capacity());
            topic->string_array_value.resize(length);
        }
        */
        topic->integer_array_value.resize(0);
        topic->string_array_value.resize(0);

        printf("deseri e\n");

        return !reader->error;
    }

    uint32_t size_of_topic(const ParameterValue* topic, uint32_t size)
    {
        (void) (topic);

        uint32_t previousSize = size;
        size += ucdr_alignment(size, 1) + 1;
        size += ucdr_alignment(size, 1) + 1;
        size += ucdr_alignment(size, 8) + 8;
        size += ucdr_alignment(size, 8) + 8;
        size += ucdr_alignment(size, 4) + 4 + (uint32_t)(topic->string_value.length() + 1);
        size += ucdr_alignment(size, 4) + 4;
        size += ucdr_alignment(size, 1) + (topic->byte_array_value.size() * 1);
        size += ucdr_alignment(size, 4) + 4;
        size += ucdr_alignment(size, 1) + (topic->bool_array_value.size() * 1);
        size += ucdr_alignment(size, 4) + 4;
        size += ucdr_alignment(size, 8) + (topic->integer_array_value.size() * 8);
        size += ucdr_alignment(size, 4) + 4;
        size += ucdr_alignment(size, 8) + (topic->double_array_value.size() * 8);
        size += ucdr_alignment(size, 4) + 4;
        size += ucdr_alignment(size, 1) + (topic->string_array_value.size() * 1);

        return size - previousSize;
    }

};

} // namespace rcl_interfaces

#endif // _RCL_INTERFACES_PARAMETERVALUE_H_
/*
#ifndef _RCL_INTERFACES_PARAMETERVALUE_H_
#define _RCL_INTERFACES_PARAMETERVALUE_H_

#include "../topic.hpp"

// Manualy include list

namespace rcl_interfaces
{

class ParameterValue: public ros2::Topic<ParameterValue>
{
public:
    uint8_t type;
    bool bool_value;
    int64_t integer_value;
    double double_value;
    std::string string_value;
    std::vector<uint8_t> byte_array_value;
    bool bool_array_value[32];
    std::vector<int64_t> integer_array_value;
    std::vector<double> double_array_value;
    std::vector<std::string> string_array_value;
    //uint32_t string_array_value_size;

    ParameterValue()
        : Topic("rcl_interfaces::msg::dds_::ParameterValue_", "ParameterValue", RCL_INTERFACES_PARAMETERVALUE_ID),
        type(0),
        bool_value(false),
        integer_value(0),
        double_value(0)
    {
    }

    bool serialize(void* msg_buf, const ParameterValue* topic)
    {
        ucdrBuffer* writer = (ucdrBuffer*)msg_buf;
        (void) ucdr_serialize_uint8_t(writer, topic->type);
        (void) ucdr_serialize_bool(writer, topic->bool_value);
        (void) ucdr_serialize_int64_t(writer, topic->integer_value);
        (void) ucdr_serialize_double(writer, topic->double_value);
        (void) ucdr_serialize_string(writer, topic->string_value.c_str());
        (void) ucdr_serialize_array_uint8_t(writer, topic->byte_array_value.data(), topic->byte_array_value.size());
        (void) ucdr_serialize_array_bool(writer, topic->bool_array_value, sizeof(bool_array_value));
        (void) ucdr_serialize_array_int64_t(writer, topic->integer_array_value.data(), topic->integer_array_value.size());
        (void) ucdr_serialize_array_double(writer, topic->double_array_value.data(), topic->double_array_value.size());
        //(void) ucdr_serialize_sequence_string(writer, topic->string_array_value, topic->string_array_value.size());
        for(size_t i = 0; i < topic->string_array_value.size(); i++)
        {
            (void) ucdr_serialize_string(writer, topic->string_array_value[i].c_str());
        }

        return !writer->error;
    }

    bool deserialize(void* msg_buf, ParameterValue* topic)
    {
        const size_t param_count_max = 16;
        //size_t str_array_size;
        ucdrBuffer* reader = (ucdrBuffer*)msg_buf;
        (void) ucdr_deserialize_uint8_t(reader, &topic->type);
        (void) ucdr_deserialize_bool(reader, &topic->bool_value);
        (void) ucdr_deserialize_int64_t(reader, &topic->integer_value);
        (void) ucdr_deserialize_double(reader, &topic->double_value);

        (void) ucdr_deserialize_string(reader, (char*)topic->string_value.c_str(), 512);
        (void) ucdr_deserialize_array_uint8_t(reader, topic->byte_array_value.data(), param_count_max);
        (void) ucdr_deserialize_array_bool(reader, topic->bool_array_value, sizeof(bool_array_value));
        (void) ucdr_deserialize_array_int64_t(reader, topic->integer_array_value.data(), param_count_max);
        (void) ucdr_deserialize_array_double(reader, topic->double_array_value.data(), param_count_max);
        //(void) ucdr_deserialize_sequence_char(reader, topic->string_array_value.c_str(), sizeof(topic->string_array_value)/sizeof(char), &str_array_size);
        (void) ucdr_deserialize_string(reader, (char*)topic->string_array_value[0].c_str(), 512);

        return !reader->error;
    }

    uint32_t size_of_topic(const ParameterValue* topic, uint32_t size)
    {
        (void) (topic);

        uint32_t previousSize = size;
        size += ucdr_alignment(size, 1) + 1;
        size += ucdr_alignment(size, 1) + 1;
        size += ucdr_alignment(size, 8) + 8;
        size += ucdr_alignment(size, 8) + 8;
        size += ucdr_alignment(size, 4) + 4 + (uint32_t)(topic->string_value.length() + 1);
        size += ucdr_alignment(size, 1) + (10 * 1);
        size += ucdr_alignment(size, 1) + (10 * 1);
        size += ucdr_alignment(size, 8) + (10 * 8);
        size += ucdr_alignment(size, 8) + (10 * 8);
        size += ucdr_alignment(size, 4) + 4;
        for(size_t i = 0; i < topic->string_array_value.size(); i++)
        {
            size += ucdr_alignment(size, 4) + 4  + (topic->string_array_value[i].length() * 1);
        }
        

        return size - previousSize;
    }

};

} // namespace rcl_interfaces

#endif // _RCL_INTERFACES_PARAMETERVALUE_H_
*/