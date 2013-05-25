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
QTime time, currentTime, updateTime;
QDateTime date;
bool pause = false;
bool running = false;
double timeStamp;
double pauseTime;
int secsIterator = 0;
int hh = 0, mm = 0, ss = 0;
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
	connect(globalTimer, SIGNAL(timeout()), this, SLOT(updateSystemState()));

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




//		QPixmap pixmap("yellow.png");
//		scene.addPixmap(pixmap);
//		ui.graphics_yellow->setScene(&scene);
//		ui.graphics_yellow->show();



//		QPixmap pixmap("green.png");
//		scene.addPixmap(pixmap);
//		ui.graphics_green->setScene(&scene);
//		ui.graphics_green->show();

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
    ui.lcd_order->display(0);
    std::string state = "STOPPED";
    ui.label_state->setText(QString::fromAscii(state.data(),state.size()));
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

