# roscpp14: ROS meets C++14!!

You can use c++14 if you use roscpp14.

## Use lambda for callback function

### Topic Subscriber

```c++
#include <roscpp14/ros.h>
#include <std_msgs/String.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");
  roscpp14::NodeHandle node;
  auto sub = node.subscribe<std_msgs::String>("chatter", 10,
                                              [] (const auto &msg) {
                                                ROS_INFO("%s", msg.data.c_str()); });
  ros::spin();
  return 0;
}
```

### Service Server

```c++
#include <roscpp14/ros.h>
#include <std_srvs/Empty.h>

int main(int argc, char **argv) 
{
  ros::init(argc, argv, "service_server");
  roscpp14::NodeHandle node;
  auto ser = node.advertiseService<std_srvs::Empty>("call_me",
                                                    [&] (auto &req, auto &res) {
                                                      ROS_INFO("called!");
                                                      return true;
                                                    });
  ros::spin();
  return 0;
}
```

## Use user-defined literal for ros::Rate

When you create a timer for 10.0[Hz], you'll write as below in roscpp.

```c++
ros::Rate r(10.0);
r.sleep();
```

You can use 10.0_Hz like below with roscpp14 now!

```c++
using roscpp14::operator"" _Hz;

auto r = 10.0_Hz;
r.sleep();
```

## Install

### Supported Platforms

* ROS
  * Jade
* OS
  * OSX (10.10.x)
  * Ubuntu15.04
  * Ubuntu14.04 (with g++-4.9)

### How to install

```bash
cd ~/catkin_ws/src
git clone https://github.com/OTL/roscpp14.git
```

It's not possible to release officially because ROS Jade/Kinetic supports very old
distribution (Ubuntu14.04)

### Ubuntu14.04
roscpp14 uses c++14. This means it requires g++-4.9, which can not be installed by default.
Please install g++-4.9 like below.

```bash
sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt-get update
sudo apt-get install g++-4.9
```

## How to use

Just add roscpp14 as dependency.
