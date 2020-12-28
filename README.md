# ros2mbed
mbed library for communicating with ROS2

## ROS2 Version
ROS 2 Dashing Diademata

## Micro-XRCE-DDS-Agent Version
v1.3.0

## Network setting(for Ubuntu)
IPv4  
method: Manual  
Address: 任意のAddress, Netmask, Gateway

IPv6
method: Link-Local Only

## How to use
### UDP

ros2mbed内のuser_config.hの```USER_TRANSPORT_TYPE```は0にしておく
```
#define USER_TRANSPORT_TYPE 0
```
コンパイルしてmbedに書き込む

ターミナルで以下を実行
```
~/Micro-XRCE-DDS-Agent/build$ ./MicroXRCEAgent udp4 -p 2018
```

### Serial
ros2mbed内のuser_config.hの```USER_TRANSPORT_TYPE```は2にしておく
```
#define USER_TRANSPORT_TYPE 2
```
コンパイルしてmbedに書き込む

ターミナルで以下を実行
```
~/Micro-XRCE-DDS-Agent/build$ ./MicroXRCEAgent serial --dev /dev/ttyACM0 -b 115200
```

## Example
mbedに以下を書き込んでおく
```cpp
/*
for UDP config
mbed_app.json

{
    "target_overrides": {
        "*": {
            "platform.stdio-convert-newlines": true,
            "target.network-default-interface-type": "ETHERNET"
        }
    }
}
*/

#include "mbed.h"
#include "ros2mbed.h"
#include "subscription.hpp"
#if USER_TRANSPORT_TYPE == 0 || USER_TRANSPORT_TYPE == 1
#include "EthernetInterface.h"
#endif 

#include <string>

DigitalOut led(LED1);

class SamplePub : public ros2::Node
{
public:
    SamplePub()
    : Node("sample_node"), count_(0)
    {
        pub_ = this->create_publisher<std_msgs::String>("string_pub");

        sub_ = this->create_subscription<std_msgs::Bool>(
            "led_sub",
            [&](std::shared_ptr<std_msgs::Bool> msg)
            {
                led = msg->data;
            });

        timer_ = this->create_wall_timer(
            500ms,
            [&](){
                auto msg = std::make_shared<std_msgs::String>();
                msg->data = "Hello ros2mbed! " + std::to_string(count_++);
                pub_->publish(msg);
            });
    }

private:
    int count_;
    ros2::Publisher<std_msgs::String>::SharedPtr pub_;
    ros2::Subscription<std_msgs::Bool>::SharedPtr sub_;
    
    ros2::TimerBase::SharedPtr timer_;
};


int main()
{
    led = 1;
#if USER_TRANSPORT_TYPE == 0 || USER_TRANSPORT_TYPE == 1
    EthernetInterface net;
    ros2::init(&net, "192.168.2.101", 2018);
#endif 

#if USER_TRANSPORT_TYPE == 2
    BufferedSerial pc(USBTX, USBRX, 115200);
    ros2::init(&pc);
#endif

    SamplePub sample_node;
    ros2::spin(&sample_node);
}
```

MicroXRCEAgentを起動させて接続する  
接続されると以下のように表示される
```
$ ~/Micro-XRCE-DDS-Agent/build$ ./MicroXRCEAgent serial --dev /dev/ttyACM0 -b 115200
Press CTRL+C to exit
[1609143777.121211] info     | TermiosAgentLinux.cpp | init                     | running...             | fd: 3
[1609143822.997434] info     | Root.cpp           | create_client            | create                 | client_key: 0xAABBCCDD, session_id: 0x81
[1609143822.997504] info     | SessionManager.hpp | establish_session        | session established    | client_key: 0x2864434397, address: 0

```

### mbed->ros
MicroXRCEAgentを接続したターミナルとは別のターミナルを起動させ、以下を実行
```
$ ros2 topic echo string_pub
```

mbedから文字列が送られてくる
```
data: Hello ros2mbed! 10
---
data: Hello ros2mbed! 11
---
data: Hello ros2mbed! 12
---
data: Hello ros2mbed! 13
---
data: Hello ros2mbed! 14
---
data: Hello ros2mbed! 15
---
data: Hello ros2mbed! 16
---
data: Hello ros2mbed! 17
---
data: Hello ros2mbed! 18
```


### ros->mbed
MicroXRCEAgentを接続したターミナルとは別のターミナルを起動させ、以下を実行
mbedのledをONにする
```
$ ros2 topic pub --once /led_sub std_msgs/Bool '{data: True}'
```

mbedのledをOFFにする
```
$ ros2 topic pub --once /led_sub std_msgs/Bool '{data: False}'
```