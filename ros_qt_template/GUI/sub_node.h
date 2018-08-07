#ifndef SUB_NODE_H
#define SUB_NODE_H
#include <ros/ros.h>
#include <QDebug>
#include <geometry_msgs/Twist.h>
#include <turtlesim/Pose.h>

class sub_node
{
public:
  sub_node();
   ros::Time time;
   float linear;
   float t;
private:

  ros::NodeHandle nh;
  ros::Subscriber sub;
  void callback(const turtlesim::Pose::ConstPtr& msg);
  ros::Time init_time;
  ros::Time temp_time;


};

#endif // SUB_NODE_H
