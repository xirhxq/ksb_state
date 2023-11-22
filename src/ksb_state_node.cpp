#include "ros/ros.h"
#include "std_msgs/String.h"
#include "gpioin.hpp"
#include <iostream>
using namespace std;

int main(int argc, char **argv) {
    ros::init(argc, argv, "ksbState_publisher");
    ros::NodeHandle n;
    ros::Publisher level_pub = n.advertise<std_msgs::String>("/ksb_state", 100);
    ros::Rate loop_rate(10);

    gpio *gp1 = new gpio();
    gpio *gp2 = new gpio();

    if(gp1->openGpio(BUZZER1) != 0 || gp2->openGpio(BUZZER2) != 0)
    {
        ROS_ERROR("Failed to open GPIO");
        return -1;
    }

    sleep(1);

    if(gp1->setGpioDirection(NAME1, DIRECTION1) != 0 || gp2->setGpioDirection(NAME2, DIRECTION2) != 0)
    {
        ROS_ERROR("Failed to set GPIO direction");
        gp1->closeGpio(BUZZER1);
        gp2->closeGpio(BUZZER2);
        return -1;
    }
    
    while (n.ok())
    {
        int level1 = gp1->readGPIOValue(NAME1);
        int level2 = gp2->readGPIOValue(NAME2);
        std_msgs::String level_msg;
        if (level1 == 0 && level2 == 0) {
            level_msg.data = "GoHome";
        } else if (level1 == 0 && level2 == 1) {
            level_msg.data = "TargetRejected";
        } else if (level1 == 1 && level2 == 0) {
            level_msg.data = "TargetConfirmed";
        } else if (level1 == 1 && level2 == 1) {
            level_msg.data = "NormalState";
        }
        level_pub.publish(level_msg);
        ros::spinOnce();
        loop_rate.sleep();
    }

    gp1->closeGpio(BUZZER1);
    gp2->closeGpio(BUZZER2);
    delete gp1;
    delete gp2;

    return 0;
}