#include "../include/distance.hpp"

distance::distance(ros::NodeHandle &nh){
    //定义订阅者
    scan_sub = nh.subscribe<sensor_msgs::LaserScan>("/scan", 10, &distance::scan_distance, this);
    //定义发布者
    dis_pub = nh.advertise<std_msgs::Float64>("scan_ret_dis",10);//distance
    ang_pub = nh.advertise<std_msgs::Float64>("scan_ret_ang",10);//angle
    loca_pub = nh.advertise<geometry_msgs::PointStamped>("scan_ret_loca",10);//location
}

distance::~distance(){};

void distance::scan_distance(const sensor_msgs::LaserScan::ConstPtr &msg){
    //首先找出最小距离，并获取此时的角度，通过cos和sin获取相对坐标

    //找最小距离
    double min_dist = std::numeric_limits<double>::max();
    double min_angle = 0.0;
    bool found = false;
    // 遍历所有激光点
    for (size_t i = 0; i < msg->ranges.size(); ++i) 
    {
        float range = msg->ranges[i];     
        // 跳过无效数据
        if (!std::isnan(range) && !std::isinf(range) && range >= 0 && range <= msg->range_max) 
        {           
            if (range < min_dist) 
            {
                min_dist = range;
                min_angle = msg->angle_min + i * msg->angle_increment;
                found = true;
            }
        }
    }
    if (found) 
    {
    // 计算相对于激光雷达的坐标
    double x = min_dist * cos(min_angle);
    double y = min_dist * sin(min_angle);
        
        ROS_INFO("=== 激光扫描结果 ===");
        ROS_INFO("最小距离: %.3f 米", min_dist);
        ROS_INFO("对应角度: %.3f 弧度 (%.1f 度)", min_angle, min_angle * 180.0/M_PI);
        ROS_INFO("激光坐标系坐标: (%.3f, %.3f) 米", x, y);
        ROS_INFO("====================");

        //发布结果
        geometry_msgs::PointStamped point_msg;
        point_msg.point.x = x;
        point_msg.point.y = y;
        loca_pub.publish(point_msg);

        std_msgs::Float64 dis_min;
        dis_min.data = min_dist;
        dis_pub.publish(dis_min);
        

        std_msgs::Float64 ang_min;
        ang_min.data = min_angle;
        ang_pub.publish(ang_min);
    }
    else
    {
        std_msgs::Float64 dis_min;
        dis_min.data = -100;
        dis_pub.publish(dis_min);
        

        // std_msgs::Float64 ang_min;
        // ang_min.data = 180;
        // ang_pub.publish(ang_min);
        
        geometry_msgs::PointStamped point_msg;
        point_msg.point.x = -100;
        point_msg.point.y = 0;
        loca_pub.publish(point_msg);        
    }

}