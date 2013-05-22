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
#include <std_msgs/Int64.h>
#include "MESSAGES/oee.h"

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
	void setTotalOrders(int count);
	void setOEE(int A, int P, int Q, int OEE);
	void totalOrdersCallback(const std_msgs::Int64::ConstPtr& msg);
	void getOEECallback(const MESSAGES::oee::ConstPtr& msg);


Q_SIGNALS:
    void rosShutdown();

private:
	int init_argc;
	int totalOrdersCount;
	int OEEarray[4];		// [0-3]: A, P, Q, OEE
	char** init_argv;
	ros::Subscriber TotalOrdersSub;
	ros::Subscriber OEESub;
	ros::Publisher pauseMsg;
};

}  // namespace GUI


#endif /* GUI_QNODE_HPP_ */
