num = int(input("n turtles: "))
turtleSpeed=float(input("turtle speed: "))
rotateSpeed=float(input("rotate speed: "))

launch_content="""
<launch>
    <node pkg="turtlesim" type="turtlesim_node" name="turtlesim_node"/>
    <node pkg="turtlesim" type="turtle_teleop_key" name="turtle_teleop_key"/>
"""
launch_content+=f'    <param name="turtle_speed" value="{turtleSpeed}" />\n'
launch_content+=f'    <param name="rotate_speed" value="{rotateSpeed}" />\n'

for i in range(1, num + 1):
    my_name = f"turtle{i+1}"
    follow_name = f"turtle{i}"
    node_name = f"turtle_follower_{i}"       
    launch_content += f'    <node pkg="turtle_follower_pkg" type="turtle_follower_node" name="{node_name}">\n'
    launch_content += f'        <param name="my_name" value="{my_name}"/>\n'
    launch_content += f'        <param name="follow_name" value="{follow_name}"/>\n'
    launch_content += f'    </node>\n'
launch_content += "</launch>"

with open("turtle_centipede.launch","w", encoding="utf-8") as f:
    f.write(launch_content)