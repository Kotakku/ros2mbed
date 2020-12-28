/*
 * ros2.cpp
 *
 *  Created on: Jul 6, 2018
 *      Author: kei
 */

#include "ros2.hpp"
#include "TimerBase.h"
#include "mbed.h"
#include "node_handle.hpp"
#include <string>

static xrcedds::XrceDdsCommportType g_client_communication_method;
static const char* g_server_ip;
static char g_server_port[6]; // Size to 16-bit number
static void* g_comm_instance;

static builtin_interfaces::Time synced_time_from_remote;
static uint32_t millis_when_synced_time;


bool ros2::init(void* comm_instance)
{
  g_client_communication_method = xrcedds::XRCE_DDS_COMM_SERIAL;
  g_comm_instance = (void*)comm_instance;

  return true;
}

bool ros2::init(void* comm_instance, const char* p_server_ip, uint16_t server_port, bool enable_tcp)
{
  if(enable_tcp == false)
  {
    g_client_communication_method = xrcedds::XRCE_DDS_COMM_UDP;
  }
  else
  {
    g_client_communication_method = xrcedds::XRCE_DDS_COMM_TCP;
  }

  g_server_ip = p_server_ip;
  sprintf(g_server_port, "%d", server_port);
  g_comm_instance = (void*)comm_instance;

  return true;
}

void ros2::spin(ros2::Node *node)
{
  while(1)
  {
    spin_once(node);
    ThisThread::sleep_for(1ms);
  }
}

void ros2::spin_once(ros2::Node *node)
{
  if(node == nullptr)
    return;

  node->run_timer_callback();

  if(xrcedds::runCommunication(1) == false)
  {
    //node->recreate();
  }
}

void ros2::syncTimeFromRemote(builtin_interfaces::Time* msg)
{
  millis_when_synced_time         = dds_getMilliseconds();
  synced_time_from_remote.sec     = msg->sec;
  synced_time_from_remote.nanosec = msg->nanosec;
}

builtin_interfaces::Time ros2::now()
{
  builtin_interfaces::Time ret_time = synced_time_from_remote;
  uint32_t msec_offset = dds_getMilliseconds() - millis_when_synced_time;
  uint32_t remain_msec = msec_offset%1000;

  ret_time.sec += (int32_t)(msec_offset/(uint32_t)1000);
  if((ret_time.nanosec/(uint32_t)1000000 + remain_msec) < 1000)
  {
    ret_time.nanosec += (uint32_t)(remain_msec*(uint32_t)1000000);
  }
  else // >= 1sec
  {
    ret_time.sec += 1;
    ret_time.nanosec = (uint32_t)(ret_time.nanosec + remain_msec*(uint32_t)1000000 - (uint32_t)1000000000);
  }

  return ret_time;
}

const char* ros2::getPrefixString(MessagePrefix prefix)
{
  switch(prefix)
  {
    case ros2::TOPICS_PUBLISH:
      return "rt";

    case ros2::TOPICS_SUBSCRIBE:
      return "rt";

    case ros2::SERVICE_REQUEST:
      return "rq";

    case ros2::SERVICE_RESPONSE:
      return "rr";

    case ros2::SERVICE:
      return "rs";

    case ros2::PARAMETER:
      return "rp";

    case ros2::ACTION:
      return "ra";
  }

  return "";
}


void ros2::runNodeSubUserCallback(uint16_t id, void* msgs, void* args)
{
  ros2::Node* p_node = (ros2::Node*) args;

  if(p_node != nullptr)
  {
    p_node->run_sub_callback(id, msgs);
  }
}


/* Node class */
ros2::Node::Node(const std::string node_name,unsigned int client_key)
{
  pub_cnt_ = 0, sub_cnt_ = 0, node_register_state_ = false;
  for(size_t i = 0; i < ROS2_PUBLISHER_MAX; i++)
  {
    pub_list_[i] = nullptr;
  }
  for(size_t i = 0; i < ROS2_SUBSCRIBER_MAX; i++)
  {
    sub_list_[i] = nullptr;
  }

  this->recreate(node_name.c_str(),client_key);
}

bool ros2::Node::getNodeRegisteredState()
{
  return node_register_state_;
}

void ros2::Node::recreate(const char* node_name, unsigned int client_key)
{
  xrcedds_participant_.is_created = false;
  xrcedds_transport_.type = g_client_communication_method;

  switch (xrcedds_transport_.type)
  {
    case xrcedds::XRCE_DDS_COMM_SERIAL:
      break;

    case xrcedds::XRCE_DDS_COMM_UDP:
    case xrcedds::XRCE_DDS_COMM_TCP:
      xrcedds_transport_.server_ip = g_server_ip;
      xrcedds_transport_.server_port = (const char*)g_server_port;
      break;

    default:
      return;
  }

  xrcedds_transport_.comm_instance = g_comm_instance;

  xrcedds::init(0, client_key);
  xrcedds::initTransportAndSession(&xrcedds_transport_,
      (void*) runNodeSubUserCallback, (void*) this);

  node_register_state_ = xrcedds::createParticipant(&this->xrcedds_participant_, node_name);

  if(node_register_state_ == true){
    xrcedds::createPublisher(&this->xrcedds_participant_,
        &this->xrcedds_publisher_);
    xrcedds::createSubscriber(&this->xrcedds_participant_,
        &this->xrcedds_subscriber_);

    uint8_t i;
    for (i = 0; i < ROS2_PUBLISHER_MAX; i++)
    {
      if (pub_list_[i])
      {
        static_cast<PublisherHandle*>(pub_list_[i].get())->recreate();
      }
    }

    for (i = 0; i < ROS2_SUBSCRIBER_MAX; i++)
    {
      if (sub_list_[i])
      {
        static_cast<SubscriptionHandle*>(sub_list_[i].get())->recreate();
      }
    }
  }
}

void ros2::Node::run_timer_callback()
{
  uint8_t i;
  ros2::TimerBase::SharedPtr p_timer;
  for(i = 0; i < ROS2_TIMER_MAX; i++)
  {
    p_timer = timer_list_[i];
    if(p_timer && p_timer->isTimeToCallback())
    {
        p_timer->call();
        break;
    }
  }
}

void ros2::Node::run_sub_callback(uint16_t reader_id, void* serialized_msg)
{
  uint8_t i;
  ros2::SubscriptionHandle *p_sub;
  for(i = 0; i < ROS2_SUBSCRIBER_MAX; i++)
  {
    p_sub = static_cast<ros2::SubscriptionHandle *>(sub_list_[i].get());
    if(sub_list_[i] && p_sub->is_registered_ && p_sub->reader_id_ == reader_id)
    {
      p_sub->runCallback(serialized_msg);
    }
  }
}


void ros2::Node::delete_publisher(const std::string name)
{
  PublisherHandle *publisher;

  for(uint8_t i = 0; i < ROS2_SUBSCRIBER_MAX; i++)
  {
    publisher = static_cast<ros2::PublisherHandle *>(pub_list_[i].get());
    if(publisher != nullptr && !strcmp(publisher->name_, name.c_str()))
    {
      publisher->destroy();
      pub_list_[i].reset();
      pub_cnt_--;
      break;
    }
  }
}


void ros2::Node::delete_publisher(uint16_t writer_id)
{
  PublisherHandle *publisher;

  for(uint8_t i = 0; i < ROS2_SUBSCRIBER_MAX; i++)
  {
    publisher = static_cast<ros2::PublisherHandle *>(pub_list_[i].get());
    if(publisher != nullptr && publisher->writer_id_ == writer_id)
    {
      publisher->destroy();
      pub_list_[i].reset();
      pub_cnt_--;
      break;
    }
  }
}

void ros2::Node::delete_subscriber(const std::string name)
{
  SubscriptionHandle *subscriber;

  for(uint8_t i = 0; i < ROS2_SUBSCRIBER_MAX; i++)
  {
    subscriber = static_cast<ros2::SubscriptionHandle *>(sub_list_[i].get());
    if(subscriber != nullptr && !strcmp(subscriber->name_, name.c_str()))
    {
      subscriber->destroy();
      sub_list_[i].reset();
      sub_cnt_--;
      break;
    }
  }
}

void ros2::Node::delete_subscriber(uint16_t reader_id)
{
  SubscriptionHandle *subscriber;

  for(uint8_t i = 0; i < ROS2_SUBSCRIBER_MAX; i++)
  {
    subscriber = static_cast<ros2::SubscriptionHandle *>(sub_list_[i].get());
    if(subscriber != nullptr && subscriber->reader_id_ == reader_id)
    {
      subscriber->destroy();
      sub_list_[i].reset();
      sub_cnt_--;
      break;
    }
  }
}

