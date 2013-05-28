/**
 * @file /include/GUI/qnode.hpp
 *
 * @brief Communications central!
 *
 * @date February 2011
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef GUI_QNODE_HPP_
#define GUI_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>
#include <string>
#include <QThread>
#include <QStringListModel>
#include <std_msgs/Int32.h>
#include <std_msgs/Bool.h>
#include "MESSAGES/oee.h"
#include "MESSAGES/order.h"

/*****************************************************************************
** Function declarations
*****************************************************************************/

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace GUI {

/*****************************************************************************
** Class
*****************************************************************************/

class QNode : public QThread {
    Q_OBJECT
public:
	QNode(int argc, char** argv );
	virtual ~QNode();
	bool init();
	void run();
	void PauseSystem();
	void getTotalOrders(int& tmp);
	int* getOEE();
	int* getOrderNeeds(int order);
	void setbrickNeeds(int red, int blue, int yellow, int order);
	void setTotalOrders(int count);
	void setOEE(int A, int P, int Q, int OEE);
	void totalOrdersCallback(const std_msgs::Int32::ConstPtr& msg);
	void newOrderCallback(const std_msgs::Bool::ConstPtr& msg);
	void getOEECallback(const MESSAGES::oee::ConstPtr& msg);
	void brickNeedsCallback(const MESSAGES::order::ConstPtr& msg);
	void startPub();
	void stopPub();
	bool pauseTemp;
	int timerStart;		// Used to indicate which order countdown to start
	bool newOrder;
	int OEEarray[4];		// [0-3]: A, P, Q, OEE
	int order1Needs[4];		// [0-4]: red, blue, yellow, slider
	int order2Needs[4];		// [0-4]: red, blue, yellow, slider


Q_SIGNALS:
    void rosShutdown();

private:
	int init_argc;
	int totalOrdersCount;
	char** init_argv;
	ros::Subscriber TotalOrdersSub;
	ros::Subscriber OEESub;
	ros::Subscriber orderStarted;
	ros::Subscriber orderNeeds;
	ros::Publisher pauseMsg;
	ros::Publisher lightState;
};

}  // namespace GUI


#endif /* GUI_QNODE_HPP_ */
