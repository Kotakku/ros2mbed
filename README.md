# ros2mbed

## Micro-XRCE-DDS-Agent
v1.3.0

## Network setting(for Ubuntu)
IPv4
method: Manual
Address: ユーザーが決めたAddress, Netmask, Gateway

IPv6
method: Link-Local Only

## UDP
```
~/Micro-XRCE-DDS-Agent/build$ ./MicroXRCEAgent udp4 -p 2018
```

## Serial
```
~/Micro-XRCE-DDS-Agent/build$ ./MicroXRCEAgent serial --dev /dev/ttyACM0 -b 115200
```