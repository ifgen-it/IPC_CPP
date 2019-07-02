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
    QPushButton *pushButtonConnectServer;
    QPushButton *pushButtonDisconnect;
    QLineEdit *lineEditMessage;
    QLabel *label;
    QLabel *label_2;
    QTextEdit *textEditResponse;
    QPushButton *pushButtonSend;
    QLabel *labelConnStatus;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(338, 388);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButtonConnectServer = new QPushButton(centralWidget);
        pushButtonConnectServer->setObjectName(QStringLiteral("pushButtonConnectServer"));
        pushButtonConnectServer->setGeometry(QRect(30, 20, 131, 23));
        pushButtonDisconnect = new QPushButton(centralWidget);
        pushButtonDisconnect->setObjectName(QStringLiteral("pushButtonDisconnect"));
        pushButtonDisconnect->setGeometry(QRect(180, 20, 131, 23));
        lineEditMessage = new QLineEdit(centralWidget);
        lineEditMessage->setObjectName(QStringLiteral("lineEditMessage"));
        lineEditMessage->setGeometry(QRect(160, 80, 151, 20));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 80, 111, 16));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(40, 140, 121, 16));
        textEditResponse = new QTextEdit(centralWidget);
        textEditResponse->setObjectName(QStringLiteral("textEditResponse"));
        textEditResponse->setGeometry(QRect(30, 170, 281, 141));
        pushButtonSend = new QPushButton(centralWidget);
        pushButtonSend->setObjectName(QStringLiteral("pushButtonSend"));
        pushButtonSend->setGeometry(QRect(190, 110, 121, 23));
        labelConnStatus = new QLabel(centralWidget);
        labelConnStatus->setObjectName(QStringLiteral("labelConnStatus"));
        labelConnStatus->setGeometry(QRect(40, 50, 131, 16));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 338, 21));
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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Named Pipe Client", nullptr));
        pushButtonConnectServer->setText(QApplication::translate("MainWindow", "Connect Server", nullptr));
        pushButtonDisconnect->setText(QApplication::translate("MainWindow", "Disconnect Server", nullptr));
        label->setText(QApplication::translate("MainWindow", "Message for Server:", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Response from Server:", nullptr));
        pushButtonSend->setText(QApplication::translate("MainWindow", "Send", nullptr));
        labelConnStatus->setText(QApplication::translate("MainWindow", "Status: DISCONNECTED", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
