#pragma once
#include <iostream>
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <sensor_msgs/PointCloud2.h>
#include <std_msgs/Float64.h>
#include <geometry_msgs/PointStamped.h>
#include <geometry_msgs/Twist.h>
#include "speedController.hpp"


class distance
{
private:
    //订阅者
    ros::Subscriber scan_sub;

    //发布者
    ros::Publisher dis_pub;
    ros::Publisher ang_pub;
    ros::Publisher loca_pub;
    //回调函数
    void scan_distance(const sensor_msgs::LaserScan::ConstPtr &msg);
public:
    distance(ros::NodeHandle &nh);
    ~distance();
};
