cmake_minimum_required(VERSION 3.8)
project(turtle_follower_pkg_2)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(turtlesim REQUIRED)
find_package(geometry_msgs REQUIRED)


include_directories(include)

add_executable(
    turtle_follower_node
    src/TurtleFollowerNode.cpp
    src/main.cpp
    src/TurtleCalculator.cpp
)

ament_target_dependencies(turtle_follower_node rclcpp)
ament_target_dependencies(turtle_follower_node turtlesim)
ament_target_dependencies(turtle_follower_node geometry_msgs)

install(DIRECTORY
  include/
  DESTINATION include
)

install(TARGETS
  turtle_follower_node
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}
)

