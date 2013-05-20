/**
 * @file /src/main.cpp
 *
 * @brief Qt based gui.
 *
 * @date November 2010
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui>
#include <QApplication>
#include "../include/GUI/main_window.hpp"
#include "ros/ros.h"
#include "std_msgs/String.h"

/*****************************************************************************
** Main
*****************************************************************************/

int main(int argc, char **argv) {

    /*********************
    ** Qt
    **********************/
	ros::init(argc, argv, "robotCommandSender");
    ros::Rate loop_rate(10);
	ros::spinOnce();
	QApplication app(argc, argv);
    GUI::MainWindow w(argc,argv);
    w.show();
    app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));
    int result = app.exec();

	return result;
}
