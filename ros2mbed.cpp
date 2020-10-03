#include "ros2mbed.h"

bool ros2::init(NetworkInterface* comm_instance, const char* p_server_ip, uint16_t server_port, bool is_tcp)
{
  return ros2::init((void*)comm_instance, p_server_ip, server_port, is_tcp);
}