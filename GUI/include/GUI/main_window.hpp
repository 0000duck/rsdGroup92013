/**
 * @file /include/GUI/main_window.hpp
 *
 * @brief Qt based gui for GUI.
 *
 * @date November 2010
 **/
#ifndef GUI_MAIN_WINDOW_H
#define GUI_MAIN_WINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui/QMainWindow>
#include "ui_main_window.h"
#include "qnode.hpp"

/*****************************************************************************
** Namespace
*****************************************************************************/

namespace GUI {

/*****************************************************************************
** Interface [MainWindow]
*****************************************************************************/
/**
 * @brief Qt central, all operations relating to the view part here.
 */
class MainWindow : public QMainWindow {
Q_OBJECT

public:
	MainWindow(int argc, char** argv, QWidget *parent = 0);
	~MainWindow();
	void ReadSettings(); // Load up qt program settings at startup
	void WriteSettings(); // Save qt program settings when closing

	void closeEvent(QCloseEvent *event); // Overloaded function

public Q_SLOTS:
	/******************************************
	** Auto-connections (connectSlotsByName())
	*******************************************/
	void on_pushButton_pause_clicked(bool check);
	void on_pushButton_start_clicked(bool check);
	void on_pushButton_stop_clicked(bool check);
	void updateOEE();
	void updateUpTime();
	void OrderCountdown();
	void updateSystemTime();
	void updateSystemDate();
	void updateTotalOrders();
	void updateSystemState(std::string state);
	void updateorderCountdowns();
	void updateOrderNeeds();
    /******************************************
    ** Manual connections
    *******************************************/

private:
	Ui::MainWindowDesign ui;
	QNode qnode;
};

}  // namespace GUI

#endif // GUI_MAIN_WINDOW_H
