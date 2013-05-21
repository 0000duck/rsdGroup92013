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
#include "../include/GUI/main_window.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace GUI {

using namespace Qt;


/*****************************************************************************
** Implementation [MainWindow]
*****************************************************************************/

MainWindow::MainWindow(int argc, char** argv, QWidget *parent)
	: QMainWindow(parent)
	, qnode(argc,argv)
{
	ui.setupUi(this); // Calling this incidentally connects all ui's triggers to on_...() callbacks in this class.
    //QObject::connect(ui.actionAbout_Qt, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt())); // qApp is a global variable for the application
	connect(ui.lcd_order, SIGNAL(valueChanged()), this, SLOT(updateOrders));
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
void MainWindow::on_pushButton_start_clicked(bool check)
{
	ROS_INFO("Button clicked!");
	ui.lcd_order->display(2);
}

void MainWindow::on_pushButton_pause_clicked(bool check)
{
	ROS_INFO("Pause button pushed!");
	qnode.PauseSystem();
}

void MainWindow::updateOrders() {
	ui.lcd_order->display(getTotalOrders());
}
/*****************************************************************************
** Implementation [Configuration]
*****************************************************************************/

void MainWindow::ReadSettings() {
    QSettings settings("Qt-Ros Package", "GUI");
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
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

