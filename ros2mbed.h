#ifndef ROS2Mbed_h
#define ROS2Mbed_h

#include <ros2/ros2.hpp>
#include "mbed.h"

namespace ros2 {

#if MBED_CONF_NSAPI_PRESENT
bool init(NetworkInterface* comm_instance, const char* p_server_ip, uint16_t server_port);
#endif //MBED_CONF_NSAPI_PRESENT

} /* namespace ros2 */

#endif //ROS2Mbed_h