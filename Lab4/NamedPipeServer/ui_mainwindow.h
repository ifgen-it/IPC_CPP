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
    QTextEdit *textEditRequest;
    QPushButton *pushButtonStartServer;
    QPushButton *pushButtonStopServer;
    QTextEdit *textEditResponse;
    QLabel *label;
    QLabel *label_2;
    QLabel *labelServerStatus;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(410, 350);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        textEditRequest = new QTextEdit(centralWidget);
        textEditRequest->setObjectName(QStringLiteral("textEditRequest"));
        textEditRequest->setGeometry(QRect(20, 120, 181, 161));
        pushButtonStartServer = new QPushButton(centralWidget);
        pushButtonStartServer->setObjectName(QStringLiteral("pushButtonStartServer"));
        pushButtonStartServer->setGeometry(QRect(20, 20, 181, 23));
        pushButtonStopServer = new QPushButton(centralWidget);
        pushButtonStopServer->setObjectName(QStringLiteral("pushButtonStopServer"));
        pushButtonStopServer->setGeometry(QRect(210, 20, 181, 23));
        textEditResponse = new QTextEdit(centralWidget);
        textEditResponse->setObjectName(QStringLiteral("textEditResponse"));
        textEditResponse->setGeometry(QRect(210, 120, 181, 161));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 90, 61, 16));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(220, 90, 61, 16));
        labelServerStatus = new QLabel(centralWidget);
        labelServerStatus->setObjectName(QStringLiteral("labelServerStatus"));
        labelServerStatus->setGeometry(QRect(30, 60, 111, 16));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 410, 21));
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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Named Pipe Server", nullptr));
        pushButtonStartServer->setText(QApplication::translate("MainWindow", "Start Server", nullptr));
        pushButtonStopServer->setText(QApplication::translate("MainWindow", "Stop Server", nullptr));
        label->setText(QApplication::translate("MainWindow", "Request:", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Response:", nullptr));
        labelServerStatus->setText(QApplication::translate("MainWindow", "Status: STOPPED", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
