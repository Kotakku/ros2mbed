#ifndef XRCEDDS_CPP_HELPER_H
#define XRCEDDS_CPP_HELPER_H

#include <ucdr/microcdr.h>

#include <cstdint>
#include <vector>
#include <string>

#define UCDR_SERIALIZE_VEC_PROTO_DEFINITION(SUFFIX, TYPE) \
    bool ucdr_serialize_vec ## SUFFIX(ucdrBuffer *ub, std::vector<TYPE>& vec);

#define UCDR_DESERIALIZE_VEC_PROTO_DEFINITION(SUFFIX, TYPE) \
    bool ucdr_deserialize_vec ## SUFFIX(ucdrBuffer *ub, std::vector<TYPE>& vec);

#define UCDR_SERI_VEC_PROTO_DEFINITION(SUFFIX, TYPE) \
    UCDR_SERIALIZE_VEC_PROTO_DEFINITION(SUFFIX, TYPE) \
    UCDR_DESERIALIZE_VEC_PROTO_DEFINITION(SUFFIX, TYPE)
    
UCDR_SERI_VEC_PROTO_DEFINITION(_uint8_t, uint8_t)
UCDR_SERI_VEC_PROTO_DEFINITION( _int8_t,  int8_t)
UCDR_SERI_VEC_PROTO_DEFINITION(_uint16_t, uint16_t)
UCDR_SERI_VEC_PROTO_DEFINITION( _int16_t,  int16_t)
UCDR_SERI_VEC_PROTO_DEFINITION(_uint32_t, uint32_t)
UCDR_SERI_VEC_PROTO_DEFINITION( _int32_t,  int32_t)
UCDR_SERI_VEC_PROTO_DEFINITION(_uint64_t, uint64_t)
UCDR_SERI_VEC_PROTO_DEFINITION( _int64_t,  int64_t)
UCDR_SERI_VEC_PROTO_DEFINITION(_float, float)
UCDR_SERI_VEC_PROTO_DEFINITION(_double, double)

bool ucdr_serialize_string(ucdrBuffer* ub, std::string& str);
bool ucdr_deserialize_string(ucdrBuffer* ub, std::string& str);

bool ucdr_serialize_vec_string(ucdrBuffer* ub, std::vector<std::string>& str);
bool ucdr_deserialize_vec_string(ucdrBuffer* ub, std::vector<std::string>& str);

#endif // XRCEDDS_CPP_HELPER_H
