#include "rclcpp/rclcpp.hpp"
#include "TurtleCalculator.h"
#include "turtlesim/msg/pose.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "turtlesim/srv/spawn.hpp"

class TurtleFollowerNode : public rclcpp::Node, public TurtleCalculator {
private:
    std::string myName;
    std::string followName;
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr subTargetPos;
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr subMyPos;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr pubMyCmdVel;
    void spawnTurtle();
    void myPoseCallback(const turtlesim::msg::Pose::SharedPtr msg);
    void targetPoseCallback(const turtlesim::msg::Pose::SharedPtr msg);
    void sendControlCommand();
public:
    TurtleFollowerNode(const rclcpp::NodeOptions & options = rclcpp::NodeOptions());
};
