/********************************************************************************
** Form generated from reading UI file 'main_window_RSD.ui'
**
** Created: Sun May 19 16:09:33 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_WINDOW_RSD_H
#define UI_MAIN_WINDOW_RSD_H

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

class Ui_ROSApp
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
    QLCDNumber *lcdNumber;
    QLCDNumber *lcdNumber_2;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLCDNumber *lcdNumber_4;
    QLCDNumber *lcdNumber_3;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton;
    QPushButton *pushButton_4;
    QPushButton *pushButton_2;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_4;
    QPushButton *pushButton_3;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QGraphicsView *graphicsView;
    QGraphicsView *graphicsView_3;
    QGraphicsView *graphicsView_2;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLCDNumber *lcdNumber_5;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLCDNumber *lcdNumber_6;
    QMenuBar *menubar;
    QMenu *menu_File;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ROSApp)
    {
        if (ROSApp->objectName().isEmpty())
            ROSApp->setObjectName(QString::fromUtf8("ROSApp"));
        ROSApp->resize(735, 416);
        ROSApp->setMouseTracking(false);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        ROSApp->setWindowIcon(icon);
        ROSApp->setLocale(QLocale(QLocale::English, QLocale::Australia));
        action_Quit = new QAction(ROSApp);
        action_Quit->setObjectName(QString::fromUtf8("action_Quit"));
        action_Quit->setShortcutContext(Qt::ApplicationShortcut);
        action_Preferences = new QAction(ROSApp);
        action_Preferences->setObjectName(QString::fromUtf8("action_Preferences"));
        actionAbout = new QAction(ROSApp);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionAbout_Qt = new QAction(ROSApp);
        actionAbout_Qt->setObjectName(QString::fromUtf8("actionAbout_Qt"));
        centralwidget = new QWidget(ROSApp);
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
        lcdNumber = new QLCDNumber(gridLayoutWidget);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));

        gridLayout_2->addWidget(lcdNumber, 0, 2, 1, 1);

        lcdNumber_2 = new QLCDNumber(gridLayoutWidget);
        lcdNumber_2->setObjectName(QString::fromUtf8("lcdNumber_2"));

        gridLayout_2->addWidget(lcdNumber_2, 1, 2, 1, 1);

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

        lcdNumber_4 = new QLCDNumber(gridLayoutWidget);
        lcdNumber_4->setObjectName(QString::fromUtf8("lcdNumber_4"));

        gridLayout_2->addWidget(lcdNumber_4, 3, 2, 1, 1);

        lcdNumber_3 = new QLCDNumber(gridLayoutWidget);
        lcdNumber_3->setObjectName(QString::fromUtf8("lcdNumber_3"));

        gridLayout_2->addWidget(lcdNumber_3, 2, 2, 1, 1);

        verticalLayoutWidget = new QWidget(frame_2);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(540, 220, 141, 101));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(verticalLayoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout_2->addWidget(pushButton);

        pushButton_4 = new QPushButton(verticalLayoutWidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        verticalLayout_2->addWidget(pushButton_4);

        pushButton_2 = new QPushButton(verticalLayoutWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        verticalLayout_2->addWidget(pushButton_2);

        verticalLayoutWidget_2 = new QWidget(frame_2);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(350, 250, 131, 40));
        verticalLayout_4 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        pushButton_3 = new QPushButton(verticalLayoutWidget_2);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        verticalLayout_4->addWidget(pushButton_3);

        horizontalLayoutWidget = new QWidget(frame_2);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(300, 10, 401, 131));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        graphicsView = new QGraphicsView(horizontalLayoutWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setAutoFillBackground(true);
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::NoBrush);
        graphicsView->setBackgroundBrush(brush);
        graphicsView->setInteractive(false);

        horizontalLayout->addWidget(graphicsView);

        graphicsView_3 = new QGraphicsView(horizontalLayoutWidget);
        graphicsView_3->setObjectName(QString::fromUtf8("graphicsView_3"));
        graphicsView_3->setAutoFillBackground(true);
        QBrush brush1(QColor(0, 170, 0, 255));
        brush1.setStyle(Qt::NoBrush);
        graphicsView_3->setBackgroundBrush(brush1);
        QBrush brush2(QColor(0, 170, 0, 255));
        brush2.setStyle(Qt::NoBrush);
        graphicsView_3->setForegroundBrush(brush2);
        graphicsView_3->setInteractive(true);

        horizontalLayout->addWidget(graphicsView_3);

        graphicsView_2 = new QGraphicsView(horizontalLayoutWidget);
        graphicsView_2->setObjectName(QString::fromUtf8("graphicsView_2"));
        QBrush brush3(QColor(255, 205, 5, 255));
        brush3.setStyle(Qt::NoBrush);
        graphicsView_2->setBackgroundBrush(brush3);
        QBrush brush4(QColor(255, 205, 5, 255));
        brush4.setStyle(Qt::NoBrush);
        graphicsView_2->setForegroundBrush(brush4);

        horizontalLayout->addWidget(graphicsView_2);

        horizontalLayoutWidget_2 = new QWidget(frame_2);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(300, 150, 191, 51));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(horizontalLayoutWidget_2);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        lcdNumber_5 = new QLCDNumber(horizontalLayoutWidget_2);
        lcdNumber_5->setObjectName(QString::fromUtf8("lcdNumber_5"));

        horizontalLayout_2->addWidget(lcdNumber_5);

        horizontalLayoutWidget_3 = new QWidget(frame_2);
        horizontalLayoutWidget_3->setObjectName(QString::fromUtf8("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(500, 150, 201, 51));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(horizontalLayoutWidget_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        lcdNumber_6 = new QLCDNumber(horizontalLayoutWidget_3);
        lcdNumber_6->setObjectName(QString::fromUtf8("lcdNumber_6"));

        horizontalLayout_3->addWidget(lcdNumber_6);


        hboxLayout->addWidget(frame_2);

        ROSApp->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ROSApp);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 735, 25));
        menu_File = new QMenu(menubar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        ROSApp->setMenuBar(menubar);
        statusbar = new QStatusBar(ROSApp);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ROSApp->setStatusBar(statusbar);
        QWidget::setTabOrder(pushButton, pushButton_4);
        QWidget::setTabOrder(pushButton_4, pushButton_2);
        QWidget::setTabOrder(pushButton_2, pushButton_3);

        menubar->addAction(menu_File->menuAction());
        menu_File->addAction(action_Preferences);
        menu_File->addSeparator();
        menu_File->addAction(actionAbout);
        menu_File->addAction(actionAbout_Qt);
        menu_File->addSeparator();
        menu_File->addAction(action_Quit);

        retranslateUi(ROSApp);
        QObject::connect(action_Quit, SIGNAL(triggered()), ROSApp, SLOT(close()));

        QMetaObject::connectSlotsByName(ROSApp);
    } // setupUi

    void retranslateUi(QMainWindow *ROSApp)
    {
        ROSApp->setWindowTitle(QApplication::translate("ROSApp", "QRosApp", 0, QApplication::UnicodeUTF8));
        action_Quit->setText(QApplication::translate("ROSApp", "&Quit", 0, QApplication::UnicodeUTF8));
        action_Quit->setShortcut(QApplication::translate("ROSApp", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        action_Preferences->setText(QApplication::translate("ROSApp", "&Preferences", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("ROSApp", "&About", 0, QApplication::UnicodeUTF8));
        actionAbout_Qt->setText(QApplication::translate("ROSApp", "About &Qt", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("ROSApp", "<html><head/><body><p align=\"center\"><span style=\" font-size:24pt; font-weight:600;\">OEE:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("ROSApp", "<html><head/><body><p align=\"center\"><span style=\" font-size:24pt; font-weight:600;\">A:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("ROSApp", "<html><head/><body><p align=\"center\"><span style=\" font-size:24pt; font-weight:600;\">P:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("ROSApp", "<html><head/><body><p align=\"center\"><span style=\" font-size:24pt; font-weight:600;\">Q:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("ROSApp", "START", 0, QApplication::UnicodeUTF8));
        pushButton_4->setText(QApplication::translate("ROSApp", "PAUSE", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("ROSApp", "STOP", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("ROSApp", "STATUS CHECK", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ROSApp", "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt; font-weight:600;\">Order:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ROSApp", "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt; font-weight:600;\">Run time:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        menu_File->setTitle(QApplication::translate("ROSApp", "&App", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ROSApp: public Ui_ROSApp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_WINDOW_RSD_H
