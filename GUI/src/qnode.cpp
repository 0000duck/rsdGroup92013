/**
 * @file /src/qnode.cpp
 *
 * @brief Ros communication central!
 *
 * @date February 2011
 **/

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>
#include <ros/network.h>
#include <string>
#include <vector>
#include <std_msgs/Int32.h>
#include <std_msgs/Int8.h>
#include <cstdlib>
#include <std_msgs/String.h>
#include <std_msgs/Bool.h>
#include <sstream>
#include "../include/GUI/qnode.hpp"
#include "MESSAGES/oee.h"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace GUI {


/*****************************************************************************
** Implementation
*****************************************************************************/

void QNode::getTotalOrders(int& tmp) {
	tmp=QNode::totalOrdersCount;
}

int* QNode::getOEE() {
	return QNode::OEEarray;
}

void QNode::setTotalOrders(int count) {
	totalOrdersCount = count;
}

void QNode::setOEE(int A, int P, int Q, int OEE) {
	OEEarray[0] = A;
	OEEarray[1] = P;
	OEEarray[2] = Q;
	OEEarray[3] = OEE;
}

void QNode::totalOrdersCallback(const std_msgs::Int32::ConstPtr& msg)
{
	setTotalOrders(msg->data);
}

void QNode::getOEECallback(const MESSAGES::oee::ConstPtr& msg)
{
	setOEE(msg->availability,msg->performance,msg->quality,msg->oee);
}


QNode::QNode(int argc, char** argv ) :
	init_argc(argc),
	init_argv(argv)

	{}

QNode::~QNode() {
    if(ros::isStarted()) {
      ros::shutdown(); // explicitly needed since we use ros::start();
      ros::waitForShutdown();
    }
	wait();
}

bool QNode::init() {
	ros::init(init_argc,init_argv,"GUI");
	if ( ! ros::master::check() ) {
		return false;
	}
	ros::start(); // explicitly needed since our nodehandle is going out of scope.
    ros::NodeHandle h;
    TotalOrdersSub = h.subscribe("/totalOrders", 10, &QNode::totalOrdersCallback, this);
    OEESub = h.subscribe("/oeeInfo", 10, &QNode::getOEECallback, this);
    pauseMsg = h.advertise<std_msgs::Bool>("/systemPause", 10);
    lightState = h.advertise<std_msgs::Int8>("/lightState", 10);
	start();
	return true;
}


void QNode::run() {
	ros::Rate loop_rate(1);
	int count = 0;
	while ( ros::ok() ) {

		ros::spinOnce();
		loop_rate.sleep();
		++count;
	}
	std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;
	Q_EMIT rosShutdown(); // used to signal the gui for a shutdown (useful to roslaunch)
}

void QNode::PauseSystem() {
	std_msgs::Bool pauseSig;
	std_msgs::Int8 light;
	if(pauseTemp==false){
		light.data = 1;
		pauseSig.data = true;
		pauseTemp=true;
	}
	else{
		light.data = 2;
		pauseSig.data = false;
		pauseTemp=false;
	}

	pauseMsg.publish(pauseSig);
	lightState.publish(light);
	/*if(!pauseMsg)
	{
		ROS_WARN("Publisher invalid!");
	}
	else
	{
		pauseMsg.publish(pauseSig);
	}*/
}

void QNode::startPub() {
	std_msgs::Int8 light;
	light.data = 2; // green
	if(!lightState)
	{
		ROS_WARN("Publisher invalid!");
	}
	else
	{
		lightState.publish(light);
	}

}

void QNode::stopPub() {
	std_msgs::Int8 light;
	light.data = 0; //red
	if(!lightState)
	{
		ROS_WARN("Publisher invalid!");
	}
	else
	{
		lightState.publish(light);
	}

}


}  // namespace GUI
