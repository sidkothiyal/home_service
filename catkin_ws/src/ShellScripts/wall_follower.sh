#!/bin/sh
DIR1="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
DIR2=$(dirname "$0")

#xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=//home/siddharth/Desktop/home_service/src/World/u_world.world" &
xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$DIR1/$DIR2/../World/u_world.world" &
sleep 10
#xterm -e "roslaunch turtlebot_gazebo gmapping_demo.launch custom_gmapping_launch_file:=//home/siddharth/Desktop/home_service/src/turtlebot_simulator/turtlebot_gazebo/launch/includes/gmapping.launch.xml" &
xterm -e "roslaunch turtlebot_gazebo gmapping_demo.launch custom_gmapping_launch_file:=$DIR1/$DIR2/../turtlebot_simulator/turtlebot_gazebo/launch/includes/gmapping.launch.xml" &
sleep 5
xterm -e "roslaunch turtlebot_rviz_launchers  view_navigation.launch" &
sleep 5
xterm -e "rosrun wall_follower wall_follower" &
