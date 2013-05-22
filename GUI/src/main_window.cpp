/**
 * @file /src/main_window.cpp
 *
 * @brief Implementation for the qt gui.
 *
 * @date February 2011
 **/
/*****************************************************************************
** Includes
*****************************************************************************/
#include <ros/ros.h>
#include <ros/network.h>
#include <QtGui>
#include <QMessageBox>
#include <iostream>
#include <ctime>
#include "../include/GUI/main_window.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace GUI {

using namespace Qt;

time_t timeStamp = time(0);
/*****************************************************************************
** Implementation [MainWindow]
*****************************************************************************/

MainWindow::MainWindow(int argc, char** argv, QWidget *parent)
	: QMainWindow(parent)
	, qnode(argc,argv)
{
	ui.setupUi(this); // Calling this incidentally connects all ui's triggers to on_...() callbacks in this class.
	QTimer *timer = new QTimer(this);
	timer->start(1000);
	connect(ui.lcd_order, SIGNAL(timeout()), this, SLOT(updateTotalOrders));
	connect(timer, SIGNAL(timeout()), this, SLOT(updateUpTime()));

	ReadSettings();
	setWindowIcon(QIcon(":/images/icon.png"));
	if(!qnode.init())
	{
		ROS_WARN("Initializing error in ROS!");
	}
}

MainWindow::~MainWindow() {}

/*****************************************************************************
** Implementation [Slots]
*****************************************************************************/

void MainWindow::on_pushButton_pause_clicked(bool check)
{
	ROS_INFO("Pause button pushed!");
	qnode.PauseSystem();
}

void MainWindow::updateTotalOrders() {
	int tmp = 0;
	qnode.getTotalOrders(tmp);
	ui.lcd_order->display(tmp);
}

void MainWindow::updateUpTime() {
	QDateTime currentTime = QDateTime::currentDateTimeUtc();
	time_t currentTimeTime_t = time(0);
	currentTime.setTime_t((currentTimeTime_t-timeStamp));
	ui.lcd_run->display((currentTime).toString(QString("mm:ss")));		// TODO: Change to add hours in new UI
}

/*****************************************************************************
** Implementation [Configuration]
*****************************************************************************/

void MainWindow::ReadSettings() {
    QSettings settings("Qt-Ros Package", "GUI");
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
    ui.lcd_order->display(0);
    ui.lcd_run->display(QTime(0,0,0,0).toString(QString("mm:ss")));				// TODO: Change to add hours in new UI
}

void MainWindow:: WriteSettings() {
    QSettings settings("Qt-Ros Package", "GUI");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
}

void MainWindow::closeEvent(QCloseEvent *event) {
	WriteSettings();
	QMainWindow::closeEvent(event);
}

}  // namespace GUI

