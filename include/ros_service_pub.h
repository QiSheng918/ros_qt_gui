#ifndef ROS_SERVICE_PUB_H
#define ROS_SERVICE_PUB_H

#include <ros/ros.h>
#include <ros_qt_gui/service.h>
#include <QString>
#include <std_msgs/String.h>
#include <QObject>

class ros_service_pub:QObject
{
    Q_OBJECT
public:
    ros_service_pub();
    void setSerialNumber(const std::string &str);
    QString getRefer();
//signals:
//   void get_refer(int b);

private:

    ros::NodeHandle nh;
    ros::ServiceServer service_server;
    ros::Subscriber sub_refer;
    std::string serialNumber;

    QString refer_str;

    bool callService(ros_qt_gui::service::Request& request, ros_qt_gui::service::Response& response);
    void callback_refer(const std_msgs::String::ConstPtr& refer_msg);
};

#endif // ROS_SERVICE_PUB_H
