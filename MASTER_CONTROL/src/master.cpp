// rosnode to send commands to robot
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Int64.h"
#include "std_msgs/Bool.h"
#include "MESSAGES/oee.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string>
#include <vector>

using namespace std;

#define PTIME 86400 // 24 hours in seconds
#define idealCycleTime 35

double stopTime =0;
double stallTime = 0;
double ordersStarted =0;
double ordersCompleted=0;
bool sysPause=false;
bool temp=true;


double calcAvailability(double runTime, double plannedTime){
	if(plannedTime<1)
		return 100;

	return   runTime / plannedTime * 100;
}

double calcPerformance(double runTime){
	if(runTime<1)
		return 100;
	if(ordersStarted<1)
		return 100;

	return (idealCycleTime * ordersCompleted) / runTime * 100;
}

double calcQuality(){
	if(ordersStarted<1)
		return 100;

	return ordersCompleted / ordersStarted * 100;
}

int calcOEE(double a, double p, double q){
	return int( (a/100*p/100*q/100)*100 );
}

void oCompCallback(const std_msgs::Int64::ConstPtr& msg)
{
	if(msg->data>0)
		ordersCompleted++;
}

void oStartCallback(const std_msgs::Int64::ConstPtr& msg)
{
	if(msg->data>0)
		ordersStarted++;
}

void pauseCallback(const std_msgs::Bool::ConstPtr& msg)
{
	if(msg->data==true && temp==true){
		stopTime=ros::Time::now().toSec();
		temp=false;
	}
	if(msg->data==false && temp==false){
		stallTime+=ros::Time::now().toSec()-stopTime;
		stopTime=0;
		temp=true;
	}

}


int main(int argc, char *argv[])
{
	ros::init(argc, argv, "master");
	ros::NodeHandle h;
 	ros::Publisher oeePub = h.advertise<MESSAGES::oee>("/oeeInfo", 10);
 	ros::Publisher timePub = h.advertise<std_msgs::Int64>("/time", 1);
 	ros::Publisher packMLPub = h.advertise<std_msgs::Int64>("/packMLState", 10);
 	ros::Subscriber compSub = h.subscribe("/orderComplete", 10, oCompCallback);
 	ros::Subscriber staSub = h.subscribe("/orderStarted", 10, oStartCallback);
 	ros::Subscriber pauSub = h.subscribe("/systemPause", 10, pauseCallback);
	ros::Rate loop_rate(1);

 	double plannedTime = 0;
 	double offset = -ros::Time::now().toSec();


	while (ros::ok())
	{
		//ROS_INFO("%f", ros::Time::now().toSec());

		plannedTime = ros::Time::now().toSec()+offset;
		double a = calcAvailability(plannedTime-stallTime,plannedTime);
		double p = calcPerformance(plannedTime-stallTime);
		double q = calcQuality();
		int oee = calcOEE(a,p,q);

		MESSAGES::oee oeeInfo;
		oeeInfo.availability=int(a);
		oeeInfo.performance=int(p);
		oeeInfo.quality=int(q);
		oeeInfo.oee=int(oee);
		oeePub.publish(oeeInfo);

		std_msgs::Int64 timeMsg;
		timeMsg.data=plannedTime-stallTime;
		timePub.publish(timeMsg);


		ros::spinOnce();
		loop_rate.sleep();
	}

    return 0;
}
