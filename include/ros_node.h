#ifndef SUB_NODE_H
#define SUB_NODE_H
#include <ros/ros.h>
#include <QDebug>
#include <QString>
#include <geometry_msgs/Twist.h>
#include <std_msgs/String.h>
#include <turtlesim/Pose.h>
#include "ros_qt_gui/service.h"
#include "ros_qt_gui//IMU.h"
#include "ros_qt_gui/EMG.h"


class ros_node
{
public:
  ros_node();

   ros::Time time;
   float IMU_data[3];
   int sEMG_data;

   float IMU_t;
   float sEMG_t;
   float t;
   float temp;
   bool time_reset[2];



private:

  ros::NodeHandle nh;
  ros::Subscriber sub_IMU_data;
  ros::Subscriber sub_sEMG_data;
  ros::Subscriber sub_test;



  ros::Time init_time[2];





  void callback_IMU(const ros_qt_gui::IMU::ConstPtr& IMU_msg);
  void callback_sEMG(const ros_qt_gui::EMG::ConstPtr& sEMG_msg);
  void calltest(const turtlesim::Pose::ConstPtr& msg);
};

#endif // SUB_NODE_H
