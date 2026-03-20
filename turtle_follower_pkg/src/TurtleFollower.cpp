#include "TurtleFollower.h"
#include "turtlesim/Spawn.h"
#include "geometry_msgs/Twist.h"
#define QUEUE_SIZE 1000

TurtleFollower::TurtleFollower(ros::NodeHandle nhandle,std::string myName,std::string followName,float turtleSpeed,float turtleRotateSpeed):TurtleCalculator(turtleSpeed,turtleRotateSpeed),nh(nhandle){
    pubMyCmdVel = nh.advertise<geometry_msgs::Twist>("/"+myName+"/cmd_vel", QUEUE_SIZE);
    subTargetPos = nh.subscribe("/"+followName+"/pose",QUEUE_SIZE,&TurtleFollower::targetPoseCallback, this);
    subMyPos = nh.subscribe("/"+myName+"/pose",QUEUE_SIZE,&TurtleFollower::myPoseCallback, this);
    spawnTurtle(myName);	
}

void TurtleFollower::spawnTurtle(std::string name){
    ros::ServiceClient client = nh.serviceClient<turtlesim::Spawn>("/spawn");
    client.waitForExistence();
    turtlesim::Spawn srv;
    srv.request.x = getX();
    srv.request.y = getY();
    srv.request.theta = getTheta();
    srv.request.name = name;
    client.call(srv);
}

void TurtleFollower::sendControlCommand(){
    geometry_msgs::Twist msg;
    msg.linear.x=getCurrSpeed();
    msg.linear.y=0;
    msg.angular.z=getCurrRotateSpeed();
    pubMyCmdVel.publish(msg);
}

void TurtleFollower::myPoseCallback(const turtlesim::Pose::ConstPtr& msg){
    setMyPos(msg->x,msg->y,msg->theta);
    sendControlCommand();
}

void TurtleFollower::targetPoseCallback(const turtlesim::Pose::ConstPtr& msg){
    setTargetPos(msg->x,msg->y,msg->theta);
    sendControlCommand();
}

