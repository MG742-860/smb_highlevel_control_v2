/*
void speedController::stop(ros::Publisher &cmd_vel_pub){
    geometry_msgs::Twist move_cmd;
    
    move_cmd.linear.x = 0.0;
    move_cmd.linear.y = 0.0;
    move_cmd.linear.z = 0.0;

    move_cmd.angular.x = 0.0;
    move_cmd.angular.y = 0.0;
    move_cmd.angular.z = 0.0;

    cmd_vel_pub.publish(move_cmd);
}


void speedController::high_speed_forward(ros::Publisher &cmd_vel_pub){
    geometry_msgs::Twist move_cmd;
    
    move_cmd.linear.x = 6.0;
    move_cmd.linear.y = 0.0;
    move_cmd.linear.z = 0.0;

    move_cmd.angular.x = 0.0;
    move_cmd.angular.y = 0.0;
    move_cmd.angular.z = 0.0;

    cmd_vel_pub.publish(move_cmd);
}


void speedController::trun_left_quick(ros::Publisher &cmd_vel_pub){
    geometry_msgs::Twist move_cmd;
    
    move_cmd.linear.x = 0.0;
    move_cmd.linear.y = 0.0;
    move_cmd.linear.z = 0.0;

    move_cmd.angular.x = 0.0;
    move_cmd.angular.y = 0.0;
    move_cmd.angular.z = 0.7;

    cmd_vel_pub.publish(move_cmd);
}


void speedController::trun_right_quick(ros::Publisher &cmd_vel_pub){
    geometry_msgs::Twist move_cmd;
    
    move_cmd.linear.x = 0.0;
    move_cmd.linear.y = 0.0;
    move_cmd.linear.z = 0.0;

    move_cmd.angular.x = 0.0;
    move_cmd.angular.y = 0.0;
    move_cmd.angular.z = -0.7;

    cmd_vel_pub.publish(move_cmd);
}


void speedController::low_speed_forward(ros::Publisher &cmd_vel_pub){
    geometry_msgs::Twist move_cmd;
    
    move_cmd.linear.x = 0.5;
    move_cmd.linear.y = 0.0;
    move_cmd.linear.z = 0.0;

    move_cmd.angular.x = 0.0;
    move_cmd.angular.y = 0.0;
    move_cmd.angular.z = 0.0;

    cmd_vel_pub.publish(move_cmd);
}



void speedController::trun_left_low(ros::Publisher &cmd_vel_pub){
    geometry_msgs::Twist move_cmd;
    
    move_cmd.linear.x = 0.0;
    move_cmd.linear.y = 0.2;
    move_cmd.linear.z = 0.0;

    move_cmd.angular.x = 0.0;
    move_cmd.angular.y = 0.0;
    move_cmd.angular.z = 0.1;

    cmd_vel_pub.publish(move_cmd);
}



void speedController::trun_right_low(ros::Publisher &cmd_vel_pub){
    geometry_msgs::Twist move_cmd;
    
    move_cmd.linear.x = 0.0;
    move_cmd.linear.y = 0.0;
    move_cmd.linear.z = 0.0;

    move_cmd.angular.x = 0.0;
    move_cmd.angular.y = 0.0;
    move_cmd.angular.z = -0.1;

    cmd_vel_pub.publish(move_cmd);
}

    void high_speed_forward(ros::Publisher &cmd_vel_pub);
    void low_speed_forward(ros::Publisher &cmd_vel_pub);

    void trun_left_quick(ros::Publisher &cmd_vel_pub);
    void trun_left_low(ros::Publisher &cmd_vel_pub);
    void trun_right_quick(ros::Publisher &cmd_vel_pub);
    void trun_right_low(ros::Publisher &cmd_vel_pub);

    //如果测量数据无效：
    if (ang_msg->data == 180)
    {
        //允许撞击的情况下不做修改
        if (Allow_Collision)
        {
            return;
        }
        //否则将停下来并环顾四周
        high_speed(vel_ctrler, STOP);
        check_around(vel_ctrler);
        return;
    }
    
    if (abs(ang_msg->data)<0.02)
    {
        Allow_Collision = true;
        return;
    }
    else
    {
        if (Allow_Collision)
        {
            if (abs(ang_msg->data)<0.2)
            {
                return;
            }
            
        }
        else
        {
            Allow_Collision = false;
            return;
        }
    }
    

    //正常情况下调整小车角度

    if (is_Attached)
    {
        return;
    }
    
    if(ang_msg->data<0){
        if (abs(ang_msg->data)>0.2)
        {
            high_speed(vel_ctrler, RIGHT);
        }
        else
        {
            low_speed(vel_ctrler, RIGHT);
        }    
    }
    else
    {
        if (abs(ang_msg->data)>0.2)
        {
            high_speed(vel_ctrler, LEFT);
        }
        else
        {
            low_speed(vel_ctrler, LEFT); 
        }
    }

    if (Allow_Collision)
    {
        high_speed(vel_ctrler, FRONT);
    }
    else
    {
        ;
    }



    // // if (dis_msg->data == 0)
    // // {
    // //     check_around(vel_ctrler);
    // //     return;
    // // }

    // //到达检测距离先停止
    // if (dis_msg->data == 10 && Allow_Collision)
    // {
    //     low_speed(vel_ctrler, FRONT);
    //     sleep(500);
    //     high_speed(vel_ctrler, STOP);
    //     Allow_Collision = false;
    //     is_Attached = false;
    //     return;
    // }

    // //判断是否贴近圆柱
    // if (dis_msg->data<0.9)
    // {
    //     is_Attached = true;
    // }

    // if (dis_msg->data>5 && Allow_Collision)
    // {
    //     high_speed(vel_ctrler, FRONT);
    //     return;
    // }
    // if (dis_msg->data < 5 && Allow_Collision)
    // {
    //     return;
    // }
    // if (dis_msg->data<5 && !Allow_Collision)
    // {
    //     high_speed(vel_ctrler, STOP);
    //     high_speed(vel_ctrler, BACK);
    // }
    // if (dis_msg->data>=5 && !Allow_Collision)
    // {
    //     //Allow_Collision = true;
    //     high_speed(vel_ctrler, STOP);
    // }


*/
