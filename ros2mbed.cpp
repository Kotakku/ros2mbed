#include "ros2mbed.h"

#if MBED_CONF_NSAPI_PRESENT
bool ros2::init(NetworkInterface* comm_instance, const char* p_server_ip, uint16_t server_port/*, bool is_tcp*/)
{
#if USER_TRANSPORT_TYPE == 0
  return ros2::init((void*)comm_instance, p_server_ip, server_port, false);
#endif 

#if USER_TRANSPORT_TYPE == 1
  return ros2::init((void*)comm_instance, p_server_ip, server_port, true);
#endif 

    return false;
}
#endif //MBED_CONF_NSAPI_PRESENT