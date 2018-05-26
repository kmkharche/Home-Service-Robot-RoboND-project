#include <ros/ros.h>
#include <std_msgs//Int8.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the pick_objects node
  ros::init(argc, argv, "pick_objects");
	
	//Publisher for robot goal status
	ros::NodeHandle n;
	ros::Publisher state_pub = n.advertise<std_msgs::Int8>("goal_state",1);
	std_msgs::Int8 goalState;
	goalState.data=0;
	state_pub.publish(goalState);
	
  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = -2.2;
  goal.target_pose.pose.position.y = 1.6;
  goal.target_pose.pose.orientation.w = 1.0;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Moving to pick up location");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
  {
    ROS_INFO("Robot picking up the object.");
    goalState.data=1;
  }
  else
    ROS_INFO("The base failed to move to pick up.");
  
  state_pub.publish(goalState);
  
  //Wait for 5 seconds
	ros::Duration(5.0).sleep();
	
	ROS_INFO("Robot heading to drop off.");
	
	// set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = 1.4;
  goal.target_pose.pose.position.y = 1.2;
  goal.target_pose.pose.orientation.w = 1.0;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Moving to drop off location");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
  {
    ROS_INFO("Robot reached drop off.");
    goalState.data=2;
  }
  else
    ROS_INFO("The base failed to move to drop off.");

	state_pub.publish(goalState);
  
  return 0;
}
