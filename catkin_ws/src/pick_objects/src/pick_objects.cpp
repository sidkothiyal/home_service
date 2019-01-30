#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include "std_msgs/Bool.h"


// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");

  ros::NodeHandle n;

  ros::Publisher marker_status = n.advertise<std_msgs::Bool>("marker_status", 2);
  std_msgs::Bool marker_msg;

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goalPickup;

  // set up the frame parameters
  goalPickup.target_pose.header.frame_id = "map";
  goalPickup.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  goalPickup.target_pose.pose.position.x = 4.0;
  goalPickup.target_pose.pose.position.y = 7.0;
  goalPickup.target_pose.pose.orientation.w = 1.0;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending pick up goal");
  ac.sendGoal(goalPickup);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
    ROS_INFO("Hooray, pick up location reached");
    marker_msg.data = false;
    marker_status.publish(marker_msg);
  }
  else
    ROS_INFO("Failed to reach the pick up location");

  ros::Duration(5.0).sleep();

  move_base_msgs::MoveBaseGoal goalDrop;

  // set up the frame parameters
  goalDrop.target_pose.header.frame_id = "map";
  goalDrop.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  goalDrop.target_pose.pose.position.x = -4.0;
  goalDrop.target_pose.pose.position.y = 7.0;
  goalDrop.target_pose.pose.orientation.w = 1.0;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending drop off goal");
  ac.sendGoal(goalDrop);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
    ROS_INFO("Hooray, drop location reached");
    marker_msg.data = true;
    marker_status.publish(marker_msg);
  }
  else
    ROS_INFO("Failed to reach the drop location");

  
  return 0;
}