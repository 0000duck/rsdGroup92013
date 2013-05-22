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
	bool init(const std::string &master_url, const std::string &host_url);
	void run();
	void PauseSystem();
	void getTotalOrders(int& tmp);
	void setTotalOrders(int count);
	void TotalOrdersCallback(const std_msgs::Int64::ConstPtr& msg);


Q_SIGNALS:
    void rosShutdown();

private:
	int init_argc;
	int totalOrdersCount;
	char** init_argv;
	ros::Subscriber sub;
	ros::Subscriber TotalOrdersSub;
	ros::Publisher pauseMsg;
    QStringListModel logging_model;
};

}  // namespace GUI


#endif /* GUI_QNODE_HPP_ */
