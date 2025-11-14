#pragma once
#include "../include/distance.hpp"
#include "../include/speedController.hpp"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "shc_v2_node");
    ros::NodeHandle nh;
    speedController stroller(nh);
    distance dis(nh);
    ros::spin();
    return 0;
}
