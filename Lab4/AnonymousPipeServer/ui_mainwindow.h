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
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pushButtonCreatePipes;
    QGroupBox *groupBox;
    QPushButton *pushButtonCreateClient1;
    QLabel *labelHW1;
    QLabel *labelHR2;
    QGroupBox *groupBox_2;
    QPushButton *pushButtonCreateClient2;
    QLabel *labelHW2;
    QLabel *labelHR1;
    QLabel *label_6;
    QLabel *label_7;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(438, 248);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButtonCreatePipes = new QPushButton(centralWidget);
        pushButtonCreatePipes->setObjectName(QStringLiteral("pushButtonCreatePipes"));
        pushButtonCreatePipes->setGeometry(QRect(30, 20, 381, 23));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(30, 60, 121, 121));
        pushButtonCreateClient1 = new QPushButton(groupBox);
        pushButtonCreateClient1->setObjectName(QStringLiteral("pushButtonCreateClient1"));
        pushButtonCreateClient1->setGeometry(QRect(20, 20, 81, 23));
        labelHW1 = new QLabel(groupBox);
        labelHW1->setObjectName(QStringLiteral("labelHW1"));
        labelHW1->setGeometry(QRect(20, 60, 81, 16));
        labelHR2 = new QLabel(groupBox);
        labelHR2->setObjectName(QStringLiteral("labelHR2"));
        labelHR2->setGeometry(QRect(20, 90, 91, 16));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(300, 60, 111, 121));
        pushButtonCreateClient2 = new QPushButton(groupBox_2);
        pushButtonCreateClient2->setObjectName(QStringLiteral("pushButtonCreateClient2"));
        pushButtonCreateClient2->setGeometry(QRect(20, 20, 71, 23));
        labelHW2 = new QLabel(groupBox_2);
        labelHW2->setObjectName(QStringLiteral("labelHW2"));
        labelHW2->setGeometry(QRect(20, 90, 81, 16));
        labelHR1 = new QLabel(groupBox_2);
        labelHR1->setObjectName(QStringLiteral("labelHR1"));
        labelHR1->setGeometry(QRect(20, 60, 81, 16));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(160, 150, 141, 21));
        QFont font;
        font.setFamily(QStringLiteral("Candara"));
        font.setPointSize(14);
        font.setBold(true);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(75);
        font.setStrikeOut(false);
        font.setKerning(true);
        label_6->setFont(font);
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(160, 110, 141, 31));
        label_7->setFont(font);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 438, 21));
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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Anonymous Pipe Server", nullptr));
        pushButtonCreatePipes->setText(QApplication::translate("MainWindow", "Create 2 anonymous pipes (read, write) for 2 Clients", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "Client 1", nullptr));
        pushButtonCreateClient1->setText(QApplication::translate("MainWindow", "Create", nullptr));
        labelHW1->setText(QApplication::translate("MainWindow", "hW1 = 0", nullptr));
        labelHR2->setText(QApplication::translate("MainWindow", "hR2 = 0", nullptr));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Client 2", nullptr));
        pushButtonCreateClient2->setText(QApplication::translate("MainWindow", "Create", nullptr));
        labelHW2->setText(QApplication::translate("MainWindow", "hW2 = 0", nullptr));
        labelHR1->setText(QApplication::translate("MainWindow", "hR1 = 0", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "<<<   Pipe 2   <<<", nullptr));
        label_7->setText(QApplication::translate("MainWindow", ">>>   Pipe 1   >>>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
