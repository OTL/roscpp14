# roscpp14: ROS meets C++14!!

roscpp supports c++14 now!!

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

### ServiceServer

```c++
#include <roscpp14/ros.h>
#include <std_srvs/Empty.h>

int main(int argc, char **argv) 
{
  ros::init(argc, argv, "service_server");
  roscpp14::NodeHandle node;
  auto ser = node.advertiseService<std_srvs::Empty>("call_me",
                                                    [&] (auto &req, auto &res) -> bool {
                                                      ROS_INFO("called!");
                                                      return true;
                                                    });
  ros::spin();
  return 0;
}
```

## Install

```bash
cd ~/catkin_ws/src
git clone https://github.com/OTL/roscpp14.git
```

Its not possible because ROS Jade uses too old compiler!

### OSX
roscpp14 works with clang.
If you have already installed ROS on OSX, you have nothing to do.

### Ubuntu14.04
roscpp14 uses c++14. This means it requires g++-4.9, which is not installed by default.
Please install g++-4.9 like below.

```bash
sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt-get update
sudo apt-get install g++-4.9
```

## How to use

Just add roscpp14 as dependency.

