
#include "ros/ros.h"
#include "std_msgs/Float32MultiArray.h"
int main(int argc, char **argv)
{
    ros::init(argc, argv, "Array_pub");
    ros::NodeHandle nh;
 
    ros::Publisher chatter_pub = nh.advertise<std_msgs::Float32MultiArray>("chatter", 1000);
 
    ros::Rate loop_rate(10);
    while (ros::ok())
    {
        std_msgs::Float32MultiArray msg;
        Msg.data.push_back(1.0);//Write it yourself, feasible
        msg.data.push_back(2.0);
        msg.data.push_back(3.0);
        msg.data.push_back(4.0);
 
        chatter_pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}
 //Subscribe
#include "ros/ros.h"
#include "std_msgs/Float32MultiArray.h"
 
void chatterCallback(const std_msgs::Float32MultiArray::ConstPtr& msg)
{
    ROS_INFO("I heard: [%f],[%f],[%f],[%f]", msg->data.at(0),msg->data.at(1),msg->data.at(2),msg->data.at(3));
}
 
int main(int argc, char **argv)
{
    ros::init(argc, argv, "Array_sub");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("chatter", 1000, chatterCallback);
    ros::spin();
    return 0;
