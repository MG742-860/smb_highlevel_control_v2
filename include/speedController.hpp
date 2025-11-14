#pragma once
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <sensor_msgs/PointCloud2.h>
#include <std_msgs/Float64.h>
#include <geometry_msgs/PointStamped.h>
#include <geometry_msgs/Twist.h>

#define LEFT 1
#define RIGHT 2
#define FRONT 3
#define BACK 4
#define STOP 5
#define CHECK RIGHT

class smb_data{
public:
    double angle;
    double distance;
    bool Allow_Collision;
    bool is_Attached;
};

class speedController
{
private:



    //创建订阅者
    ros::Subscriber ang;
    ros::Subscriber dis;
    ros::Subscriber lca;

    //创建回调函数
    void ang_callback(const std_msgs::Float64::ConstPtr &ang_msg);
    void dis_callback(const std_msgs::Float64::ConstPtr &dis_msg);
    void lca_callback(const geometry_msgs::PointStamped::ConstPtr &loca_msg);



public:
    speedController(ros::NodeHandle &nh);
    ~speedController();
    //创建发布者
    ros::Publisher vel_ctrler;

    ros::Publisher *get_pub(){
        return &vel_ctrler;
    }

    //创建控制函数
    void stop(ros::Publisher &cmd_vel_pub);
    void high_speed(ros::Publisher &cmd_vel_pub, int Mode);
    void low_speed(ros::Publisher &cmd_vel_pub, int Mode);
};
