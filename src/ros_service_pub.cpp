#include "../include/ros_service_pub.h"

ros_service_pub::ros_service_pub()
{
   service_server=nh.advertiseService("SerialNumber",&ros_service_pub::callService,this);
   sub_refer=nh.subscribe<std_msgs::String>("/Action_num",1000,&ros_service_pub::callback_refer,this);
}

bool ros_service_pub::callService(ros_qt_gui::service::Request& request, ros_qt_gui::service::Response& response)
{
  // response=std::string((const char *)this->serialNumber.toLocal8Bit());
     response.SerialNumber=this->serialNumber;
     return true;
}

void ros_service_pub::setSerialNumber(const std::string &str)
{
    serialNumber=str;
}

void ros_service_pub::callback_refer(const std_msgs::String::ConstPtr &refer_msg)
{

    refer_str=QString(QString::fromLocal8Bit((refer_msg->data).c_str()));


}

QString ros_service_pub::getRefer()
{
  return refer_str;
}
