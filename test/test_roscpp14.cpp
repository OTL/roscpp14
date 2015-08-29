// Copyright [2015] Takashi Ogura <t.ogura@gmail.com>

#include <roscpp14/ros.h>
#include <std_msgs/String.h>
#include <std_srvs/Empty.h>
#include <gtest/gtest.h>
#include <future>

using roscpp14::operator"" _Hz;
using roscpp14::operator"" _s;

TEST(Roscpp14PubSub, pubSub)
{
  static const char *const TEST_TOPIC_NAME = "test_pub_sub";

  roscpp14::NodeHandle node;
  std_msgs::String received_msg;
  auto sub = node.subscribe<std_msgs::String>(TEST_TOPIC_NAME, 1,
                                              [&received_msg] (const auto &msg) {
                                                received_msg = msg;
                                              });
  auto pub = node.advertise<std_msgs::String>(TEST_TOPIC_NAME, 1);
  auto r = 10.0_Hz;
  while (sub.getNumPublishers() == 0) {
    r.sleep();
  }
  std_msgs::String sending_msg;
  sending_msg.data = "send";
  pub.publish(sending_msg);
  while (received_msg.data == "") {
    ros::spinOnce();
    r.sleep();
  }
  EXPECT_EQ(received_msg.data, sending_msg.data);
}

TEST(Roscpp14Service, service)
{
  static const char *const TEST_SERVICE_NAME = "test_service";
  roscpp14::NodeHandle node;
  bool is_called = false;
  auto server = node.advertiseService<std_srvs::Empty>(TEST_SERVICE_NAME,
                                                       [&is_called] (auto &req, auto &res) {
                                                         is_called = true;
                                                         return true;
                                                       });
  ros::AsyncSpinner spinner(1);
  spinner.start();

  auto client = node.serviceClient<std_srvs::Empty>(TEST_SERVICE_NAME);
  ASSERT_TRUE(client.waitForExistence(2.0_s));
  std_srvs::Empty empty;
  ASSERT_TRUE(client.call(empty));
  EXPECT_TRUE(is_called);
}

int main(int argc, char **argv){
  ros::init(argc, argv, "test_roscpp14");
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
