// Copyright [2015] Takashi Ogura <t.ogura@gmail.com>

#ifndef ROSCPP14_ROS_H
#define ROSCPP14_ROS_H

#include "ros/ros.h"

/**
   ros::init(argc, argv, "listener");
   ros11::NodeHandle node;
   auto sub = node.subscribe("/hoge", 100, [&] (const std::shared_ptr<std_msgs::String> &msg){
   ROS_INFO("msg = %s", msg->data.c_str());
   });

   auto sub2 = node.subscribe("/hoge", 100, [&] (const std_msgs::String &msg){
   ROS_INFO("msg = %s", msg->data.c_str());
   });
*/
namespace roscpp14
{
  class NodeHandle : public ::ros::NodeHandle {
  public:
    using RosNodeHandle = ::ros::NodeHandle::NodeHandle;
    using VoidConstPtr = ::ros::VoidConstPtr;
    using TransportHints = ::ros::TransportHints;
    using Subscriber = ::ros::Subscriber;
    using ServiceServer = ::ros::ServiceServer;
    template<class M>
    Subscriber subscribe(const std::string& topic, uint32_t queue_size, 
			 const std::function<void(const M&)>& callback,
			 const VoidConstPtr& tracked_object = VoidConstPtr(),
			 const TransportHints& transport_hints = TransportHints()) {
      return RosNodeHandle::subscribe<M>(topic, queue_size, static_cast<boost::function<void(const M&)>>(callback), tracked_object, transport_hints);
    }
    template<class S>
      ServiceServer advertiseService(const std::string& service, 
				   const std::function<bool(typename S::Request&, typename S::Response&)> callback,
				   const VoidConstPtr& tracked_object = VoidConstPtr()) {
      return RosNodeHandle::advertiseService<typename S::Request, typename S::Response>(service, static_cast<boost::function<bool(typename S::Request&, typename S::Response&)>>(callback), tracked_object);
    }
  };
}  // namespace ros

#endif // ROSCPP14_ROS_H
