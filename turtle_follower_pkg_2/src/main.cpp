#include "rclcpp/rclcpp.hpp"
#include "TurtleFollowerNode.h"

int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<TurtleFollowerNode>());
    rclcpp::shutdown();
    return 0;
}

