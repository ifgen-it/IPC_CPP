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
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLineEdit *lineEditFirstTerm;
    QLineEdit *lineEditSecondTerm;
    QLabel *label;
    QLabel *labelCalculationResult;
    QPushButton *pushButtonAddition;
    QPushButton *pushButtonSubtraction;
    QPushButton *pushButtonMultiplication;
    QPushButton *pushButtonDivision;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(502, 300);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        lineEditFirstTerm = new QLineEdit(centralWidget);
        lineEditFirstTerm->setObjectName(QStringLiteral("lineEditFirstTerm"));
        lineEditFirstTerm->setGeometry(QRect(10, 70, 91, 20));
        lineEditSecondTerm = new QLineEdit(centralWidget);
        lineEditSecondTerm->setObjectName(QStringLiteral("lineEditSecondTerm"));
        lineEditSecondTerm->setGeometry(QRect(190, 70, 91, 20));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(300, 70, 21, 16));
        labelCalculationResult = new QLabel(centralWidget);
        labelCalculationResult->setObjectName(QStringLiteral("labelCalculationResult"));
        labelCalculationResult->setGeometry(QRect(330, 70, 131, 16));
        pushButtonAddition = new QPushButton(centralWidget);
        pushButtonAddition->setObjectName(QStringLiteral("pushButtonAddition"));
        pushButtonAddition->setGeometry(QRect(130, 70, 31, 23));
        pushButtonSubtraction = new QPushButton(centralWidget);
        pushButtonSubtraction->setObjectName(QStringLiteral("pushButtonSubtraction"));
        pushButtonSubtraction->setGeometry(QRect(130, 100, 31, 23));
        pushButtonMultiplication = new QPushButton(centralWidget);
        pushButtonMultiplication->setObjectName(QStringLiteral("pushButtonMultiplication"));
        pushButtonMultiplication->setGeometry(QRect(130, 130, 31, 23));
        pushButtonDivision = new QPushButton(centralWidget);
        pushButtonDivision->setObjectName(QStringLiteral("pushButtonDivision"));
        pushButtonDivision->setGeometry(QRect(130, 160, 31, 23));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 502, 21));
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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Calculator", nullptr));
        label->setText(QApplication::translate("MainWindow", "=", nullptr));
        labelCalculationResult->setText(QApplication::translate("MainWindow", "___", nullptr));
        pushButtonAddition->setText(QApplication::translate("MainWindow", "+", nullptr));
        pushButtonSubtraction->setText(QApplication::translate("MainWindow", "-", nullptr));
        pushButtonMultiplication->setText(QApplication::translate("MainWindow", "*", nullptr));
        pushButtonDivision->setText(QApplication::translate("MainWindow", "/", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
