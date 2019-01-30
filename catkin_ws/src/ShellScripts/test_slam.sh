#!/bin/sh
DIR1="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
DIR2=$(dirname "$0")

#xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=//home/siddharth/Desktop/home_service/src/World/u_world.world" &
xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$DIR1/$DIR2/../World/u_world.world" &
sleep 5
xterm -e "roslaunch turtlebot_teleop keyboard_teleop.launch" &
sleep 5
xterm -e "roslaunch turtlebot_gazebo gmapping_demo.launch" &
sleep 5
xterm -e "roslaunch turtlebot_rviz_launchers  view_navigation.launch" &
