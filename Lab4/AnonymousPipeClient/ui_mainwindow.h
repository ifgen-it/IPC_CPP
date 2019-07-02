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
    QTextEdit *textEditSend;
    QPushButton *pushButtonSend;
    QTextEdit *textEditReceive;
    QLabel *labelHR;
    QLabel *labelHW;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 338);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        textEditSend = new QTextEdit(centralWidget);
        textEditSend->setObjectName(QStringLiteral("textEditSend"));
        textEditSend->setGeometry(QRect(20, 190, 361, 51));
        pushButtonSend = new QPushButton(centralWidget);
        pushButtonSend->setObjectName(QStringLiteral("pushButtonSend"));
        pushButtonSend->setGeometry(QRect(20, 250, 361, 23));
        textEditReceive = new QTextEdit(centralWidget);
        textEditReceive->setObjectName(QStringLiteral("textEditReceive"));
        textEditReceive->setEnabled(true);
        textEditReceive->setGeometry(QRect(20, 40, 361, 141));
        textEditReceive->setReadOnly(true);
        labelHR = new QLabel(centralWidget);
        labelHR->setObjectName(QStringLiteral("labelHR"));
        labelHR->setGeometry(QRect(20, 10, 81, 16));
        labelHW = new QLabel(centralWidget);
        labelHW->setObjectName(QStringLiteral("labelHW"));
        labelHW->setGeometry(QRect(130, 10, 81, 16));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 21));
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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Anonymous Pipe Client", nullptr));
        pushButtonSend->setText(QApplication::translate("MainWindow", "Send", nullptr));
        labelHR->setText(QApplication::translate("MainWindow", "hR = 0", nullptr));
        labelHW->setText(QApplication::translate("MainWindow", "hW = 0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
