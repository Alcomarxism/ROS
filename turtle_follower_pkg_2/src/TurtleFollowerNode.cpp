#include "TurtleFollowerNode.h"
#include <string>
#define QUEUE_SIZE 1

TurtleFollowerNode::TurtleFollowerNode(const rclcpp::NodeOptions & options) : Node("turtle_follower_node",options),TurtleCalculator(){
    this->setTurtleSpeed(this->declare_parameter("turtle_speed", 0.0));
    this->setRotateSpeed(this->declare_parameter("rotate_speed", 0.0));
    myName = this->declare_parameter("my_name", "no_my_name");
    followName = this->declare_parameter("follow_name", "no_follow_name");
    pubMyCmdVel = this->create_publisher<geometry_msgs::msg::Twist>("/"+myName+"/cmd_vel",QUEUE_SIZE);
    subMyPos = this->create_subscription<turtlesim::msg::Pose>("/"+myName+"/pose",QUEUE_SIZE, std::bind(&TurtleFollowerNode::myPoseCallback, this, std::placeholders::_1));
    subTargetPos = this->create_subscription<turtlesim::msg::Pose>("/"+followName+"/pose",QUEUE_SIZE, std::bind(&TurtleFollowerNode::targetPoseCallback, this, std::placeholders::_1));
    spawnTurtle();
}

void TurtleFollowerNode::spawnTurtle(){
    auto client = this->create_client<turtlesim::srv::Spawn>("/spawn");
    client->wait_for_service();
    auto request = std::make_shared<turtlesim::srv::Spawn::Request>();
    request->x = this->getX();
    request->y = this->getY();
    request->theta = this->getTheta();
    request->name = myName;
    client->async_send_request(request);
}


void TurtleFollowerNode::sendControlCommand(){
    geometry_msgs::msg::Twist msg;
    msg.linear.x=getCurrSpeed();
    msg.linear.y=0;
    msg.angular.z=getCurrRotateSpeed();
    pubMyCmdVel->publish(msg);
}

void TurtleFollowerNode::myPoseCallback(const turtlesim::msg::Pose::SharedPtr msg){
    setMyPos(msg->x,msg->y,msg->theta);
}

void TurtleFollowerNode::targetPoseCallback(const turtlesim::msg::Pose::SharedPtr msg){
    setTargetPos(msg->x,msg->y,msg->theta);
    sendControlCommand();
}
