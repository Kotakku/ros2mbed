#ifndef _SRC_C_PROFILE_TRANSPORT_TRANSPORT_MBED_INTERNAL_H_
#define _SRC_C_PROFILE_TRANSPORT_TRANSPORT_MBED_INTERNAL_H_

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

bool uxr_initSerialMbed(void *serial_instance);
bool uxr_closeSerialMbed();
size_t uxr_writeSerialDataMbed(uint8_t* buf, size_t len);
size_t uxr_readSerialDataMbed(uint8_t* buf, size_t len, int timeout);

bool uxr_initUdpMbed(void* udp_instance, const char* ip_address, uint16_t port);
bool uxr_closeUdpMbed();
size_t uxr_writeUdpDataMbed(const uint8_t* buf, size_t len);
size_t uxr_readUdpDataMbed(uint8_t* buf, size_t len, int timeout);

bool uxr_connectTcpMbed(void* client_instance, const char* ip_address, uint16_t port);
bool uxr_closeTcpMbed();
size_t uxr_writeTcpDataMbed(const uint8_t* buf, size_t len);
size_t uxr_readTcpDataMbed(uint8_t* buf, size_t len, int timeout);
bool uxr_disconnectTcpMbed();

#ifdef __cplusplus
}
#endif

#endif //_SRC_C_PROFILE_TRANSPORT_TRANSPORT_MBED_INTERNAL_H_
