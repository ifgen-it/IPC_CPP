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
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pushButtonDisconnect;
    QLabel *label;
    QLabel *labelConnStatus;
    QLineEdit *lineEditMessage;
    QPushButton *pushButtonSend;
    QPushButton *pushButtonConnectServer;
    QTextEdit *textEditResponse;
    QLabel *label_2;
    QLineEdit *lineEditTimer;
    QLabel *label_3;
    QLabel *labelPeriod;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(321, 454);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButtonDisconnect = new QPushButton(centralWidget);
        pushButtonDisconnect->setObjectName(QStringLiteral("pushButtonDisconnect"));
        pushButtonDisconnect->setGeometry(QRect(20, 170, 281, 23));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 80, 111, 16));
        labelConnStatus = new QLabel(centralWidget);
        labelConnStatus->setObjectName(QStringLiteral("labelConnStatus"));
        labelConnStatus->setGeometry(QRect(30, 50, 131, 16));
        lineEditMessage = new QLineEdit(centralWidget);
        lineEditMessage->setObjectName(QStringLiteral("lineEditMessage"));
        lineEditMessage->setGeometry(QRect(150, 80, 151, 20));
        pushButtonSend = new QPushButton(centralWidget);
        pushButtonSend->setObjectName(QStringLiteral("pushButtonSend"));
        pushButtonSend->setGeometry(QRect(20, 140, 281, 23));
        pushButtonConnectServer = new QPushButton(centralWidget);
        pushButtonConnectServer->setObjectName(QStringLiteral("pushButtonConnectServer"));
        pushButtonConnectServer->setGeometry(QRect(20, 20, 281, 23));
        textEditResponse = new QTextEdit(centralWidget);
        textEditResponse->setObjectName(QStringLiteral("textEditResponse"));
        textEditResponse->setGeometry(QRect(20, 260, 281, 131));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 210, 121, 16));
        lineEditTimer = new QLineEdit(centralWidget);
        lineEditTimer->setObjectName(QStringLiteral("lineEditTimer"));
        lineEditTimer->setGeometry(QRect(150, 110, 151, 20));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 110, 111, 16));
        labelPeriod = new QLabel(centralWidget);
        labelPeriod->setObjectName(QStringLiteral("labelPeriod"));
        labelPeriod->setGeometry(QRect(30, 230, 121, 16));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 321, 21));
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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Socket Client", nullptr));
        pushButtonDisconnect->setText(QApplication::translate("MainWindow", "Stop and disconnect from the Server", nullptr));
        label->setText(QApplication::translate("MainWindow", "Message for Server:", nullptr));
        labelConnStatus->setText(QApplication::translate("MainWindow", "Status: DISCONNECTED", nullptr));
        pushButtonSend->setText(QApplication::translate("MainWindow", "Start", nullptr));
        pushButtonConnectServer->setText(QApplication::translate("MainWindow", "Connect to the Server", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Response from Server:", nullptr));
        lineEditTimer->setText(QApplication::translate("MainWindow", "1000", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Timer:", nullptr));
        labelPeriod->setText(QApplication::translate("MainWindow", "Period: 1000", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
