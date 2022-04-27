#include <ros/ros.h>
#include "std_msgs/String.h"
#include <iostream>

using namespace std;
string temp;
	
void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
		ROS_INFO("I heard: [%s]", msg->data.c_str());
		temp = msg-> data.c_str();
}

int main(int argc, char **argv)

{	
	ros::Rate loop_rate(10);
	ros::init(argc, argv, "ros");
	ros::NodeHandle n;
	ros::Publisher chatter_pub = n.advertise<std_msgs::String>("RosToForsyde", 1000);
	while (ros::ok())
	{
		ros::Subscriber sub = n.subscribe("ForsydeToRos", 1000, chatterCallback);
		std_msgs::String msg;
		stringstream ss;
		ss << "-" << temp;
		msg.data = ss.str();       
		ROS_INFO("%s", msg.data.c_str());
		chatter_pub.publish(msg);
		loop_rate.sleep();
		ros::spin();
	}
	
	return 0;
}

