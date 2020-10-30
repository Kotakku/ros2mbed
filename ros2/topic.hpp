/*
 * topic.hpp
 *
 *  Created on: May 16, 2018
 *      Author: Kei
 */

#ifndef ROS2_TOPIC_HPP_
#define ROS2_TOPIC_HPP_

#include <stdlib.h>
#include <memory>
#include <string>
#include <vector>
#include "xrcedds/xrcedds.hpp"
#include "topic_id_number.h"

namespace ros2 {

/* Base Message Type */
template <typename MsgT>
class Topic
{

public:
  //using SharedPtr = std::shared_ptr<Topic<MsgT>>;

  Topic(const char* type, const char* name, uint8_t id):
    type_(type),
    name_(name),
    id_(id)
  {
  }

  virtual ~Topic()
  {
  }

  virtual bool serialize(void* msg_buf, const MsgT* topic) = 0;
  virtual bool deserialize(void* msg_buf, MsgT* topic) = 0;
  virtual uint32_t size_of_topic(const MsgT* topic, uint32_t size)
  {
    (void)(topic); (void)(size);

    return 0;
  }

  const char* type_;
  const char* name_;
  uint8_t id_;
};

} // namespace ros2

#endif /* ROS2_TOPIC_HPP_ */
