// Copyright [2015] Takashi Ogura <t.ogura@gmail.com>

#ifndef ROSCPP14_ROS_H
#define ROSCPP14_ROS_H

#include <string>

#include <ros/ros.h>

/**
   ros::init(argc, argv, "listener");
   roscpp14::NodeHandle node;
   auto sub = node.subscribe<std_msgs::String>("/hoge", 100,
       [&] (const auto &msg){
       ROS_INFO("msg = %s", msg.data.c_str());
   });
*/

namespace roscpp14
{
::ros::Rate operator"" _Hz(long double hz) {
  return ::ros::Rate(hz);
}
::ros::Duration operator"" _s(long double sec) {
  return ::ros::Duration(sec);
}

class NodeHandle : public ::ros::NodeHandle
{
public:
  using RosNodeHandle = ::ros::NodeHandle;
  using VoidConstPtr = ::ros::VoidConstPtr;
  using TransportHints = ::ros::TransportHints;
  using Subscriber = ::ros::Subscriber;
  using ServiceServer = ::ros::ServiceServer;

  template<class M>
  Subscriber subscribe(const std::string& topic, uint32_t queue_size,
                       const std::function<void(const M&)>& callback,
                       const VoidConstPtr& tracked_object = VoidConstPtr(),
                       const TransportHints& transport_hints = TransportHints())
  {
    return RosNodeHandle::subscribe<M>(topic, queue_size,
                                       static_cast<boost::function<void(const M&)>>(callback),
                                       tracked_object, transport_hints);
  }

  template<class S>
  ServiceServer advertiseService(const std::string& service,
                                 const std::function<bool(typename S::Request&, typename S::Response&)> callback,
                                 const VoidConstPtr& tracked_object = VoidConstPtr())
  {
    return RosNodeHandle::advertiseService<typename S::Request, typename S::Response>(
        service,
        static_cast<boost::function<bool(typename S::Request&, typename S::Response&)>>(callback),
        tracked_object);
  }
};

}  // namespace roscpp14

#endif  // ROSCPP14_ROS_H
