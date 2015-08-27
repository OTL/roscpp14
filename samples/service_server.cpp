// Copyright [2015] Takashi Ogura <t.ogura@gmail.com>

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
