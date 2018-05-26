#!/bin/sh

xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/apeksha/udacity_ws/src/World/myWorld.world" &
sleep 5
xterm -e "roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
xterm -e "roslaunch turtlebot_navigation amcl_demo.launch map_file:=/home/apeksha/udacity_ws/src/wall_follower/maps/mymap.yaml"

