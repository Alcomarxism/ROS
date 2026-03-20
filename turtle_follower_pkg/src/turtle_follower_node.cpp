#include "ros/ros.h"
#include "TurtleFollower.h"
#include <string>


int main(int argc, char **argv) {
    ros::init(argc, argv, "turtle_follower_node");
    ros::NodeHandle nh("~");
    std::string myName;
    std::string followName;
    float turtleSpeed;
    float rotateSpeed;
    nh.getParam("my_name", myName);
    nh.getParam("follow_name",followName);
    nh.getParam("/turtle_speed",turtleSpeed);
    nh.getParam("/rotate_speed",rotateSpeed);
    TurtleFollower tf(nh,myName,followName,turtleSpeed,rotateSpeed);
    ros::spin();
    return 0;
}

