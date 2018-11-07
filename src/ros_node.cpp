#include "../include/ros_node.h"
#include <QDebug>

ros_node::ros_node()
{
    qDebug()<<"started";
    sub_IMU_data=nh.subscribe<ros_qt_gui::IMU>("/IMU_data",1000,&ros_node::callback_IMU,this);
    sub_sEMG_data=nh.subscribe<ros_qt_gui::EMG>("/sEMG_data",1000,&ros_node::callback_sEMG,this);
    sub_test=nh.subscribe<turtlesim::Pose>("/turtle1/pose",1000,&ros_node::calltest,this);
    time_reset[0]=false;
    time_reset[1]=false;
}

void ros_node::callback_IMU(const ros_qt_gui::IMU::ConstPtr& IMU_msg)
{
  if(!time_reset[0]){
    IMU_t=0;
    init_time[0]=ros::Time::now();
  }
  else{
    IMU_t=ros::Time::now().toSec()-init_time[0].toSec();
    for(int i=0;i<3;i++)  IMU_data[i]=IMU_msg->data[i];
  }
}

void ros_node::callback_sEMG(const ros_qt_gui::EMG::ConstPtr& sEMG_msg)
{
  if(!time_reset[1])  {
    sEMG_t=0;
    init_time[1]=ros::Time::now();
  }
  else{
    sEMG_t=ros::Time::now().toSec()-init_time[1].toSec();
    sEMG_data=sEMG_msg->data;
  }
}

void ros_node::calltest(const turtlesim::Pose::ConstPtr &msg)
{
  time=ros::Time::now();
  t=time.toSec()-init_time[1].toSec();
   temp=msg->x;
}


