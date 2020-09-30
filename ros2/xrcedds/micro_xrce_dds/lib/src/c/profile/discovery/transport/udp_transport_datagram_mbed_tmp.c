#include "udp_transport_datagram_internal.h"
#include "ip.h"

bool uxr_init_udp_transport_datagram(
        struct uxrUDPTransportDatagram* transport) { return false; }

bool uxr_udp_send_datagram_to(
        struct uxrUDPTransportDatagram* transport,
        const uint8_t* buf,
        size_t length,
        const TransportLocator* locator) { return false; }

bool uxr_udp_recv_datagram(
        struct uxrUDPTransportDatagram* transport,
        uint8_t** buf,
        size_t* len,
        int timeout) { return false; }

void uxr_bytes_to_ip(
        const uint8_t* bytes,
        char* ip) { }

bool uxr_ip_to_locator(
        char const * ip,
        uint16_t port,
        uxrIpProtocol ip_protocol,
        TransportLocator * locator) { return false; }
