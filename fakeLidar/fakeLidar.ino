#include "math.h"
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

// ROS includes
#include <ros.h>
#include <ros/time.h>
#include <sensor_msgs/LaserScan.h>
#include <tf/transform_broadcaster.h>
 
sensor_msgs::LaserScan CDLaser_msg;

//
float f_angle_min;
float f_angle_max;
float f_angle_increment;
float f_time_increment;
float f_scan_time;
float f_range_min;
float f_range_max;
float f_ranges[5]; // max of 30 measurements
float f_intensities[5];

int publisher_timer;

geometry_msgs::TransformStamped t;
tf::TransformBroadcaster broadcaster;
ros:: Publisher pub_Laser("LaserData", &CDLaser_msg);  
char base_link[] = "/base_link";
char odom[] = "/odom";
ros::NodeHandle nh;

void setup() 
{
  nh.initNode();
  nh.advertise(pub_Laser);
   broadcaster.init(nh);
  f_angle_min = -1.57;
  f_angle_max = 1.57;
  f_angle_increment = 0.785;  // 3.14/4   - 5 measurement points
  f_time_increment = 10;
  f_scan_time = 4;
  f_range_min = 0.1;
  f_range_max = 30;

  CDLaser_msg.ranges_length = 5;
  CDLaser_msg.intensities_length = 5;

  // create the test data
  for (int z = 0 ; z<5; z++)
  {
    f_ranges[z] = z;
    f_intensities[z] = z*z;
  }
}

void loop() 
{
  if (millis() > publisher_timer)
  {
    CDLaser_msg.header.stamp = nh.now();
    CDLaser_msg.header.frame_id = "/lidar_frame";
    CDLaser_msg.angle_min = f_angle_min;
    CDLaser_msg.angle_max = f_angle_max;
    CDLaser_msg.angle_increment = f_angle_increment;
    CDLaser_msg.time_increment = f_time_increment;
    CDLaser_msg.scan_time = f_scan_time;
    CDLaser_msg.range_min = f_range_min;
    CDLaser_msg.range_max = f_range_max;

    for (int z = 0 ; z<5; z++)
    {
      CDLaser_msg.ranges[z] = f_ranges[z];
    }

    for (int z = 0 ; z<5; z++)
    {
      CDLaser_msg.intensities[z] = f_intensities[z];
    }

    publisher_timer = millis() + 1000;
    pub_Laser.publish(&CDLaser_msg);
    t.header.frame_id = odom;
     t.child_frame_id = base_link;
    t.transform.translation.x = 1.0; 
     t.transform.rotation.x = 0.0;
    t.transform.rotation.y = 0.0; 
     t.transform.rotation.z = 0.0; 
     t.transform.rotation.w = 1.0;  
    t.header.stamp = nh.now();
     broadcaster.sendTransform(t);
  }
  nh.spinOnce();
  delay(50);
}
