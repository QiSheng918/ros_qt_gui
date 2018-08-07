#include "sub_node.h"
#include <QDebug>

sub_node::sub_node()
{
    qDebug()<<"started";
    sub=nh.subscribe<turtlesim::Pose>("/turtle1/pose",1000,&sub_node::callback,this);
    init_time=ros::Time::now();
}

void sub_node::callback(const turtlesim::Pose::ConstPtr& msg)
{
  linear=msg->x;
  time=ros::Time::now();
  t=time.toSec()-init_time.toSec();
//  qDebug()<<t;
//  qDebug()<<linear;
}


