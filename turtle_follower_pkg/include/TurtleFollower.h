#include "ros/ros.h"
#include "TurtleCalculator.h"
#include "turtlesim/Pose.h"

class TurtleFollower:public TurtleCalculator{
private:
    ros::NodeHandle nh;
    ros::Publisher pubMyCmdVel;
    ros::Subscriber subMyPos;
    ros::Subscriber subTargetPos;
    void spawnTurtle(std::string name);
    void myPoseCallback(const turtlesim::Pose::ConstPtr& msg);
    void targetPoseCallback(const turtlesim::Pose::ConstPtr& msg);
    void sendControlCommand();
public:
    TurtleFollower(ros::NodeHandle nh,std::string myName,std::string followName,float turtleSpeed,float turtleRotateSpeed);
};