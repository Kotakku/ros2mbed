#include "transport_mbed_internal.h"
#include "mbed.h"
// #include <Udp.h>
// #include <Client.h>
#include <xrcedds/dds_time.h>
#include <ctime>
#include "user_config.h"


static USER_SERIAL_TYPE *p_serial;

extern DigitalOut led[3];

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

  //printf("tx: %d\n", tx_len);
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
  
  if(rv > 0)
    printf("rv: %d\n", rv);
  return rv;
}


#if MBED_CONF_NSAPI_PRESENT
static NetworkInterface *udp_interface;
static SocketAddress udp_remote_addr;
static UDPSocket *udp_socket;
static bool is_udp_connect = false;
static Mutex recv_mutex;
static Thread recv_thread;
static CircularBuffer<uint8_t, USER_TRANSPORT_MTU> recv_buf;

void udp_recv_thread()
{
    uint8_t buf[USER_TRANSPORT_MTU];
    while(1)
    {
        if(udp_interface)
        {
            size_t count = udp_socket->recv(buf, USER_TRANSPORT_MTU);
            recv_mutex.lock();
            for(size_t i = 0; i < count; i++)
            {
                //printf("/");
                recv_buf.push(buf[i]);
            }
            //printf("a%d\n", recv_buf.size());
            recv_mutex.unlock();
        }
        ThisThread::sleep_for(1ms);
    }
}

bool uxr_initUdpMbed(void* udp_instance, const char* ip_address, uint16_t port)
{
  nsapi_size_or_error_t result;

  if(udp_instance == nullptr)
  {
    return false;
  }

  udp_interface = (NetworkInterface*)udp_instance;

  udp_interface->set_network("192.168.2.10", "255.255.255.0", "192.168.2.1");
  udp_remote_addr.set_ip_address(ip_address);
  udp_remote_addr.set_port(port);
  result = udp_interface->connect();

    /*
    SocketAddress a;
        udp_interface->get_ip_address(&a);
        printf("IP address: %s\n", a.get_ip_address() ? a.get_ip_address() : "None");
        udp_interface->get_netmask(&a);
        printf("Netmask:    %s\n", a.get_ip_address() ? a.get_ip_address() : "None");
        udp_interface->get_gateway(&a);
        printf("Gateway:    %s\n\n", a.get_ip_address() ? a.get_ip_address() : "None");
        printf("Agent:      %s:%d\n", udp_remote_addr.get_ip_address() ? udp_remote_addr.get_ip_address() : "None", udp_remote_addr.get_port());
    */

  if(result >= 0)
  {
    udp_socket = new UDPSocket();
    result = udp_socket->open(udp_interface);
    
    if(result >= 0)
    {
      //is_udp_connect = true;
      
      
      result = udp_socket->connect(udp_remote_addr);

      if (result >= 0)
      {
          is_udp_connect = true;
          recv_thread.start(udp_recv_thread);
      }
    }    
  }
  
  //printf("[uxr_initUdpMbed]: %d\n", is_udp_connect);
  /*
  char str[] = "teststr";
  uxr_writeUdpDataMbed((uint8_t*)str, sizeof(str));

  ThisThread::sleep_for(1s);
  uxr_writeUdpDataMbed((uint8_t*)str, sizeof(str));
  */

  ThisThread::sleep_for(5s);
  return is_udp_connect;
}

bool uxr_closeUdpMbed()
{
  //p_udp->stop();
  udp_socket->close();
  delete udp_socket;
  recv_thread.join();
  is_udp_connect = false;

  return true;
}

size_t uxr_writeUdpDataMbed(const uint8_t* buf, size_t len)
{
  int tx_len = 0;

  //led[0] = 1;

  //printf("[uxr_writeUdpDataMbed] len:%d\n", len);
  //printf("Agent:      %s:%d\n", udp_remote_addr.get_ip_address() ? udp_remote_addr.get_ip_address() : "None", udp_remote_addr.get_port());

  //tx_len = udp_socket->sendto(udp_remote_addr, buf, len);
  tx_len = udp_socket->send(buf, len);

  //printf("==> tx_len:%d\n", tx_len);

  //led[0] = 0;

  return (tx_len > 0 ? tx_len : 0);
}

size_t uxr_readUdpDataMbed(uint8_t* buf, size_t len, int timeout)
{
  size_t rv = 0;
  //led[1] = 1;
  //printf("<== [uxr_readUdpDataMbed] len: %d, timeout: %d\n", len, timeout);
  //int count = 0;
  uint32_t pre_time = dds_getMilliseconds();

    
  //printf("<== [uxr_readUdpDataMbed] len: %d, timeout: %d\n", len, timeout);
  //printf("r\n");
  while ((rv <= 0 && (dds_getMilliseconds() - pre_time < (uint32_t)timeout))) // || count == 0)
  {
      //ThisThread::sleep_for(1ms);
      recv_mutex.lock();
      rv = recv_buf.size();
      recv_mutex.unlock();
      //count++;
  }
  
  recv_mutex.lock();
  for(size_t i = 0; i < rv; i++)
  {
    //printf("b");
    recv_buf.pop(buf[i]);
  }
  //printf("\n");
  recv_mutex.unlock();

  //if(rv > 0)
    //printf("rv: %d(%d)\n", rv, count);

  //led[1] = 0;

  return (rv > 0 ? rv : 0);
}

static NetworkInterface *client_interface;
static TCPSocket *tcp_socket;
static bool is_tcp_connect = false;
SocketAddress tcp_addr;

bool uxr_connectTcpMbed(void* client_instance, const char* ip_address, uint16_t port)
{
  nsapi_size_or_error_t result;

  printf("[uxr_connectTcpMbed]\n");
  if(client_instance == nullptr)
  {
    printf("Client instance is NULL, please \"ros2::init();\" before create Node instance.");
    return false;
  }

  client_interface = (NetworkInterface*)client_instance;
  client_interface->set_network("192.168.2.10", "255.255.255.0", "192.168.2.1");
  tcp_addr.set_ip_address(ip_address);
  tcp_addr.set_port(port);

  //rv = client_interface->connect(ip_address, port);
  result = client_interface->connect();


  SocketAddress a;
    client_interface->get_ip_address(&a);
    printf("IP address: %s\n", a.get_ip_address() ? a.get_ip_address() : "None");
    client_interface->get_netmask(&a);
    printf("Netmask:    %s\n", a.get_ip_address() ? a.get_ip_address() : "None");
    client_interface->get_gateway(&a);
    printf("Gateway:    %s\n\n", a.get_ip_address() ? a.get_ip_address() : "None");

  if(result >= 0)
  {
    
    tcp_socket = new TCPSocket();
    result = tcp_socket->open(client_interface);

    if(result >= 0)
    {
      is_tcp_connect = true;

      /*
      result = tcp_socket->connect(addr);

      if (result >= 0)
        is_tcp_connect = true;
      else
      {
        printf("[uxr_connectTcpMbed] socket connect error: %d\n", result);
      }  
      */
    } 
    else
    {
        printf("[uxr_connectTcpMbed] socket open error: %d\n", result);
    }  
  }
  else
  {
      printf("[uxr_connectTcpMbed] connect error: %d\n", result);
  }
  
  printf("[uxr_connectTcpMbed] ret: %d\n", is_tcp_connect);
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

  printf("[uxr_writeTcpDataMbed] len:%d\n", len);

  if(is_tcp_connect)
    tx_len = tcp_socket->sendto(tcp_addr,buf, len);

  printf("[uxr_writeTcpDataMbed] tx_len:%d\n", tx_len);
    
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


  printf("[uxr_readTcpDataMbed] len: %d, timeout: %d\n", len, timeout);

  while (rv <= 0 && (dds_getMilliseconds() - pre_time < (uint32_t)timeout))
  {
    rv = tcp_socket->recv(buf, len);
  }

  printf("[uxr_readTcpDataMbed] rv: %d\n", rv);
  
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