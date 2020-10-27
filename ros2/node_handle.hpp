/*
 * node_handle.hpp
 *
 *  Created on: May 16, 2018
 *      Author: Kei
 */

#ifndef ROS2_NODE_HANDLE_HPP_
#define ROS2_NODE_HANDLE_HPP_

#include <stdio.h>
#include "xrcedds/xrcedds.hpp"
#include "xrcedds/dds_time.h"
#include <functional>

namespace ros2 {

enum MessagePrefix{
  TOPICS_PUBLISH = 0,
  TOPICS_SUBSCRIBE,
  SERVICE_REQUEST,
  SERVICE_RESPONSE,
  SERVICE,
  PARAMETER,
  ACTION
};
const char* getPrefixString(MessagePrefix prefix);

class PublisherHandle
{
 
public:
  PublisherHandle()
    : is_registered_(false), writer_id_(0)
  {
    pub_msg_cnt_ = 0;
  }
  virtual ~PublisherHandle(){}

  virtual void recreate(void) = 0;
  virtual void destroy(void) = 0;

  bool is_registered_;
  uint32_t pub_msg_cnt_;
  uint16_t writer_id_;
  const char* name_;
};

class SubscriptionHandle
{

public:
  SubscriptionHandle()
    : is_registered_(false), request_id_(0), reader_id_(0)
  {
    sub_msg_cnt_ = 0;
  }
  virtual ~SubscriptionHandle(){};

  virtual void recreate(void) = 0;
  virtual void subscribe(void) = 0;
  virtual void destroy(void) = 0;

  virtual void runCallback(void* serialized_msg) = 0;

  bool is_registered_;
  uint32_t sub_msg_cnt_;
  uint16_t request_id_;
  uint16_t reader_id_;
  const char* name_;
};

} // namespace ros2

#endif /* ROS2_NODE_HANDLE_HPP_ */
