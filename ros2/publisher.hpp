/*
 * publisher.hpp
 *
 *  Created on: May 16, 2018
 *      Author: Kei
 */

#ifndef ROS2_PUBLISHER_HPP_
#define ROS2_PUBLISHER_HPP_

#include <stdio.h>
#include <memory>
#include "xrcedds/xrcedds.hpp"
#include "node_handle.hpp"

namespace ros2 {

template <typename MsgT>
class Publisher:public PublisherHandle
{
public:
  using SharedPtr = std::shared_ptr<Publisher<MsgT>>;

  Publisher(xrcedds::Publisher_t* publisher, const char* name)
    : PublisherHandle()
  {
    name_ = name;
    publisher_ = publisher;
    this->recreate();
  }

  void publish(std::shared_ptr<MsgT> &msg)
  {
    if(is_registered_ ==  false)
    {
      return;
    }

    ucdrBuffer mb;
    xrcedds::writeData(&data_writer_, (void*)&mb, msg->size_of_topic(msg.get(), 0));
    msg->serialize(&mb, msg.get());
  }

  void recreate()
  {
#if (UXR_CREATE_ENTITIES_USING_REF)
    is_registered_ = xrcedds::createDataWriter(publisher_, &data_writer_, (char*)name_, topic_.type_);
#else
    char writer_name[64];
    sprintf(writer_name, "%s/%s", getPrefixString(TOPICS_PUBLISH), name_);    
    is_registered_ = xrcedds::createDataWriter(publisher_, &data_writer_, writer_name, topic_.type_);    
#endif
  }

  void destroy(void)
  {
    xrcedds::deleteEntity(&data_writer_);
  }
  
private:
  MsgT topic_;
  xrcedds::Publisher_t* publisher_;
  xrcedds::DataWriter_t data_writer_;
};

} // namespace ros2

#endif /* ROS2_PUBLISHER_HPP_ */
