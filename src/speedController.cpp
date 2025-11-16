#include "../include/speedController.hpp"

smb_data smbdata;

speedController::~speedController(){};

speedController::speedController(ros::NodeHandle &nh){
    //初始化发布者
    vel_ctrler = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
    //初始化订阅者
    dis = nh.subscribe<std_msgs::Float64>("/scan_ret_dis", 10, &speedController::dis_callback, this);
    ang = nh.subscribe<std_msgs::Float64>("/scan_ret_ang", 10, &speedController::ang_callback, this);
    lca = nh.subscribe<geometry_msgs::PointStamped>("/scan_ret_loca", 10, &speedController::lca_callback, this);
}

void speedController::high_speed(ros::Publisher &cmd_vel_pub, int Mode){
    geometry_msgs::Twist move_cmd;
    move_cmd.linear.x = 0.0;
    move_cmd.linear.y = 0.0;
    move_cmd.linear.z = 0.0;
    move_cmd.angular.x = 0.0;
    move_cmd.angular.y = 0.0;
    move_cmd.angular.z = 0.0;
    switch (Mode)
    {
        case LEFT:
            move_cmd.angular.z = 0.7;
            break;
        case RIGHT:
            move_cmd.angular.z = -0.7;
            break;
        case FRONT:
            move_cmd.linear.x = 15.0;
            break;
        case BACK:
            move_cmd.linear.x = -3.0;
            break;
        case STOP:
            cmd_vel_pub.publish(move_cmd);
            return;
        default:
            break;
    }
    cmd_vel_pub.publish(move_cmd);
}

void speedController::low_speed(ros::Publisher &cmd_vel_pub, int Mode){
    geometry_msgs::Twist move_cmd;
    move_cmd.linear.x = 0.0;
    move_cmd.linear.y = 0.0;
    move_cmd.linear.z = 0.0;
    move_cmd.angular.x = 0.0;
    move_cmd.angular.y = 0.0;
    move_cmd.angular.z = 0.0;
    switch (Mode)
    {
        case LEFT:
            move_cmd.angular.z = 0.01;
            break;
        case RIGHT:
            move_cmd.angular.z = -0.01;
            break;
        case FRONT:
            move_cmd.linear.x = 0.5;
            break;
        case BACK:
            move_cmd.linear.x = -0.5;
            break;
        case STOP:
            cmd_vel_pub.publish(move_cmd);
            return;
        default:
            break;
    }
    cmd_vel_pub.publish(move_cmd);
}


void speedController::ang_callback(const std_msgs::Float64::ConstPtr &ang_msg){
    smbdata.angle = ang_msg->data;

}
void speedController::dis_callback(const std_msgs::Float64::ConstPtr &dis_msg){
    smbdata.distance = dis_msg->data;
};
void speedController::lca_callback(const geometry_msgs::PointStamped::ConstPtr &loca_msg){
    std::cout<<smbdata.Allow_Collision<<std::endl;
    std::cout<<smbdata.distance<<std::endl;
    std::cout<<smbdata.angle<<std::endl;
    if (loca_msg->point.x == -100 && loca_msg->point.y == 0 && smbdata.distance == -100)
    {
        smbdata.Allow_Collision = false;
        high_speed(vel_ctrler, BACK);
        return;
    }
    if (smbdata.distance < 2 && !smbdata.Allow_Collision)
    {
        high_speed(vel_ctrler, BACK);
    }
    
    if (abs(smbdata.angle) > 0.02)
    {
        if (smbdata.Allow_Collision)
        {
            std::cout<<"前进中，不调整角度"<<std::endl;
            if (abs(smbdata.angle) < 0.2) return;
        }
        else
        {
            std::cout<<"调整角度中"<<std::endl;
            if (smbdata.angle > 0.1)
            {
                high_speed(vel_ctrler, LEFT);
            }
            else if (smbdata.angle < -0.1)
            {
                high_speed(vel_ctrler, RIGHT);
            }
            else if (smbdata.angle < 0.1)
            {
                low_speed(vel_ctrler, LEFT);
            }
            else if (smbdata.angle > -0.1)
            {
                low_speed(vel_ctrler, RIGHT);
            }
            else
            {
                smbdata.Allow_Collision = false;
                return;
            }  
        }    
    }
    if (abs(smbdata.angle) < 0.02)
    {
        std::cout<<"前进中"<<std::endl;
        smbdata.Allow_Collision = true;
        high_speed(vel_ctrler, FRONT);        
    }
    
};