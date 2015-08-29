// Copyright [2015] Takashi Ogura <t.ogura@gmail.com>

#include <roscpp14/ros.h>
#include <std_msgs/String.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");
  roscpp14::NodeHandle node;
  auto sub = node.subscribe<std_msgs::String>("chatter", 10,
                                              [] (const std_msgs::String &msg) {
                                                ROS_INFO("%s", msg.data.c_str()); });
  ros::spin();
  return 0;
}
