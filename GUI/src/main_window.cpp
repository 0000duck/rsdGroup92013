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
QDateTime pauseDT;
time_t currentTime;
time_t pauseTime;
QDateTime currentTimeDT;
QTimer *timer = new QTimer();
struct itimerspec i;
bool pause = false;
bool running = false;
/*****************************************************************************
** Implementation [MainWindow]
*****************************************************************************/

MainWindow::MainWindow(int argc, char** argv, QWidget *parent)
	: QMainWindow(parent)
	, qnode(argc,argv)
{
	ui.setupUi(this); // Calling this incidentally connects all ui's triggers to on_...() callbacks in this class.

	connect(ui.lcd_order, SIGNAL(valuechanged()), this, SLOT(updateTotalOrders));
	connect(timer, SIGNAL(timeout()), this, SLOT(updateUpTime()));
	connect(timer, SIGNAL(timeout()), this, SLOT(updateOEE()));
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
void MainWindow::on_pushButton_start_clicked(bool check) {
	ROS_INFO("System started!");
	running = true;
	timeStamp = time(0);
	timer->start(1000);
}


void MainWindow::on_pushButton_pause_clicked(bool check) {

	if(pause == true) {
		ROS_INFO("System resumed!");
		pause = false;
		pauseDT.setTime_t(pauseTime);
		//ui.lcd_up->display((pauseDT).toString(QString("hh:mm:ss")));
		pauseDT.setTime_t(pauseTime-timeStamp);
		timeStamp = pauseDT.toTime_t();
		timer->start();
	}
	else {
		ROS_INFO("System paused!");
		pause = true;
		pauseDT = QDateTime::currentDateTimeUtc();
		//pauseDT.setTime_t((pauseDT-timeStamp));
		qDebug() << pauseDT.toString() << endl;
		timer->stop();
		qnode.PauseSystem();
	}
}

void MainWindow::on_pushButton_stop_clicked(bool check) {
	ROS_INFO("System stopped!");
	timer->stop();
}

void MainWindow::updateOEE() {
	int *OEEData = qnode.getOEE();
	ROS_INFO("show[0]: %d",OEEData[0]);
	ui.lcd_a->display(OEEData[0]);
	ui.lcd_p->display(OEEData[1]);
	ui.lcd_q->display(OEEData[2]);
	ui.lcd_oee->display(OEEData[3]);
}

void MainWindow::updateTotalOrders() {
	int tmp = 0;
	qnode.getTotalOrders(tmp);
	ui.lcd_order->display(tmp);
}

void MainWindow::updateUpTime() {
	currentTimeDT = QDateTime::currentDateTimeUtc();
	currentTime = time(0);
	currentTimeDT.setTime_t((currentTime-timeStamp));
	ui.lcd_up->display((currentTimeDT).toString(QString("hh:mm:ss")));
}

/*****************************************************************************
** Implementation [Configuration]
*****************************************************************************/

void MainWindow::ReadSettings() {
    QSettings settings("Qt-Ros Package", "GUI");
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
    ui.lcd_order->display(0);
    ui.lcd_up->display(QTime(0,0,0,0).toString(QString("hh:mm:ss")));
    ui.lcd_a->display(0);
    ui.lcd_p->display(0);
    ui.lcd_q->display(0);
    ui.lcd_oee->display(0);
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

