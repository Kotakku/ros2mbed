// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef _STD_MSGS_INT32_HPP_
#define _STD_MSGS_INT32_HPP_

#include "../topic.hpp"


namespace std_msgs {


class Int32 : public ros2::Topic<Int32>
{
public:
    using SharedPtr = std::shared_ptr<Int32>;
    
  int32_t data;

  Int32():
    Topic("std_msgs::msg::dds_::Int32_", "Int32", STD_MSGS_INT32_ID),
    data(0)
  { 
  }

  bool serialize(void* msg_buf, Int32* topic)
  {
    ucdrBuffer* writer = (ucdrBuffer*)msg_buf;
    (void) ucdr_serialize_int32_t(writer, topic->data);

    return !writer->error;
  }

  bool deserialize(void* msg_buf, Int32* topic)
  {
    ucdrBuffer* reader = (ucdrBuffer*)msg_buf;
    (void) ucdr_deserialize_int32_t(reader, &topic->data);

    return !reader->error;
  }

  uint32_t size_of_topic(const Int32* topic, uint32_t size)
  {
    (void)(topic);

    uint32_t previousSize = size;
    size += ucdr_alignment(size, 4) + 4;

    return size - previousSize;
  }

};

} // namespace std_msgs


#endif // _STD_MSGS_INT32_HPP_
