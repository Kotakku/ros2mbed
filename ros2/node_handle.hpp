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

//typedef void(*CallbackFunc)(void* msg, void* arg);

template<typename MsgT>
using CallbackFunc = std::function<void(MsgT* msg)>;
//using CallbackFunc = std::function<void(MsgT* msg, void* arg)>;


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
    //callback_arg = nullptr;
    pub_msg_cnt_ = 0;
    callback_interval_ms_ = 0;
    last_call_time_ms_ = 0;
  }
  virtual ~PublisherHandle(){}

  //void*        callback_arg;
  virtual void recreate(void) = 0;
  virtual void publish(void) = 0;
  virtual void destroy(void) = 0;

  void setInterval(uint32_t msec)
  {
    this->callback_interval_ms_ = msec;
  }

  bool isTimeToPublish()
  {
    if(this->callback_interval_ms_ > 0 && dds_getMilliseconds() - this->last_call_time_ms_ >= this->callback_interval_ms_)
    {
      this->last_call_time_ms_ = dds_getMilliseconds();
      return true;
    }
    return false;
  }

  bool is_registered_;
  uint32_t pub_msg_cnt_;
  uint16_t writer_id_;
  const char* name_;

private:
  uint32_t last_call_time_ms_;
  uint32_t callback_interval_ms_;
};

class SubscriptionHandle
{

public:
  SubscriptionHandle()
    : is_registered_(false), request_id_(0), reader_id_(0)
  {
    //callback_arg = nullptr;
    sub_msg_cnt_ = 0;
  }
  virtual ~SubscriptionHandle(){};

  //void*        callback_arg;
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
