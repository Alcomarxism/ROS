from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import TimerAction

NUM_TURTLES=50

def generate_launch_description():
    nodesList=[
       Node(
            package='turtlesim',
            executable='turtlesim_node',
            name='ts_node',
        ),
        Node(
            package='turtlesim',
            executable='turtle_teleop_key',
            name='ts_teleop_key',
            prefix='xterm -e'
        )
    ]
    for i in range(1, NUM_TURTLES):
        follower_node = Node(
            package='turtle_follower_pkg_2',
            executable='turtle_follower_node',
            name=f'follower_{i}',
            parameters=[
                {'my_name': f'turtle{i+1}'},
                {'follow_name': f'turtle{i}'},
                {'turtle_speed': 3.0},
                {'rotate_speed': 30.0}
            ]
        )
        nodesList.append(TimerAction(period=i * 0.1, actions=[follower_node]))
    return LaunchDescription(nodesList)

