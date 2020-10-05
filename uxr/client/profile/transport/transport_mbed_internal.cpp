#include "transport_mbed_internal.h"
#include "mbed.h"
// #include <Udp.h>
// #include <Client.h>
#include <xrcedds/dds_time.h>
#include <ctime>
#include "user_config.h"


static USER_SERIAL_TYPE *p_serial;

bool uxr_initSerialMbed(void *serial_instance)
{
  bool rv = true;

  if(serial_instance == NULL)
    printf("serial instance is NULL, please \"ros2::init();\" before create Node instance.");
  p_serial = (USER_SERIAL_TYPE*) serial_instance;

  return rv;
}

bool uxr_closeSerialMbed()
{
  bool rv = true;

  return rv;
}

size_t uxr_writeSerialDataMbed(uint8_t* buf, size_t len)
{
  size_t tx_len = 0;

  tx_len = p_serial->write(buf, len);
  //p_serial->flush(); // not exit flush function ?

  return tx_len;
}

size_t uxr_readSerialDataMbed(uint8_t* buf, size_t len, int timeout)
{
  size_t rv = 0;

  uint32_t pre_time = dds_getMilliseconds();

  while (rv <= 0 && (dds_getMilliseconds() - pre_time < (uint32_t)timeout))
  {
    rv = p_serial->readable();
  }

  if(rv > len)
  {
    rv = len;
  }

  if (0 < rv)
  {
    // for (size_t i = 0; i < rv; i++)
    // {
    //   buf[i] = p_serial->read();
    // }
    p_serial->read(buf, rv);
  }
  
  return rv;
}


#if MBED_CONF_NSAPI_PRESENT

static NetworkInterface *udp_interface;
static SocketAddress udp_remote_addr;
static UDPSocket *udp_socket;
static bool is_udp_connect = false;

bool uxr_initUdpMbed(void* udp_instance, const char* ip_address, uint16_t port)
{
  nsapi_size_or_error_t result;

  if(udp_instance == nullptr)
  {
    return false;
  }

  udp_interface = (NetworkInterface*)udp_instance;
  udp_remote_addr.set_ip_address(ip_address);
  udp_remote_addr.set_port(port);
// #if defined(ESP_PLATFORM)
//   WiFiUDP *p_wifi_udp = (WiFiUDP*)udp_instance;
//   p_wifi_udp->begin(WiFi.localIP(), local_port);
// #else
//   p_udp->begin(local_port);
// #endif


  result = udp_interface->connect();

  if(result >= 0)
  {
    udp_socket = new UDPSocket();
    result = udp_socket->open(udp_interface);

    if(result >= 0)
    {
      result = udp_socket->connect(udp_remote_addr);

      if (result >= 0)
        is_udp_connect = true;
    }    
  }

  return is_udp_connect;
}

bool uxr_closeUdpMbed()
{
  //p_udp->stop();
  udp_socket->close();
  delete udp_socket;
  is_udp_connect = false;

  return true;
}

size_t uxr_writeUdpDataMbed(const uint8_t* buf, size_t len)
{
  size_t tx_len = 0;

#warning Todo:
  // p_udp->beginPacket(remote_ip_addr, remote_port);
  // tx_len = p_udp->write(buf, len);
  // p_udp->endPacket();

  return tx_len;
}

size_t uxr_readUdpDataMbed(uint8_t* buf, size_t len, int timeout)
{
  size_t rv = 0;
  uint32_t pre_time = dds_getMilliseconds();

#warning Todo:
  // while (rv <= 0 && (dds_getMilliseconds() - pre_time < (uint32_t)timeout))
  // {
  //   p_udp->parsePacket();
  //   rv = p_udp->available();
  // }

  // if(rv > len)
  // {
  //   rv = len;
  // }

  // if (0 < rv)
  // {
  //   p_udp->read(buf, len);
  // }
  
  return rv;
}

static NetworkInterface *client_interface;
static TCPSocket *tcp_socket;
static bool is_tcp_connect = false;

bool uxr_connectTcpMbed(void* client_instance, const char* ip_address, uint16_t port)
{
  nsapi_size_or_error_t result;

  if(client_instance == nullptr)
  {
    printf("Client instance is NULL, please \"ros2::init();\" before create Node instance.");
    return false;
  }

  client_interface = (NetworkInterface*)client_instance;

  //rv = client_interface->connect(ip_address, port);
  result = client_interface->connect();

  if(result >= 0)
  {
    SocketAddress addr(ip_address, port);
    tcp_socket = new TCPSocket();
    result = tcp_socket->open(client_interface);

    if(result >= 0)
    {
      result = tcp_socket->connect(addr);

      if (result >= 0)
        is_tcp_connect = true;
    }    
  }

  return is_tcp_connect;
}

bool uxr_closeTcpMbed()
{
  //p_client->stop();
  tcp_socket->close();
  delete tcp_socket;
  is_tcp_connect = false;

  return true;
}

size_t uxr_writeTcpDataMbed(const uint8_t* buf, size_t len)
{
  int tx_len = 0;

//   if(p_client->connected())
//   {
//     tx_len = p_client->write(buf, len);
//   }

  if(is_tcp_connect)
    tx_len = tcp_socket->send(buf, len);
    
  return (tx_len >= 0 ? tx_len : 0);
}

size_t uxr_readTcpDataMbed(uint8_t* buf, size_t len, int timeout)
{
  int rv = 0;
  uint32_t pre_time = dds_getMilliseconds();

  // while (rv <= 0 && (dds_getMilliseconds() - pre_time < (uint32_t)timeout))
  // {
  //   //rv = p_client->available();
  // }

  // if(rv > len)
  // {
  //   rv = len;
  // }

  // if (0 < rv)
  // {
  //   rv = tcp_socket->read(buf, len);
  // }

  rv = tcp_socket->recv(buf, len);
  
  return (rv >= 0 ? rv : 0);
}

bool uxr_disconnectTcpMbed()
{
  //p_client->stop();
  client_interface->disconnect();
  is_tcp_connect = false;
  return true;
}

#endif