#include <iostream>
#include <string>
#include <ignition/msgs.hh>
#include <ignition/transport.hh>
#include <ros/ros.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Quaternion.h>

geometry_msgs::Pose msg;

void cb(const ignition::msgs::Pose &_msg)
{
  msg.position.x = _msg.position().x();
  msg.position.y = _msg.position().y();
  msg.orientation.z = _msg.orientation().z();
  std::cout << "X: " << _msg.position().x() << " Y: " << _msg.position().y() << " Yaw: " << _msg.orientation().z() << std::endl << std::endl;
}

//////////////////////////////////////////////////
int main(int argc, char **argv)
{
  ros::init(argc, argv, "posePublisher");
  ros::NodeHandle n;
  ignition::transport::Node node;
  std::string botid = getenv("BOT_ID");
  std::string subTopic = "/bot" + botid + "/pose";
  ros::Publisher pose_pub = n.advertise<geometry_msgs::Pose>("pose", 1000);
  ros::Rate loop_rate(10);

  // Subscribe to a topic by registering a callback.
  if (!node.Subscribe(subTopic, cb))
  {
    std::cerr << "Error subscribing to topic [" << subTopic << "]" << std::endl;
    return -1;
  }

  while (ros::ok())
  {
    pose_pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
