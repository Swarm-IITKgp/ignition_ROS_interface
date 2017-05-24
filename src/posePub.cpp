#include <iostream>
#include <string>
#include <ignition/msgs.hh>
#include <ignition/transport.hh>
#include <ros/ros.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Quaternion.h>

geometry_msgs::Pose msg1;
geometry_msgs::Pose msg2;
geometry_msgs::Pose msg3;

void cb1(const ignition::msgs::Pose &_msg)
{
  msg1.position.x = _msg.position().x();
  msg1.position.y = _msg.position().y();
  msg1.orientation.z = _msg.orientation().z();
}

void cb2(const ignition::msgs::Pose &_msg)
{
  msg2.position.x = _msg.position().x();
  msg2.position.y = _msg.position().y();
  msg2.orientation.z = _msg.orientation().z();
}

void cb3(const ignition::msgs::Pose &_msg)
{
  msg3.position.x = _msg.position().x();
  msg3.position.y = _msg.position().y();
  msg3.orientation.z = _msg.orientation().z();
}


//////////////////////////////////////////////////
int main(int argc, char **argv)
{
  ros::init(argc, argv, "posePublisher");
  ros::NodeHandle n;
  ignition::transport::Node node;
  //std::string botid = getenv("BOT_ID");
  std::string bot1 = "/bot1/pose";
  std::string bot2 = "/bot2/pose";
  std::string bot3 = "/bot3/pose";
  ros::Publisher pose_bot1 = n.advertise<geometry_msgs::Pose>(bot1, 1000); 
  ros::Publisher pose_bot2 = n.advertise<geometry_msgs::Pose>(bot2, 1000);
  ros::Publisher pose_bot3 = n.advertise<geometry_msgs::Pose>(bot3, 1000);
  ros::Rate loop_rate(10);

  // Subscribe to a topic by registering a callback.
  if (!node.Subscribe(bot1, cb)){
    std::cerr << "Error subscribing to topic [" << subTopic << "]" << std::endl;
    return -1;
  }
  if (!node.Subscribe(bot2, cb)){
    std::cerr << "Error subscribing to topic [" << subTopic << "]" << std::endl;
    return -1;
  }
  if (!node.Subscribe(bot3, cb)){
    std::cerr << "Error subscribing to topic [" << subTopic << "]" << std::endl;
    return -1;
  }
  while (ros::ok())
  {
    pose_bot1.publish(msg1);
    pose_bot2.publish(msg2);
    pose_bot3.publish(msg3);
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
