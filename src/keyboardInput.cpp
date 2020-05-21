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



int main(int argc, char **argv)
{
    
    ros::init(argc, argv, "keyboard");
    ros::NodeHandle n;

    //~ ros::Publisher pub = n.advertise<std_msgs::String>("Key", 1000);
    ros::Publisher pubInt = n.advertise<std_msgs::Int32MultiArray>("intKey1", 1000);
    ros::Rate loop_rate(10);

	//~ std_msgs::String s;
	std_msgs::Int32MultiArray num;
	
	for(int i = 0; i < 4; i++)
	{
		num.data.push_back(0);
	}

    while (ros::ok())
    {
		
        string input;
        cin>>input; 
        //~ s.data = input;
        //~ pub.publish(s);
        
        string StrArray[4] = {"0","0","0","0"};
        
        string delimiter = ",";
        
        size_t pos = 0;
		int i = 0;
		while ((pos = input.find(delimiter)) != std::string::npos) {
			StrArray[i] = input.substr(0, pos);
			input.erase(0, pos + delimiter.length());
			i++;
			if(i == 3)
				break;
		}
		
		StrArray[i] = input;
        
        
        
        num.data[0] = stoi(StrArray[0]); 
        num.data[1] = stoi(StrArray[1]); 
        num.data[2] = stoi(StrArray[2]); 
        num.data[3] = stoi(StrArray[3]); 
		

 
		pubInt.publish(num);
        ros::spinOnce();
        loop_rate.sleep();
    }
}
