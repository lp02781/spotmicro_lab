#include <iostream>
#include <stdio.h>

#include "ros/ros.h"
#include "std_msgs/Float64.h"

ros::Publisher pub_servo;
std_msgs::Float64 servo;

int main(int argc, char **argv){
	ros::init(argc, argv, "servo");
	ros::NodeHandle n;

	pub_servo = n.advertise<std_msgs::Float64>("/servo_input", 10);
  
	while(ros::ok()){
		float i=-1.0;
		for(i=-1.0;i<1.0;i+=0.2){
			servo.data=i;
			pub_servo.publish(servo);
			sleep(1);
			ros::spinOnce();
		}
		for(i=1.0;i<-1.0;i-=0.2){
			servo.data=i;
			pub_servo.publish(servo);
			sleep(1);
			ros::spinOnce();
		}
	}
}
