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
#include <std_msgs/Int64.h>
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
	ROS_INFO("getOEE");
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

void QNode::totalOrdersCallback(const std_msgs::Int64::ConstPtr& msg)
{
	setTotalOrders(msg->data);
	ROS_INFO("Total orders incremented");
}

void QNode::getOEECallback(const MESSAGES::oee::ConstPtr& msg)
{
	setOEE(msg->availability,msg->performance,msg->quality,msg->oee);
	ROS_INFO("Updated OEE numbers");
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
	pauseSig.data = true;
	if(!pauseMsg)
	{
		ROS_WARN("Publisher invalid!");
	}
	else
	{
		pauseMsg.publish(pauseSig);
	}
}


}  // namespace GUI
