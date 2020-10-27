/*
 * ros2.hpp
 *
 *  Created on: May 16, 2018
 *      Author: Kei
 */

#ifndef ROS2_HPP_
#define ROS2_HPP_

#include <cstddef>
#include <memory>
#include <string.h>
#include "publisher.hpp"
#include "subscription.hpp"
#include "topic.hpp"
#include "msg_list.hpp"
#include <functional>
#include <chrono>
#include <utility>
#include "TimerBase.h"

#define ROS2_TIMER_MAX      USER_ROS2_TIMER_MAX
#define ROS2_PUBLISHER_MAX  USER_ROS2_PUBLISHER_MAX
#define ROS2_SUBSCRIBER_MAX USER_ROS2_SUBSCRIBER_MAX

namespace ros2 {

bool init(void* serial_dev);
bool init(void* comm_instance, const char* p_server_ip, uint16_t server_port, bool enable_tcp);
void spin(Node *node);
void spin_once(Node *node);
void syncTimeFromRemote(builtin_interfaces::Time* time);
builtin_interfaces::Time now();

void runNodeSubUserCallback(uint16_t id, void* msgs, void* args);

class Node
{
  public:
    Node(const char* node_name = "ros2_xrcedds_participant",unsigned int client_key=0xAABBCCDD);
    virtual ~Node(){};

    bool getNodeRegisteredState();

    TimerBase::SharedPtr create_wall_timer(std::chrono::milliseconds msec, std::function<void(void)> callback)
    {
        TimerBase::SharedPtr timer = std::make_shared<TimerBase>(msec, callback);

        for(size_t i = 0; i < ROS2_TIMER_MAX; i++)
        {
            if(!timer_list_[i])
            {
                timer_list_[i] = timer;
                timer_cnt_++;
                break;
            }
        }

        return timer;
    }

//protected:
    void recreate(const char* node_name = "ros2_xrcedds_participant",unsigned int client_key=0xAABBCCDD);

    void run_timer_callback();
    void run_sub_callback(uint16_t reader_id, void* serialized_msg);

    void delete_publisher(const char* name);
    void delete_publisher(uint16_t writer_id);
    void delete_subscriber(const char* name);
    void delete_subscriber(uint16_t reader_id);

    template <typename MsgT>
    std::shared_ptr<Publisher<MsgT>> create_publisher(const char* name)
    {
      bool ret = false;

      if (this->node_register_state_ == false)
      {
        return nullptr;
      }

      if (pub_cnt_ >= ROS2_PUBLISHER_MAX)
      {
        return nullptr;
      }

      // Register Topic
      ret = this->registerTopic<MsgT>();

      if (ret == false)
      {
        return nullptr;
      }
      
      auto p_pub = std::make_shared<ros2::Publisher<MsgT>>(&this->xrcedds_publisher_, name);

      if (p_pub->is_registered_ == false)
      {
        p_pub.reset();
        return nullptr;
      }

      for (uint8_t i = 0; i < ROS2_PUBLISHER_MAX; i++)
      {
        if (!pub_list_[i])
        {
          pub_list_[i] = p_pub;
          pub_cnt_++;
          break;
        }
      }

      return p_pub;
    }
    
    template <typename MsgT, typename CallbackT>
    std::shared_ptr<Subscription<MsgT>> create_subscription(const char* name, CallbackT callback)
    {
      bool ret = false;

      if(this->node_register_state_ == false)
      {
        return nullptr;
      }

      if(sub_cnt_ >= ROS2_SUBSCRIBER_MAX)
      {
        return nullptr;
      }

      // Register Topic
      ret = this->registerTopic<MsgT>();

      if (ret == false)
      {
        return nullptr;
      }

      auto p_sub = std::make_shared<ros2::Subscription<MsgT>>(&this->xrcedds_subscriber_, name, callback);

      if(p_sub->is_registered_ == false)
      {
        p_sub.reset();
        return nullptr;
      }

      for(uint8_t i = 0; i < ROS2_SUBSCRIBER_MAX; i++)
      {
        if(!sub_list_[i])
        {
          sub_list_[i] = p_sub;
          sub_cnt_++;
          p_sub->subscribe();
          break;
        }
      }

      return p_sub;
    }

  private:
    TimerBase::SharedPtr timer_list_[ROS2_TIMER_MAX];

    /*
    PublisherHandle*    pub_list_[ROS2_PUBLISHER_MAX];
    SubscriptionHandle* sub_list_[ROS2_SUBSCRIBER_MAX];
    */

    std::shared_ptr<void> pub_list_[ROS2_PUBLISHER_MAX];
    std::shared_ptr<void> sub_list_[ROS2_SUBSCRIBER_MAX];

    bool node_register_state_;
    xrcedds::Transport_t xrcedds_transport_;
    xrcedds::Participant_t xrcedds_participant_;
    xrcedds::Publisher_t xrcedds_publisher_;
    xrcedds::Subscriber_t xrcedds_subscriber_;
    uint8_t timer_cnt_;
    uint8_t pub_cnt_;
    uint8_t sub_cnt_;

    template <
      typename MsgT>
    bool registerTopic()
    {
      bool ret;
      MsgT topic;

      if(this->node_register_state_ == false)
      {
        return false;
      }

      ret = xrcedds::registerTopic(&this->xrcedds_participant_, topic.name_, topic.type_, topic.id_);

      return ret;
    }
};

} /* namespace ros2 */

#endif /* ROS2_H_ */
