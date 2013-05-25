/********************************************************************************
** Form generated from reading UI file 'main_window_old.ui'
**
** Created: Sat May 25 15:49:41 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_WINDOW_OLD_H
#define UI_MAIN_WINDOW_OLD_H

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
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton_start;
    QPushButton *pushButton_pause;
    QPushButton *pushButton_stop;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_4;
    QPushButton *pushButton_status;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QGraphicsView *graphics_red;
    QGraphicsView *graphics_yellow;
    QGraphicsView *graphics_green;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLCDNumber *lcd_order;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLCDNumber *lcd_run;
    QMenuBar *menubar;
    QMenu *menu_File;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindowDesign)
    {
        if (MainWindowDesign->objectName().isEmpty())
            MainWindowDesign->setObjectName(QString::fromUtf8("MainWindowDesign"));
        MainWindowDesign->resize(735, 416);
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
        gridLayoutWidget->setGeometry(QRect(20, 10, 271, 331));
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

        verticalLayoutWidget = new QWidget(frame_2);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(540, 220, 141, 101));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        pushButton_start = new QPushButton(verticalLayoutWidget);
        pushButton_start->setObjectName(QString::fromUtf8("pushButton_start"));

        verticalLayout_2->addWidget(pushButton_start);

        pushButton_pause = new QPushButton(verticalLayoutWidget);
        pushButton_pause->setObjectName(QString::fromUtf8("pushButton_pause"));

        verticalLayout_2->addWidget(pushButton_pause);

        pushButton_stop = new QPushButton(verticalLayoutWidget);
        pushButton_stop->setObjectName(QString::fromUtf8("pushButton_stop"));

        verticalLayout_2->addWidget(pushButton_stop);

        verticalLayoutWidget_2 = new QWidget(frame_2);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(350, 250, 131, 40));
        verticalLayout_4 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        pushButton_status = new QPushButton(verticalLayoutWidget_2);
        pushButton_status->setObjectName(QString::fromUtf8("pushButton_status"));

        verticalLayout_4->addWidget(pushButton_status);

        horizontalLayoutWidget = new QWidget(frame_2);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(300, 10, 401, 131));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        graphics_red = new QGraphicsView(horizontalLayoutWidget);
        graphics_red->setObjectName(QString::fromUtf8("graphics_red"));
        graphics_red->setAutoFillBackground(true);
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::NoBrush);
        graphics_red->setBackgroundBrush(brush);
        graphics_red->setInteractive(false);

        horizontalLayout->addWidget(graphics_red);

        graphics_yellow = new QGraphicsView(horizontalLayoutWidget);
        graphics_yellow->setObjectName(QString::fromUtf8("graphics_yellow"));
        graphics_yellow->setAutoFillBackground(true);
        QBrush brush1(QColor(0, 170, 0, 255));
        brush1.setStyle(Qt::NoBrush);
        graphics_yellow->setBackgroundBrush(brush1);
        QBrush brush2(QColor(0, 170, 0, 255));
        brush2.setStyle(Qt::NoBrush);
        graphics_yellow->setForegroundBrush(brush2);
        graphics_yellow->setInteractive(true);

        horizontalLayout->addWidget(graphics_yellow);

        graphics_green = new QGraphicsView(horizontalLayoutWidget);
        graphics_green->setObjectName(QString::fromUtf8("graphics_green"));
        QBrush brush3(QColor(255, 205, 5, 255));
        brush3.setStyle(Qt::NoBrush);
        graphics_green->setBackgroundBrush(brush3);
        QBrush brush4(QColor(255, 205, 5, 255));
        brush4.setStyle(Qt::NoBrush);
        graphics_green->setForegroundBrush(brush4);

        horizontalLayout->addWidget(graphics_green);

        horizontalLayoutWidget_2 = new QWidget(frame_2);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(300, 150, 191, 51));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(horizontalLayoutWidget_2);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        lcd_order = new QLCDNumber(horizontalLayoutWidget_2);
        lcd_order->setObjectName(QString::fromUtf8("lcd_order"));

        horizontalLayout_2->addWidget(lcd_order);

        horizontalLayoutWidget_3 = new QWidget(frame_2);
        horizontalLayoutWidget_3->setObjectName(QString::fromUtf8("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(500, 150, 201, 51));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(horizontalLayoutWidget_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        lcd_run = new QLCDNumber(horizontalLayoutWidget_3);
        lcd_run->setObjectName(QString::fromUtf8("lcd_run"));

        horizontalLayout_3->addWidget(lcd_run);


        hboxLayout->addWidget(frame_2);

        MainWindowDesign->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindowDesign);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 735, 25));
        menu_File = new QMenu(menubar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        MainWindowDesign->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindowDesign);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindowDesign->setStatusBar(statusbar);
        QWidget::setTabOrder(pushButton_pause, pushButton_stop);
        QWidget::setTabOrder(pushButton_stop, pushButton_status);

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
        pushButton_start->setText(QApplication::translate("MainWindowDesign", "START", 0, QApplication::UnicodeUTF8));
        pushButton_pause->setText(QApplication::translate("MainWindowDesign", "PAUSE", 0, QApplication::UnicodeUTF8));
        pushButton_stop->setText(QApplication::translate("MainWindowDesign", "STOP", 0, QApplication::UnicodeUTF8));
        pushButton_status->setText(QApplication::translate("MainWindowDesign", "STATUS CHECK", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindowDesign", "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt; font-weight:600;\">Order:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindowDesign", "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt; font-weight:600;\">Run time:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        menu_File->setTitle(QApplication::translate("MainWindowDesign", "&App", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindowDesign: public Ui_MainWindowDesign {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_WINDOW_OLD_H
