#include <termios.h>
#include <iostream>     // belongs to blocking input mode
#include <stdio.h>
#include <stdlib.h>
#include <ros/ros.h>
#include "std_msgs/Int32.h"
#include <std_msgs/Int32MultiArray.h>
#include <std_msgs/String.h>

#include <string>


using namespace std;

class sub_class{
    public:
        void SubArrayCallback(const std_msgs::Int32MultiArray::ConstPtr& msg);
        void publish();
        
        sub_class();
        ~sub_class(){};

    private:
        ros::NodeHandle n;
		ros::Publisher pubIntArray = n.advertise<std_msgs::Int32MultiArray>("rx_ST1", 1);
        ros::Subscriber ArraySub = n.subscribe<std_msgs::Int32MultiArray>("intKey1", 1, &sub_class::SubArrayCallback,this);     
        std_msgs::Int32MultiArray numArray;
};

sub_class::sub_class(){
    for(int i = 0; i < 4; i++)
	{
		this->numArray.data.push_back(0);
	}
}

void sub_class::publish(){
	this->pubIntArray.publish(this->numArray);
}

void sub_class::SubArrayCallback(const std_msgs::Int32MultiArray::ConstPtr& msg){
	//~ for(int i = 0; i < 4; i++)
	//~ {
		//~ this->numArray.data[i] = msg->data[i];
	//~ }
	numArray.data = msg->data;
}



int main(int argc, char **argv)
{
    
    ros::init(argc, argv, "pubKeyboard");
    ros::NodeHandle n;


    ros::Rate loop_rate(10);
	sub_class pubKeyboard;
    while (ros::ok())
    {
		//~ ROS_INFO("******");
		
		pubKeyboard.publish();
        ros::spinOnce();
        loop_rate.sleep();
    }
}
