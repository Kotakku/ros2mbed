/*
 * subscriber.hpp
 *
 *  Created on: May 16, 2018
 *      Author: Kei
 */

#ifndef ROS2_SUBSCRIBER_HPP_
#define ROS2_SUBSCRIBER_HPP_

#include <stdio.h>
#include <memory>
#include "xrcedds/xrcedds.hpp"
#include "node_handle.hpp"
#include "topic.hpp"

namespace ros2
{

class Node;

template <typename MsgT>
class Subscription:public SubscriptionHandle
{
public:
    using SharedPtr = std::shared_ptr<Subscription>;

    std::function<void(std::shared_ptr<MsgT>)> callback;
    
    template<typename CallbackT>
    Subscription(xrcedds::Subscriber_t* subscriber, const char* name, CallbackT callback)
      : SubscriptionHandle()
    {
      name_ = name;
      topic_ = std::make_shared<MsgT>();
      subscriber_ = subscriber;
      this->callback = callback;
      this->recreate();
    }

    void subscribe(void)
    {
      if(is_registered_ ==  false)
      {
        return;
      }

      xrcedds::readData(&data_reader_);
      request_id_ = data_reader_.request_id;
    }

    void runCallback(void* serialized_msg)
    {
      if(this->callback != nullptr)
      {
        topic_->deserialize((ucdrBuffer*)serialized_msg, topic_.get());

        this->callback(topic_);
      }
    }

    void recreate()
    {
#if (UXR_CREATE_ENTITIES_USING_REF)
      is_registered_ = xrcedds::createDataReader(subscriber_, &data_reader_, (char*)name_, topic_->type_);
#else
      char reader_name[64];
      sprintf(reader_name, "%s/%s", getPrefixString(TOPICS_SUBSCRIBE), name_);
      is_registered_ = xrcedds::createDataReader(subscriber_, &data_reader_, reader_name, topic_->type_);      
#endif      
      this->reader_id_ = data_reader_.id;
    };  

    void destroy(void)
    {
      xrcedds::deleteEntity(&data_reader_);
    }

  private:
    std::shared_ptr<MsgT> topic_;
    xrcedds::Subscriber_t* subscriber_;
    xrcedds::DataReader_t data_reader_;
};

} // namespace ros2

#endif /* ROS2_SUBSCRIBER_HPP_ */
