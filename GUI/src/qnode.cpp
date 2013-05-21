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

/*****************************************************************************
** Namespaces
*****************************************************************************/
int TotalOrders = 1;

int getTotalOrders() {
	return TotalOrders;
}

namespace GUI {


/*****************************************************************************
** Implementation
*****************************************************************************/
void TotalOrdersCallback(const std_msgs::Int64::ConstPtr& msg)
{
	TotalOrders = msg->data;
	ROS_INFO("Total orders incremented");
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
    TotalOrdersSub = h.subscribe("TotalOrders", 10, TotalOrdersCallback);
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
