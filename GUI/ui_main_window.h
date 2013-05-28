/********************************************************************************
** Form generated from reading UI file 'main_window.ui'
**
** Created: Mon May 27 15:43:48 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_WINDOW_H
#define UI_MAIN_WINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGraphicsView>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowDesign
{
public:
    QAction *action_Quit;
    QAction *action_Preferences;
    QAction *actionAbout;
    QAction *actionAbout_Qt;
    QWidget *centralwidget;
    QHBoxLayout *hboxLayout;
    QFrame *frame_2;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_2;
    QLCDNumber *lcd_oee;
    QLCDNumber *lcd_a;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLCDNumber *lcd_q;
    QLCDNumber *lcd_p;
    QWidget *horizontalLayoutWidget_6;
    QHBoxLayout *horizontalLayout_6;
    QGraphicsView *graphics_red;
    QGraphicsView *graphics_yellow;
    QGraphicsView *graphics_green;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_8;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_8;
    QLCDNumber *lcd_date;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_7;
    QLCDNumber *lcd_system_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_9;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_state;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_10;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_12;
    QLCDNumber *lcd_up;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label;
    QHBoxLayout *horizontalLayout_15;
    QLCDNumber *lcd_order;
    QHBoxLayout *horizontalLayout_13;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton_start;
    QPushButton *pushButton_pause;
    QPushButton *pushButton_stop;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout_16;
    QHBoxLayout *horizontalLayout_26;
    QLabel *label_10;
    QHBoxLayout *horizontalLayout_27;
    QLabel *label_order1;
    QHBoxLayout *horizontalLayout_17;
    QHBoxLayout *horizontalLayout_28;
    QLabel *label_12;
    QHBoxLayout *horizontalLayout_29;
    QLCDNumber *lcd_time1;
    QHBoxLayout *horizontalLayout_18;
    QHBoxLayout *horizontalLayout_30;
    QLabel *label_13;
    QHBoxLayout *horizontalLayout_32;
    QLCDNumber *lcd_red1;
    QHBoxLayout *horizontalLayout_19;
    QHBoxLayout *horizontalLayout_33;
    QLabel *label_14;
    QHBoxLayout *horizontalLayout_34;
    QLCDNumber *lcd_blue1;
    QHBoxLayout *horizontalLayout_20;
    QHBoxLayout *horizontalLayout_35;
    QLabel *label_15;
    QHBoxLayout *horizontalLayout_36;
    QLCDNumber *lcd_yellow1;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_21;
    QHBoxLayout *horizontalLayout_37;
    QLabel *label_11;
    QHBoxLayout *horizontalLayout_38;
    QLabel *label_order2;
    QHBoxLayout *horizontalLayout_22;
    QHBoxLayout *horizontalLayout_39;
    QLabel *label_16;
    QHBoxLayout *horizontalLayout_40;
    QLCDNumber *lcd_time2;
    QHBoxLayout *horizontalLayout_23;
    QHBoxLayout *horizontalLayout_41;
    QLabel *label_17;
    QHBoxLayout *horizontalLayout_42;
    QLCDNumber *lcd_red2;
    QHBoxLayout *horizontalLayout_24;
    QHBoxLayout *horizontalLayout_43;
    QLabel *label_18;
    QHBoxLayout *horizontalLayout_44;
    QLCDNumber *lcd_blue2;
    QHBoxLayout *horizontalLayout_25;
    QHBoxLayout *horizontalLayout_45;
    QLabel *label_19;
    QHBoxLayout *horizontalLayout_46;
    QLCDNumber *lcd_yellow2;
    QMenuBar *menubar;
    QMenu *menu_File;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindowDesign)
    {
        if (MainWindowDesign->objectName().isEmpty())
            MainWindowDesign->setObjectName(QString::fromUtf8("MainWindowDesign"));
        MainWindowDesign->resize(691, 677);
        MainWindowDesign->setMouseTracking(false);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindowDesign->setWindowIcon(icon);
        MainWindowDesign->setLocale(QLocale(QLocale::English, QLocale::Australia));
        action_Quit = new QAction(MainWindowDesign);
        action_Quit->setObjectName(QString::fromUtf8("action_Quit"));
        action_Quit->setShortcutContext(Qt::ApplicationShortcut);
        action_Preferences = new QAction(MainWindowDesign);
        action_Preferences->setObjectName(QString::fromUtf8("action_Preferences"));
        actionAbout = new QAction(MainWindowDesign);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionAbout_Qt = new QAction(MainWindowDesign);
        actionAbout_Qt->setObjectName(QString::fromUtf8("actionAbout_Qt"));
        centralwidget = new QWidget(MainWindowDesign);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        hboxLayout = new QHBoxLayout(centralwidget);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayoutWidget = new QWidget(frame_2);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(20, 10, 271, 381));
        gridLayout_2 = new QGridLayout(gridLayoutWidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        lcd_oee = new QLCDNumber(gridLayoutWidget);
        lcd_oee->setObjectName(QString::fromUtf8("lcd_oee"));

        gridLayout_2->addWidget(lcd_oee, 0, 2, 1, 1);

        lcd_a = new QLCDNumber(gridLayoutWidget);
        lcd_a->setObjectName(QString::fromUtf8("lcd_a"));

        gridLayout_2->addWidget(lcd_a, 1, 2, 1, 1);

        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 0, 1, 1, 1);

        label_5 = new QLabel(gridLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 1, 1, 1, 1);

        label_6 = new QLabel(gridLayoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 2, 1, 1, 1);

        label_7 = new QLabel(gridLayoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_2->addWidget(label_7, 3, 1, 1, 1);

        lcd_q = new QLCDNumber(gridLayoutWidget);
        lcd_q->setObjectName(QString::fromUtf8("lcd_q"));

        gridLayout_2->addWidget(lcd_q, 3, 2, 1, 1);

        lcd_p = new QLCDNumber(gridLayoutWidget);
        lcd_p->setObjectName(QString::fromUtf8("lcd_p"));

        gridLayout_2->addWidget(lcd_p, 2, 2, 1, 1);

        horizontalLayoutWidget_6 = new QWidget(frame_2);
        horizontalLayoutWidget_6->setObjectName(QString::fromUtf8("horizontalLayoutWidget_6"));
        horizontalLayoutWidget_6->setGeometry(QRect(300, 119, 361, 81));
        horizontalLayout_6 = new QHBoxLayout(horizontalLayoutWidget_6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        graphics_red = new QGraphicsView(horizontalLayoutWidget_6);
        graphics_red->setObjectName(QString::fromUtf8("graphics_red"));
        graphics_red->setAutoFillBackground(true);
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::NoBrush);
        graphics_red->setBackgroundBrush(brush);
        graphics_red->setInteractive(false);

        horizontalLayout_6->addWidget(graphics_red);

        graphics_yellow = new QGraphicsView(horizontalLayoutWidget_6);
        graphics_yellow->setObjectName(QString::fromUtf8("graphics_yellow"));
        graphics_yellow->setAutoFillBackground(true);
        QBrush brush1(QColor(0, 170, 0, 255));
        brush1.setStyle(Qt::NoBrush);
        graphics_yellow->setBackgroundBrush(brush1);
        QBrush brush2(QColor(0, 170, 0, 255));
        brush2.setStyle(Qt::NoBrush);
        graphics_yellow->setForegroundBrush(brush2);
        graphics_yellow->setInteractive(true);

        horizontalLayout_6->addWidget(graphics_yellow);

        graphics_green = new QGraphicsView(horizontalLayoutWidget_6);
        graphics_green->setObjectName(QString::fromUtf8("graphics_green"));
        graphics_green->setMaximumSize(QSize(16777215, 78));
        QBrush brush3(QColor(255, 205, 5, 255));
        brush3.setStyle(Qt::NoBrush);
        graphics_green->setBackgroundBrush(brush3);
        QBrush brush4(QColor(255, 205, 5, 255));
        brush4.setStyle(Qt::NoBrush);
        graphics_green->setForegroundBrush(brush4);

        horizontalLayout_6->addWidget(graphics_green);

        gridLayoutWidget_2 = new QWidget(frame_2);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(300, 10, 361, 101));
        gridLayout = new QGridLayout(gridLayoutWidget_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_8 = new QLabel(gridLayoutWidget_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_9->addWidget(label_8);

        lcd_date = new QLCDNumber(gridLayoutWidget_2);
        lcd_date->setObjectName(QString::fromUtf8("lcd_date"));
        lcd_date->setNumDigits(12);

        horizontalLayout_9->addWidget(lcd_date);


        horizontalLayout_8->addLayout(horizontalLayout_9);


        gridLayout->addLayout(horizontalLayout_8, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(gridLayoutWidget_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        lcd_system_2 = new QLCDNumber(gridLayoutWidget_2);
        lcd_system_2->setObjectName(QString::fromUtf8("lcd_system_2"));
        lcd_system_2->setNumDigits(12);

        horizontalLayout_7->addWidget(lcd_system_2);


        horizontalLayout_3->addLayout(horizontalLayout_7);


        gridLayout->addLayout(horizontalLayout_3, 0, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_9 = new QLabel(gridLayoutWidget_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_4->addWidget(label_9);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_state = new QLabel(gridLayoutWidget_2);
        label_state->setObjectName(QString::fromUtf8("label_state"));

        horizontalLayout_5->addWidget(label_state);


        horizontalLayout_4->addLayout(horizontalLayout_5);


        gridLayout->addLayout(horizontalLayout_4, 2, 0, 1, 1);

        verticalLayoutWidget_2 = new QWidget(frame_2);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(299, 210, 361, 181));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_2 = new QLabel(verticalLayoutWidget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_11->addWidget(label_2);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        lcd_up = new QLCDNumber(verticalLayoutWidget_2);
        lcd_up->setObjectName(QString::fromUtf8("lcd_up"));
        lcd_up->setNumDigits(12);

        horizontalLayout_12->addWidget(lcd_up);


        horizontalLayout_11->addLayout(horizontalLayout_12);


        horizontalLayout_10->addLayout(horizontalLayout_11);


        verticalLayout->addLayout(horizontalLayout_10);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label = new QLabel(verticalLayoutWidget_2);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_14->addWidget(label);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        lcd_order = new QLCDNumber(verticalLayoutWidget_2);
        lcd_order->setObjectName(QString::fromUtf8("lcd_order"));
        lcd_order->setNumDigits(12);

        horizontalLayout_15->addWidget(lcd_order);


        horizontalLayout_14->addLayout(horizontalLayout_15);


        horizontalLayout->addLayout(horizontalLayout_14);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        pushButton_start = new QPushButton(verticalLayoutWidget_2);
        pushButton_start->setObjectName(QString::fromUtf8("pushButton_start"));

        verticalLayout_2->addWidget(pushButton_start);

        pushButton_pause = new QPushButton(verticalLayoutWidget_2);
        pushButton_pause->setObjectName(QString::fromUtf8("pushButton_pause"));

        verticalLayout_2->addWidget(pushButton_pause);

        pushButton_stop = new QPushButton(verticalLayoutWidget_2);
        pushButton_stop->setObjectName(QString::fromUtf8("pushButton_stop"));

        verticalLayout_2->addWidget(pushButton_stop);


        horizontalLayout_13->addLayout(verticalLayout_2);


        verticalLayout->addLayout(horizontalLayout_13);

        verticalLayoutWidget = new QWidget(frame_2);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(20, 400, 321, 191));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        horizontalLayout_26 = new QHBoxLayout();
        horizontalLayout_26->setObjectName(QString::fromUtf8("horizontalLayout_26"));
        label_10 = new QLabel(verticalLayoutWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_26->addWidget(label_10);


        horizontalLayout_16->addLayout(horizontalLayout_26);


        horizontalLayout_2->addLayout(horizontalLayout_16);

        horizontalLayout_27 = new QHBoxLayout();
        horizontalLayout_27->setObjectName(QString::fromUtf8("horizontalLayout_27"));
        label_order1 = new QLabel(verticalLayoutWidget);
        label_order1->setObjectName(QString::fromUtf8("label_order1"));

        horizontalLayout_27->addWidget(label_order1);


        horizontalLayout_2->addLayout(horizontalLayout_27);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        horizontalLayout_28 = new QHBoxLayout();
        horizontalLayout_28->setObjectName(QString::fromUtf8("horizontalLayout_28"));
        label_12 = new QLabel(verticalLayoutWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout_28->addWidget(label_12);


        horizontalLayout_17->addLayout(horizontalLayout_28);

        horizontalLayout_29 = new QHBoxLayout();
        horizontalLayout_29->setObjectName(QString::fromUtf8("horizontalLayout_29"));
        lcd_time1 = new QLCDNumber(verticalLayoutWidget);
        lcd_time1->setObjectName(QString::fromUtf8("lcd_time1"));

        horizontalLayout_29->addWidget(lcd_time1);


        horizontalLayout_17->addLayout(horizontalLayout_29);


        verticalLayout_3->addLayout(horizontalLayout_17);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        horizontalLayout_30 = new QHBoxLayout();
        horizontalLayout_30->setObjectName(QString::fromUtf8("horizontalLayout_30"));
        label_13 = new QLabel(verticalLayoutWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout_30->addWidget(label_13);


        horizontalLayout_18->addLayout(horizontalLayout_30);

        horizontalLayout_32 = new QHBoxLayout();
        horizontalLayout_32->setObjectName(QString::fromUtf8("horizontalLayout_32"));
        lcd_red1 = new QLCDNumber(verticalLayoutWidget);
        lcd_red1->setObjectName(QString::fromUtf8("lcd_red1"));

        horizontalLayout_32->addWidget(lcd_red1);


        horizontalLayout_18->addLayout(horizontalLayout_32);


        verticalLayout_3->addLayout(horizontalLayout_18);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        horizontalLayout_33 = new QHBoxLayout();
        horizontalLayout_33->setObjectName(QString::fromUtf8("horizontalLayout_33"));
        label_14 = new QLabel(verticalLayoutWidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        horizontalLayout_33->addWidget(label_14);


        horizontalLayout_19->addLayout(horizontalLayout_33);

        horizontalLayout_34 = new QHBoxLayout();
        horizontalLayout_34->setObjectName(QString::fromUtf8("horizontalLayout_34"));
        lcd_blue1 = new QLCDNumber(verticalLayoutWidget);
        lcd_blue1->setObjectName(QString::fromUtf8("lcd_blue1"));

        horizontalLayout_34->addWidget(lcd_blue1);


        horizontalLayout_19->addLayout(horizontalLayout_34);


        verticalLayout_3->addLayout(horizontalLayout_19);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        horizontalLayout_35 = new QHBoxLayout();
        horizontalLayout_35->setObjectName(QString::fromUtf8("horizontalLayout_35"));
        label_15 = new QLabel(verticalLayoutWidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        horizontalLayout_35->addWidget(label_15);


        horizontalLayout_20->addLayout(horizontalLayout_35);

        horizontalLayout_36 = new QHBoxLayout();
        horizontalLayout_36->setObjectName(QString::fromUtf8("horizontalLayout_36"));
        lcd_yellow1 = new QLCDNumber(verticalLayoutWidget);
        lcd_yellow1->setObjectName(QString::fromUtf8("lcd_yellow1"));

        horizontalLayout_36->addWidget(lcd_yellow1);


        horizontalLayout_20->addLayout(horizontalLayout_36);


        verticalLayout_3->addLayout(horizontalLayout_20);

        verticalLayoutWidget_3 = new QWidget(frame_2);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(349, 399, 311, 191));
        verticalLayout_4 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
        horizontalLayout_37 = new QHBoxLayout();
        horizontalLayout_37->setObjectName(QString::fromUtf8("horizontalLayout_37"));
        label_11 = new QLabel(verticalLayoutWidget_3);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_37->addWidget(label_11);


        horizontalLayout_21->addLayout(horizontalLayout_37);

        horizontalLayout_38 = new QHBoxLayout();
        horizontalLayout_38->setObjectName(QString::fromUtf8("horizontalLayout_38"));
        label_order2 = new QLabel(verticalLayoutWidget_3);
        label_order2->setObjectName(QString::fromUtf8("label_order2"));

        horizontalLayout_38->addWidget(label_order2);


        horizontalLayout_21->addLayout(horizontalLayout_38);


        verticalLayout_4->addLayout(horizontalLayout_21);

        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setObjectName(QString::fromUtf8("horizontalLayout_22"));
        horizontalLayout_39 = new QHBoxLayout();
        horizontalLayout_39->setObjectName(QString::fromUtf8("horizontalLayout_39"));
        label_16 = new QLabel(verticalLayoutWidget_3);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        horizontalLayout_39->addWidget(label_16);


        horizontalLayout_22->addLayout(horizontalLayout_39);

        horizontalLayout_40 = new QHBoxLayout();
        horizontalLayout_40->setObjectName(QString::fromUtf8("horizontalLayout_40"));
        lcd_time2 = new QLCDNumber(verticalLayoutWidget_3);
        lcd_time2->setObjectName(QString::fromUtf8("lcd_time2"));

        horizontalLayout_40->addWidget(lcd_time2);


        horizontalLayout_22->addLayout(horizontalLayout_40);


        verticalLayout_4->addLayout(horizontalLayout_22);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setObjectName(QString::fromUtf8("horizontalLayout_23"));
        horizontalLayout_41 = new QHBoxLayout();
        horizontalLayout_41->setObjectName(QString::fromUtf8("horizontalLayout_41"));
        label_17 = new QLabel(verticalLayoutWidget_3);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        horizontalLayout_41->addWidget(label_17);


        horizontalLayout_23->addLayout(horizontalLayout_41);

        horizontalLayout_42 = new QHBoxLayout();
        horizontalLayout_42->setObjectName(QString::fromUtf8("horizontalLayout_42"));
        lcd_red2 = new QLCDNumber(verticalLayoutWidget_3);
        lcd_red2->setObjectName(QString::fromUtf8("lcd_red2"));

        horizontalLayout_42->addWidget(lcd_red2);


        horizontalLayout_23->addLayout(horizontalLayout_42);


        verticalLayout_4->addLayout(horizontalLayout_23);

        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setObjectName(QString::fromUtf8("horizontalLayout_24"));
        horizontalLayout_43 = new QHBoxLayout();
        horizontalLayout_43->setObjectName(QString::fromUtf8("horizontalLayout_43"));
        label_18 = new QLabel(verticalLayoutWidget_3);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        horizontalLayout_43->addWidget(label_18);


        horizontalLayout_24->addLayout(horizontalLayout_43);

        horizontalLayout_44 = new QHBoxLayout();
        horizontalLayout_44->setObjectName(QString::fromUtf8("horizontalLayout_44"));
        lcd_blue2 = new QLCDNumber(verticalLayoutWidget_3);
        lcd_blue2->setObjectName(QString::fromUtf8("lcd_blue2"));

        horizontalLayout_44->addWidget(lcd_blue2);


        horizontalLayout_24->addLayout(horizontalLayout_44);


        verticalLayout_4->addLayout(horizontalLayout_24);

        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setObjectName(QString::fromUtf8("horizontalLayout_25"));
        horizontalLayout_45 = new QHBoxLayout();
        horizontalLayout_45->setObjectName(QString::fromUtf8("horizontalLayout_45"));
        label_19 = new QLabel(verticalLayoutWidget_3);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        horizontalLayout_45->addWidget(label_19);


        horizontalLayout_25->addLayout(horizontalLayout_45);

        horizontalLayout_46 = new QHBoxLayout();
        horizontalLayout_46->setObjectName(QString::fromUtf8("horizontalLayout_46"));
        lcd_yellow2 = new QLCDNumber(verticalLayoutWidget_3);
        lcd_yellow2->setObjectName(QString::fromUtf8("lcd_yellow2"));

        horizontalLayout_46->addWidget(lcd_yellow2);


        horizontalLayout_25->addLayout(horizontalLayout_46);


        verticalLayout_4->addLayout(horizontalLayout_25);


        hboxLayout->addWidget(frame_2);

        MainWindowDesign->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindowDesign);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 691, 25));
        menu_File = new QMenu(menubar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        MainWindowDesign->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindowDesign);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindowDesign->setStatusBar(statusbar);
        QWidget::setTabOrder(pushButton_pause, pushButton_stop);

        menubar->addAction(menu_File->menuAction());
        menu_File->addAction(action_Preferences);
        menu_File->addSeparator();
        menu_File->addAction(actionAbout);
        menu_File->addAction(actionAbout_Qt);
        menu_File->addSeparator();
        menu_File->addAction(action_Quit);

        retranslateUi(MainWindowDesign);

        QMetaObject::connectSlotsByName(MainWindowDesign);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowDesign)
    {
        MainWindowDesign->setWindowTitle(QApplication::translate("MainWindowDesign", "QRosApp", 0, QApplication::UnicodeUTF8));
        action_Quit->setText(QApplication::translate("MainWindowDesign", "&Quit", 0, QApplication::UnicodeUTF8));
        action_Quit->setShortcut(QApplication::translate("MainWindowDesign", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        action_Preferences->setText(QApplication::translate("MainWindowDesign", "&Preferences", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("MainWindowDesign", "&About", 0, QApplication::UnicodeUTF8));
        actionAbout_Qt->setText(QApplication::translate("MainWindowDesign", "About &Qt", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindowDesign", "<html><head/><body><p align=\"center\"><span style=\" font-size:24pt; font-weight:600;\">OEE:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindowDesign", "<html><head/><body><p align=\"center\"><span style=\" font-size:24pt; font-weight:600;\">A:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindowDesign", "<html><head/><body><p align=\"center\"><span style=\" font-size:24pt; font-weight:600;\">P:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindowDesign", "<html><head/><body><p align=\"center\"><span style=\" font-size:24pt; font-weight:600;\">Q:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindowDesign", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">Date:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindowDesign", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">System time: </span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindowDesign", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">State:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_state->setText(QApplication::translate("MainWindowDesign", "<html><head/><body><p align=\"center\"><span style=\" font-size:24pt;\"><br/></span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindowDesign", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt; font-weight:600;\">Up time:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindowDesign", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt; font-weight:600;\">Order:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        pushButton_start->setText(QApplication::translate("MainWindowDesign", "START", 0, QApplication::UnicodeUTF8));
        pushButton_pause->setText(QApplication::translate("MainWindowDesign", "PAUSE/RESUME", 0, QApplication::UnicodeUTF8));
        pushButton_stop->setText(QApplication::translate("MainWindowDesign", "STOP", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainWindowDesign", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt; font-weight:600;\">ORDER 1:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_order1->setText(QString());
        label_12->setText(QApplication::translate("MainWindowDesign", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">Time left:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("MainWindowDesign", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">Red needed:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("MainWindowDesign", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">Blue needed: </span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("MainWindowDesign", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">Yellow needed:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("MainWindowDesign", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt; font-weight:600;\">ORDER 2:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_order2->setText(QString());
        label_16->setText(QApplication::translate("MainWindowDesign", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">Time left:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("MainWindowDesign", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">Red needed</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("MainWindowDesign", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">Blue needed</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("MainWindowDesign", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">Yellow needed</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        menu_File->setTitle(QApplication::translate("MainWindowDesign", "&App", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindowDesign: public Ui_MainWindowDesign {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_WINDOW_H
