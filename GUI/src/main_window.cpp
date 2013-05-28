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
#include <string.h>
#include "../include/GUI/main_window.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace GUI {

using namespace Qt;

QTimer *timer = new QTimer();
QTimer *globalTimer = new QTimer();
QTimer *order1Timer = new QTimer();
QTimer *order2Timer = new QTimer();
QTime time, currentTime, updateTime, order1CountDown, order2CountDown;
QDateTime date;
bool pause = false;
bool running = false;
double timeStamp;
double pauseTime;
int secsIterator = 0;
int hh = 0, mm = 0, ss = 0, ord1mm = 0, ord2mm = 0, ord1ss = 0, ord2ss = 0;
/*****************************************************************************
** Implementation [MainWindow]
*****************************************************************************/

MainWindow::MainWindow(int argc, char** argv, QWidget *parent)
	: QMainWindow(parent)
	, qnode(argc,argv)
{
	ui.setupUi(this); // Calling this incidentally connects all ui's triggers to on_...() callbacks in this class.

	connect(timer, SIGNAL(timeout()), this, SLOT(updateTotalOrders()));
	connect(timer, SIGNAL(timeout()), this, SLOT(updateUpTime()));
	connect(timer, SIGNAL(timeout()), this, SLOT(updateOEE()));
	connect(globalTimer, SIGNAL(timeout()), this, SLOT(updateSystemTime()));
	connect(globalTimer, SIGNAL(timeout()), this, SLOT(updateSystemDate()));
	connect(globalTimer, SIGNAL(timeout()), this, SLOT(updateSystemState(std::string state)));
	connect(globalTimer, SIGNAL(timeout()), this, SLOT(OrderCountdown()));
	connect(globalTimer, SIGNAL(timeout()), this, SLOT(updateorderCountdowns()));
	connect(timer, SIGNAL(timeout()), this, SLOT(updateOrderNeeds()));

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
	updateSystemState("RUNNING");
	running = true;
    qnode.pauseTemp=false;
	system("roslaunch MASTER_CONTROL legopicker.launch &");
	ss = 0;
	mm = 0;
	hh = 0;
	updateTime.setHMS(hh,mm,ss,0);
	ui.lcd_up->display(updateTime.toString());
	qnode.startPub();
	time = QTime::currentTime();
	timer->start(1000);

}


void MainWindow::on_pushButton_pause_clicked(bool check) {
	if(pause == true) {
		ROS_INFO("System resumed!");
		pause = false;
		updateSystemState("RUNNING");
		timer->start();
		qnode.PauseSystem();
	}
	else {
		ROS_INFO("System paused!");
		pause = true;
		updateSystemState("SUSPENDED");
		timer->stop();
		qnode.PauseSystem();
	}
}

void MainWindow::on_pushButton_stop_clicked(bool check) {
	ROS_INFO("System stopped!");
	ss = 0;
	mm = 0;
	hh = 0;
	timer->stop();
	updateSystemState("STOPPED");
	system("killall roslaunch");
	qnode.stopPub();
}

void MainWindow::updateOEE() {
	int *OEEData = qnode.getOEE();
	ui.lcd_a->display(OEEData[0]);
	ui.lcd_p->display(OEEData[1]);
	ui.lcd_q->display(OEEData[2]);
	if(OEEData[3] > 200)
		ui.lcd_oee->display(0);
	else
		ui.lcd_oee->display(OEEData[3]);
}

void MainWindow::updateOrderNeeds() {

	if(order1Timer->isActive())
	{
		int *order1Info = qnode.getOrderNeeds(0);
		ui.lcd_red1->display(order1Info[0]);
		ui.lcd_blue1->display(order1Info[1]);
		ui.lcd_yellow1->display(order1Info[2]);
	}

	if(order2Timer->isActive())
	{
		int *order2Info = qnode.getOrderNeeds(1);
		ui.lcd_red2->display(order2Info[0]);
		ui.lcd_blue2->display(order2Info[1]);
		ui.lcd_yellow2->display(order2Info[2]);
	}
}

void MainWindow::updateTotalOrders() {
	int tmp = 0;
	qnode.getTotalOrders(tmp);
	ui.lcd_order->display(tmp);
}


void MainWindow::updateSystemTime() {
	time = QTime::currentTime();
	ui.lcd_system_2->display((time).toString(QString("hh:mm:ss")));
}


void MainWindow::updateSystemDate() {
	ui.lcd_date->display(QDateTime::currentDateTime().toString("dd.MM.yyyy"));
}

void MainWindow::updateUpTime() {
	ss++;
	if(ss == 60)
	{
		ss = 0;
		mm++;
		if(mm == 60)
		{
			mm = 0;
			hh++;
		}
	}
	updateTime.setHMS(hh,mm,ss,0);
	ui.lcd_up->display(updateTime.toString());
}

void MainWindow::OrderCountdown() {

	if(!order1Timer->isActive())
	{
		if(qnode.timerStart == 0)
		{
			order1Timer->start(1);
			ord1ss = 0;
			ord1mm = 3;
		}
	}

	if(!order2Timer->isActive())
	{
		if(qnode.timerStart == 1)
		{
			order2Timer->start(1);
			ord2ss = 0;
			ord2mm = 3;
		}
	}
}

void MainWindow::updateSystemState(std::string state) {
	ui.label_state->setText(QString::fromAscii(state.data(),state.size()));
	if(state == "STOPPED")
	{
		ui.graphics_red->setStyleSheet("background-color: rgb(255,0,0);");
		ui.graphics_yellow->setStyleSheet("background-color: white;");
		ui.graphics_green->setStyleSheet("background-color: white;");
	}
	if(state == "SUSPENDED")
	{
		ui.graphics_yellow->setStyleSheet("background-color: rgb(255,255,0);");
		ui.graphics_red->setStyleSheet("background-color: white;");
		ui.graphics_green->setStyleSheet("background-color: white;");
	}
	if(state == "RUNNING")
	{
		ui.graphics_green->setStyleSheet("background-color: rgb(0,255,0);");
		ui.graphics_yellow->setStyleSheet("background-color: white;");
		ui.graphics_red->setStyleSheet("background-color: white;");
	}
}

void MainWindow::updateorderCountdowns() {


	if(order1Timer->isActive())
	{
		if(ord1ss == 0 && ord1mm == 0)
		{
			qnode.timerStart = -1;
			order1Timer->stop();
			ui.lcd_time1->display((order1CountDown).toString(QString("00:00:00")));
		}

		if(ord1ss == 0 && ord1mm > 0)
		{
			ord1ss = 59;
			ord1mm--;
		}


		order1CountDown.setHMS(00,ord1mm,ord1ss,0);
		ui.lcd_time1->display((order1CountDown).toString(QString("mm:ss")));
		ord1ss--;
	}

	if(order2Timer->isActive())
	{
		if(ord2ss == 0 && ord2mm == 0)
		{
			qnode.timerStart = -1;
			order2Timer->stop();
			ui.lcd_time2->display((order2CountDown).toString(QString("00:00:00")));
		}

		if(ord2ss == 0 && ord2mm > 0)
		{
			ord2ss = 59;
			ord2mm--;
		}

		order2CountDown.setHMS(00,ord2mm,ord2ss,0);
		ui.lcd_time2->display((order2CountDown).toString(QString("mm:ss")));
		ord2ss--;
	}
}

/*****************************************************************************
** Implementation [Configuration]
*****************************************************************************/

void MainWindow::ReadSettings() {
    QSettings settings("Qt-Ros Package", "GUI");
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
    updateTime.QTime::fromString(QString("00:00:00"));
    globalTimer->start(1000);
	date.currentDateTime();
    qnode.setTotalOrders(0);
    qnode.timerStart = -1;
    qnode.newOrder = false;
    qnode.OEEarray[0] = 0;
    qnode.OEEarray[1] = 0;
    qnode.OEEarray[2] = 0;
    qnode.OEEarray[3] = 0;
    qnode.order1Needs[0] = 0;
    qnode.order1Needs[1] = 0;
    qnode.order1Needs[2] = 0;
    qnode.order1Needs[3] = 0;
    qnode.order2Needs[0] = 0;
    qnode.order2Needs[1] = 0;
    qnode.order2Needs[2] = 0;
    qnode.order2Needs[3] = 0;
    ui.lcd_order->display(0);
    std::string state = "STOPPED";
    ui.label_state->setText(QString::fromAscii(state.data(),state.size()));
    ui.lcd_up->display(QTime(0,0,0,0).toString(QString("hh:mm:ss")));
    ui.lcd_time1->display(QTime(0,0,0,0).toString(QString("hh:mm:ss")));
    ui.lcd_time2->display(QTime(0,0,0,0).toString(QString("hh:mm:ss")));
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

