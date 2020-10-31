#include "xrcedds_cpp_helper.hpp"


extern void ucdr_array_to_buffer(ucdrBuffer* ub, const uint8_t* array, size_t size, size_t data_size);
extern void ucdr_deserialize_sequence_header(ucdrBuffer* ub, ucdrEndianness endianness, size_t capacity, uint32_t* length);
extern void ucdr_buffer_to_array(ucdrBuffer* ub, uint8_t* array, size_t size, size_t data_size);

bool ucdr_serialize_vec_uint8_t(ucdrBuffer *ub, std::vector<uint8_t>& vec)
{
    // vector size header
    ucdr_serialize_endian_uint32_t(ub, ub->endianness, vec.size());

    // data
    ucdr_array_to_buffer(ub, (uint8_t*)vec.data(), vec.size(), 1);
    return !ub->error;
}

bool ucdr_serialize_vec_int8_t(ucdrBuffer *ub, std::vector<int8_t>& vec)
{
    ucdr_serialize_endian_uint32_t(ub, ub->endianness, vec.size());

    ucdr_array_to_buffer(ub, (uint8_t*)vec.data(), vec.size(), 1);
    return !ub->error;
}

#define UCDR_SERIALIZE_VEC_BYTE_N(TYPE, TYPE_SIZE, ENDIAN) \
    size_t alignment = ucdr_buffer_alignment(ub, TYPE_SIZE); \
    ub->iterator += alignment; \
    ub->offset += alignment; \
    if(UCDR_MACHINE_ENDIANNESS == ENDIAN) \
    { \
        for(size_t i = 0; i < vec.size(); i++)\
        {\
            ucdr_serialize_ ## TYPE(ub, vec[i]); \ 
        }\
    } \
    else \
    { \
        for(uint32_t i = 0; i < vec.size(); ++i) \
        { \
            ucdr_serialize_endian_ ## TYPE(ub, ENDIAN, vec[i]); \
        } \
    } \
    return !ub->error;

#define UCDR_SERIALIZE_VEC_DEFINITION(SUFFIX, TYPE, SIZE) \
    bool ucdr_serialize_vec ## SUFFIX(ucdrBuffer* ub, std::vector<TYPE>& vec) \
    { \
        ucdr_serialize_endian_uint32_t(ub, ub->endianness, vec.size()); \
        UCDR_SERIALIZE_VEC_BYTE_N(TYPE, SIZE, ub->endianness) \
    } 

bool ucdr_deserialize_vec_uint8_t(ucdrBuffer *ub, std::vector<uint8_t>& vec)
{
    uint32_t length;
    ucdr_deserialize_sequence_header(ub, ub->endianness, vec.max_size(), &length);
    vec.resize(length);
    //ucdr_buffer_to_array(ub, (uint8_t*)vec.data(), vec.size(), 1);
    for(size_t i = 0; i < length; i++)
    {
        uint8_t tmp;
        ucdr_deserialize_uint8_t(ub, &tmp);
        vec[i] = tmp; 
    }
    return !ub->error;
}

bool ucdr_deserialize_vec_int8_t(ucdrBuffer *ub, std::vector<int8_t>& vec)
{
    uint32_t length;
    ucdr_deserialize_sequence_header(ub, ub->endianness, vec.max_size(), &length);
    vec.resize(length);
    //ucdr_buffer_to_array(ub, (uint8_t*)vec.data(), vec.size(), 1);
    for(size_t i = 0; i < length; i++)
    {
        int8_t tmp;
        ucdr_deserialize_int8_t(ub, &tmp);
        vec[i] = tmp; 
    }
    return !ub->error;
}

#define UCDR_DESERIALIZE_VEC_BYTE_N(TYPE, TYPE_SIZE, ENDIAN) \
        size_t alignment = ucdr_buffer_alignment(ub, TYPE_SIZE); \
        ub->iterator += alignment; \
        ub->offset += alignment; \
        if(UCDR_MACHINE_ENDIANNESS == ENDIAN) \
        { \
            for(size_t i = 0; i < vec.size(); i++)\
            {\
                TYPE tmp; \
                ucdr_deserialize_ ## TYPE(ub, &tmp); \ 
                vec[i] = tmp; \
            }\
        } \
        else \
        { \
            for(uint32_t i = 0; i < vec.size(); ++i) \
            { \
                ucdr_deserialize_endian_ ## TYPE(ub, ENDIAN, &vec[i]); \
            } \
        } \
        return !ub->error; 

#define UCDR_DESERIALIZE_VEC_DEFINITION(SUFFIX, TYPE, SIZE) \
    bool ucdr_deserialize_vec ## SUFFIX(ucdrBuffer *ub, std::vector<TYPE>& vec) \
    { \
        uint32_t length; \
        ucdr_deserialize_sequence_header(ub, ub->endianness, vec.max_size(), &length); \
        vec.resize(length); \
        UCDR_DESERIALIZE_VEC_BYTE_N(TYPE, SIZE, ub->endianness)\
    }

#define UCDR_SERI_VEC_DEFINITION(UFFIX, TYPE, SIZE) \
    UCDR_SERIALIZE_VEC_DEFINITION(UFFIX, TYPE, SIZE) \
    UCDR_DESERIALIZE_VEC_DEFINITION(UFFIX, TYPE, SIZE)

UCDR_SERI_VEC_DEFINITION(_uint16_t, uint16_t, 2)
UCDR_SERI_VEC_DEFINITION(_int16_t,  int16_t,  2)
UCDR_SERI_VEC_DEFINITION(_uint32_t, uint32_t, 4)
UCDR_SERI_VEC_DEFINITION(_int32_t,  int32_t,  4)
UCDR_SERI_VEC_DEFINITION(_uint64_t, uint64_t, 4)
UCDR_SERI_VEC_DEFINITION(_int64_t,  int64_t,  4)
UCDR_SERI_VEC_DEFINITION(_float, float, 4)
UCDR_SERI_VEC_DEFINITION(_double, double, 4)

bool ucdr_serialize_string(ucdrBuffer* ub, std::string& str)
{
    return ucdr_serialize_sequence_char(ub, str.data(), str.length());
}

bool ucdr_deserialize_string(ucdrBuffer* ub, std::string& str)
{
    uint32_t length;
    char c;

    ucdr_deserialize_sequence_header(ub, ub->endianness, str.max_size(), &length);

    str.resize(length);
    for(size_t i = 0; i < length; i++)
    {
        ucdr_deserialize_char(ub, &c);
        str[i] = c;
    }
        
    return !ub->error;
}

bool ucdr_serialize_vec_string(ucdrBuffer* ub, std::vector<std::string>& str)
{
    bool is_error = false;
    for(size_t i = 0; i < str.size(); i++)
    {
        is_error &= !ucdr_deserialize_string(ub, str[i]);
    }

    return !is_error;
}

bool ucdr_deserialize_vec_string(ucdrBuffer* ub, std::vector<std::string>& str)
{
    uint32_t length;
    ucdr_deserialize_sequence_header(ub, ub->endianness, str.max_size(), &length);

    str.resize(length);
    for(size_t i = 0; i < str.size(); i++)
    {
        ucdr_deserialize_string(ub, str[i]);
    }
    return !ub->error;
}