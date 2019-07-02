/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "mydemowidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBoxControl;
    QPushButton *pushButtonThreadsGo;
    QPushButton *pushButtonCriticalSection;
    QPushButton *pushButtonMutex;
    QPushButton *pushButtonSemaphore;
    QPushButton *pushButtonSystemSemaphore;
    QPushButton *pushButtonClear;
    QPushButton *pushButtonSystemMutex;
    QPushButton *pushButtonAutoEvent;
    QPushButton *pushButtonManualEvent;
    QPushButton *pushButtonManualEventGo;
    QPushButton *pushButtonManualEventReset;
    QPushButton *pushButtonSystemManualEvent;
    QGroupBox *groupBoxField;
    MyDemoWidget *widgetField;
    QGroupBox *groupBoxRedPriority;
    QRadioButton *radioButtonRedHigh;
    QRadioButton *radioButtonRedNormal;
    QRadioButton *radioButtonRedLow;
    QGroupBox *groupBoxGreenPriority;
    QRadioButton *radioButtonGreenHigh;
    QRadioButton *radioButtonGreenNormal;
    QRadioButton *radioButtonGreenLow;
    QGroupBox *groupBoxBluePriority;
    QRadioButton *radioButtonBlueHigh;
    QRadioButton *radioButtonBlueNormal;
    QRadioButton *radioButtonBlueLow;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(855, 476);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBoxControl = new QGroupBox(centralWidget);
        groupBoxControl->setObjectName(QStringLiteral("groupBoxControl"));
        groupBoxControl->setGeometry(QRect(10, 10, 181, 401));
        pushButtonThreadsGo = new QPushButton(groupBoxControl);
        pushButtonThreadsGo->setObjectName(QStringLiteral("pushButtonThreadsGo"));
        pushButtonThreadsGo->setGeometry(QRect(20, 30, 141, 23));
        pushButtonCriticalSection = new QPushButton(groupBoxControl);
        pushButtonCriticalSection->setObjectName(QStringLiteral("pushButtonCriticalSection"));
        pushButtonCriticalSection->setGeometry(QRect(20, 60, 141, 23));
        pushButtonMutex = new QPushButton(groupBoxControl);
        pushButtonMutex->setObjectName(QStringLiteral("pushButtonMutex"));
        pushButtonMutex->setGeometry(QRect(20, 100, 141, 23));
        pushButtonSemaphore = new QPushButton(groupBoxControl);
        pushButtonSemaphore->setObjectName(QStringLiteral("pushButtonSemaphore"));
        pushButtonSemaphore->setGeometry(QRect(20, 170, 141, 23));
        pushButtonSystemSemaphore = new QPushButton(groupBoxControl);
        pushButtonSystemSemaphore->setObjectName(QStringLiteral("pushButtonSystemSemaphore"));
        pushButtonSystemSemaphore->setGeometry(QRect(20, 200, 141, 23));
        pushButtonClear = new QPushButton(groupBoxControl);
        pushButtonClear->setObjectName(QStringLiteral("pushButtonClear"));
        pushButtonClear->setGeometry(QRect(20, 360, 141, 23));
        pushButtonSystemMutex = new QPushButton(groupBoxControl);
        pushButtonSystemMutex->setObjectName(QStringLiteral("pushButtonSystemMutex"));
        pushButtonSystemMutex->setGeometry(QRect(20, 130, 141, 23));
        pushButtonAutoEvent = new QPushButton(groupBoxControl);
        pushButtonAutoEvent->setObjectName(QStringLiteral("pushButtonAutoEvent"));
        pushButtonAutoEvent->setGeometry(QRect(20, 240, 141, 23));
        pushButtonManualEvent = new QPushButton(groupBoxControl);
        pushButtonManualEvent->setObjectName(QStringLiteral("pushButtonManualEvent"));
        pushButtonManualEvent->setGeometry(QRect(20, 270, 141, 23));
        pushButtonManualEventGo = new QPushButton(groupBoxControl);
        pushButtonManualEventGo->setObjectName(QStringLiteral("pushButtonManualEventGo"));
        pushButtonManualEventGo->setGeometry(QRect(20, 300, 71, 23));
        pushButtonManualEventReset = new QPushButton(groupBoxControl);
        pushButtonManualEventReset->setObjectName(QStringLiteral("pushButtonManualEventReset"));
        pushButtonManualEventReset->setGeometry(QRect(90, 300, 71, 23));
        pushButtonSystemManualEvent = new QPushButton(groupBoxControl);
        pushButtonSystemManualEvent->setObjectName(QStringLiteral("pushButtonSystemManualEvent"));
        pushButtonSystemManualEvent->setGeometry(QRect(20, 330, 141, 23));
        groupBoxField = new QGroupBox(centralWidget);
        groupBoxField->setObjectName(QStringLiteral("groupBoxField"));
        groupBoxField->setGeometry(QRect(210, 10, 631, 221));
        widgetField = new MyDemoWidget(groupBoxField);
        widgetField->setObjectName(QStringLiteral("widgetField"));
        widgetField->setGeometry(QRect(20, 30, 591, 171));
        groupBoxRedPriority = new QGroupBox(centralWidget);
        groupBoxRedPriority->setObjectName(QStringLiteral("groupBoxRedPriority"));
        groupBoxRedPriority->setGeometry(QRect(210, 250, 191, 131));
        radioButtonRedHigh = new QRadioButton(groupBoxRedPriority);
        radioButtonRedHigh->setObjectName(QStringLiteral("radioButtonRedHigh"));
        radioButtonRedHigh->setGeometry(QRect(20, 30, 91, 21));
        radioButtonRedNormal = new QRadioButton(groupBoxRedPriority);
        radioButtonRedNormal->setObjectName(QStringLiteral("radioButtonRedNormal"));
        radioButtonRedNormal->setGeometry(QRect(20, 60, 91, 21));
        radioButtonRedLow = new QRadioButton(groupBoxRedPriority);
        radioButtonRedLow->setObjectName(QStringLiteral("radioButtonRedLow"));
        radioButtonRedLow->setGeometry(QRect(20, 90, 91, 21));
        groupBoxGreenPriority = new QGroupBox(centralWidget);
        groupBoxGreenPriority->setObjectName(QStringLiteral("groupBoxGreenPriority"));
        groupBoxGreenPriority->setGeometry(QRect(430, 250, 191, 131));
        radioButtonGreenHigh = new QRadioButton(groupBoxGreenPriority);
        radioButtonGreenHigh->setObjectName(QStringLiteral("radioButtonGreenHigh"));
        radioButtonGreenHigh->setGeometry(QRect(20, 30, 91, 21));
        radioButtonGreenNormal = new QRadioButton(groupBoxGreenPriority);
        radioButtonGreenNormal->setObjectName(QStringLiteral("radioButtonGreenNormal"));
        radioButtonGreenNormal->setGeometry(QRect(20, 60, 91, 21));
        radioButtonGreenLow = new QRadioButton(groupBoxGreenPriority);
        radioButtonGreenLow->setObjectName(QStringLiteral("radioButtonGreenLow"));
        radioButtonGreenLow->setGeometry(QRect(20, 90, 91, 21));
        groupBoxBluePriority = new QGroupBox(centralWidget);
        groupBoxBluePriority->setObjectName(QStringLiteral("groupBoxBluePriority"));
        groupBoxBluePriority->setGeometry(QRect(650, 250, 191, 131));
        radioButtonBlueHigh = new QRadioButton(groupBoxBluePriority);
        radioButtonBlueHigh->setObjectName(QStringLiteral("radioButtonBlueHigh"));
        radioButtonBlueHigh->setGeometry(QRect(20, 30, 91, 21));
        radioButtonBlueNormal = new QRadioButton(groupBoxBluePriority);
        radioButtonBlueNormal->setObjectName(QStringLiteral("radioButtonBlueNormal"));
        radioButtonBlueNormal->setGeometry(QRect(20, 60, 91, 21));
        radioButtonBlueLow = new QRadioButton(groupBoxBluePriority);
        radioButtonBlueLow->setObjectName(QStringLiteral("radioButtonBlueLow"));
        radioButtonBlueLow->setGeometry(QRect(20, 90, 91, 21));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 855, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Threads", nullptr));
        groupBoxControl->setTitle(QApplication::translate("MainWindow", "Control", nullptr));
        pushButtonThreadsGo->setText(QApplication::translate("MainWindow", "Threads GO!", nullptr));
        pushButtonCriticalSection->setText(QApplication::translate("MainWindow", "Critical section", nullptr));
        pushButtonMutex->setText(QApplication::translate("MainWindow", "Mutex", nullptr));
        pushButtonSemaphore->setText(QApplication::translate("MainWindow", "Semaphore", nullptr));
        pushButtonSystemSemaphore->setText(QApplication::translate("MainWindow", "System semaphore", nullptr));
        pushButtonClear->setText(QApplication::translate("MainWindow", "Clear", nullptr));
        pushButtonSystemMutex->setText(QApplication::translate("MainWindow", "System mutex", nullptr));
        pushButtonAutoEvent->setText(QApplication::translate("MainWindow", "Auto event", nullptr));
        pushButtonManualEvent->setText(QApplication::translate("MainWindow", "Manual event", nullptr));
        pushButtonManualEventGo->setText(QApplication::translate("MainWindow", "S. ev. Go!", nullptr));
        pushButtonManualEventReset->setText(QApplication::translate("MainWindow", "S. ev. reset", nullptr));
        pushButtonSystemManualEvent->setText(QApplication::translate("MainWindow", "System manual event", nullptr));
        groupBoxField->setTitle(QApplication::translate("MainWindow", "Field", nullptr));
        groupBoxRedPriority->setTitle(QApplication::translate("MainWindow", "RED Priority", nullptr));
        radioButtonRedHigh->setText(QApplication::translate("MainWindow", "HIGHEST", nullptr));
        radioButtonRedNormal->setText(QApplication::translate("MainWindow", "NORMAL", nullptr));
        radioButtonRedLow->setText(QApplication::translate("MainWindow", "LOWEST", nullptr));
        groupBoxGreenPriority->setTitle(QApplication::translate("MainWindow", "GREEN Priority", nullptr));
        radioButtonGreenHigh->setText(QApplication::translate("MainWindow", "HIGHEST", nullptr));
        radioButtonGreenNormal->setText(QApplication::translate("MainWindow", "NORMAL", nullptr));
        radioButtonGreenLow->setText(QApplication::translate("MainWindow", "LOWEST", nullptr));
        groupBoxBluePriority->setTitle(QApplication::translate("MainWindow", "BLUE Priority", nullptr));
        radioButtonBlueHigh->setText(QApplication::translate("MainWindow", "HIGHEST", nullptr));
        radioButtonBlueNormal->setText(QApplication::translate("MainWindow", "NORMAL", nullptr));
        radioButtonBlueLow->setText(QApplication::translate("MainWindow", "LOWEST", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
