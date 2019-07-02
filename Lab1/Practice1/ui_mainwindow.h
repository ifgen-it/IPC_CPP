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
    QGroupBox *groupBox;
    QPushButton *pushButtonCalc;
    QPushButton *pushButtonExitProcess;
    QPushButton *pushButtonTerminateProcess;
    QGroupBox *groupBox_2;
    QPushButton *pushButtonRun3Processes;
    QGroupBox *groupBox_3;
    QPushButton *pushButtonSoliter;
    QGroupBox *groupBox_4;
    QPushButton *pushButtonRunChildProc;
    QGroupBox *groupBox_5;
    QPushButton *pushButtonSendMsg;
    QPushButton *pushButtonPostMsg;
    QLineEdit *lineEditWparam;
    QLineEdit *lineEditLparam;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButtonBrdCastPostMsg;
    QPushButton *pushButtonBrdCastSendMsg;
    QGroupBox *groupBox_6;
    QLineEdit *lineEditCopyData;
    QGroupBox *groupBox_7;
    QPushButton *pushButtonCreateFileMapping;
    QPushButton *pushButtonCloseFileMapping;
    QLabel *labelFileMappingInfo;
    QTextEdit *textEditFileMapping;
    QPushButton *pushButtonSaveFileMapping;
    QPushButton *pushButtonLoadFileMapping;
    QPushButton *pushButtonClearTextEdit;
    QGroupBox *groupBox_8;
    QPushButton *pushButtonFMOpenFile;
    QTextEdit *textEditFMFile;
    QPushButton *pushButtonFMSaveFile;
    QPushButton *pushButtonCloseFile;
    QLabel *labelFileMappingFInfo;
    QPushButton *pushButtonFMLoadFile;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(542, 689);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 321, 61));
        pushButtonCalc = new QPushButton(groupBox);
        pushButtonCalc->setObjectName(QStringLiteral("pushButtonCalc"));
        pushButtonCalc->setGeometry(QRect(10, 20, 61, 21));
        pushButtonCalc->setCursor(QCursor(Qt::PointingHandCursor));
        pushButtonExitProcess = new QPushButton(groupBox);
        pushButtonExitProcess->setObjectName(QStringLiteral("pushButtonExitProcess"));
        pushButtonExitProcess->setGeometry(QRect(80, 20, 91, 23));
        pushButtonTerminateProcess = new QPushButton(groupBox);
        pushButtonTerminateProcess->setObjectName(QStringLiteral("pushButtonTerminateProcess"));
        pushButtonTerminateProcess->setGeometry(QRect(180, 20, 121, 23));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(340, 10, 191, 61));
        pushButtonRun3Processes = new QPushButton(groupBox_2);
        pushButtonRun3Processes->setObjectName(QStringLiteral("pushButtonRun3Processes"));
        pushButtonRun3Processes->setGeometry(QRect(20, 20, 151, 23));
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(340, 80, 191, 61));
        pushButtonSoliter = new QPushButton(groupBox_3);
        pushButtonSoliter->setObjectName(QStringLiteral("pushButtonSoliter"));
        pushButtonSoliter->setGeometry(QRect(20, 20, 151, 23));
        groupBox_4 = new QGroupBox(centralWidget);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 80, 321, 61));
        pushButtonRunChildProc = new QPushButton(groupBox_4);
        pushButtonRunChildProc->setObjectName(QStringLiteral("pushButtonRunChildProc"));
        pushButtonRunChildProc->setGeometry(QRect(10, 20, 291, 23));
        groupBox_5 = new QGroupBox(centralWidget);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(10, 150, 521, 101));
        pushButtonSendMsg = new QPushButton(groupBox_5);
        pushButtonSendMsg->setObjectName(QStringLiteral("pushButtonSendMsg"));
        pushButtonSendMsg->setGeometry(QRect(160, 20, 141, 23));
        pushButtonPostMsg = new QPushButton(groupBox_5);
        pushButtonPostMsg->setObjectName(QStringLiteral("pushButtonPostMsg"));
        pushButtonPostMsg->setGeometry(QRect(160, 60, 141, 23));
        lineEditWparam = new QLineEdit(groupBox_5);
        lineEditWparam->setObjectName(QStringLiteral("lineEditWparam"));
        lineEditWparam->setGeometry(QRect(60, 20, 81, 20));
        lineEditWparam->setText(QStringLiteral(""));
        lineEditWparam->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditLparam = new QLineEdit(groupBox_5);
        lineEditLparam->setObjectName(QStringLiteral("lineEditLparam"));
        lineEditLparam->setGeometry(QRect(60, 60, 81, 20));
        lineEditLparam->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label = new QLabel(groupBox_5);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 60, 47, 13));
        label_2 = new QLabel(groupBox_5);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 20, 47, 13));
        pushButtonBrdCastPostMsg = new QPushButton(groupBox_5);
        pushButtonBrdCastPostMsg->setObjectName(QStringLiteral("pushButtonBrdCastPostMsg"));
        pushButtonBrdCastPostMsg->setGeometry(QRect(350, 60, 151, 23));
        pushButtonBrdCastSendMsg = new QPushButton(groupBox_5);
        pushButtonBrdCastSendMsg->setObjectName(QStringLiteral("pushButtonBrdCastSendMsg"));
        pushButtonBrdCastSendMsg->setGeometry(QRect(350, 20, 151, 23));
        groupBox_6 = new QGroupBox(centralWidget);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setGeometry(QRect(10, 260, 521, 71));
        lineEditCopyData = new QLineEdit(groupBox_6);
        lineEditCopyData->setObjectName(QStringLiteral("lineEditCopyData"));
        lineEditCopyData->setGeometry(QRect(10, 30, 491, 20));
        groupBox_7 = new QGroupBox(centralWidget);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        groupBox_7->setGeometry(QRect(10, 340, 521, 141));
        pushButtonCreateFileMapping = new QPushButton(groupBox_7);
        pushButtonCreateFileMapping->setObjectName(QStringLiteral("pushButtonCreateFileMapping"));
        pushButtonCreateFileMapping->setGeometry(QRect(20, 30, 61, 23));
        pushButtonCloseFileMapping = new QPushButton(groupBox_7);
        pushButtonCloseFileMapping->setObjectName(QStringLiteral("pushButtonCloseFileMapping"));
        pushButtonCloseFileMapping->setGeometry(QRect(20, 70, 61, 23));
        labelFileMappingInfo = new QLabel(groupBox_7);
        labelFileMappingInfo->setObjectName(QStringLiteral("labelFileMappingInfo"));
        labelFileMappingInfo->setGeometry(QRect(30, 110, 471, 16));
        textEditFileMapping = new QTextEdit(groupBox_7);
        textEditFileMapping->setObjectName(QStringLiteral("textEditFileMapping"));
        textEditFileMapping->setGeometry(QRect(230, 20, 271, 71));
        pushButtonSaveFileMapping = new QPushButton(groupBox_7);
        pushButtonSaveFileMapping->setObjectName(QStringLiteral("pushButtonSaveFileMapping"));
        pushButtonSaveFileMapping->setGeometry(QRect(90, 70, 61, 23));
        pushButtonLoadFileMapping = new QPushButton(groupBox_7);
        pushButtonLoadFileMapping->setObjectName(QStringLiteral("pushButtonLoadFileMapping"));
        pushButtonLoadFileMapping->setGeometry(QRect(90, 30, 61, 23));
        pushButtonClearTextEdit = new QPushButton(groupBox_7);
        pushButtonClearTextEdit->setObjectName(QStringLiteral("pushButtonClearTextEdit"));
        pushButtonClearTextEdit->setGeometry(QRect(160, 30, 61, 23));
        groupBox_8 = new QGroupBox(centralWidget);
        groupBox_8->setObjectName(QStringLiteral("groupBox_8"));
        groupBox_8->setGeometry(QRect(10, 490, 521, 141));
        pushButtonFMOpenFile = new QPushButton(groupBox_8);
        pushButtonFMOpenFile->setObjectName(QStringLiteral("pushButtonFMOpenFile"));
        pushButtonFMOpenFile->setGeometry(QRect(20, 30, 71, 23));
        textEditFMFile = new QTextEdit(groupBox_8);
        textEditFMFile->setObjectName(QStringLiteral("textEditFMFile"));
        textEditFMFile->setGeometry(QRect(193, 20, 311, 81));
        pushButtonFMSaveFile = new QPushButton(groupBox_8);
        pushButtonFMSaveFile->setObjectName(QStringLiteral("pushButtonFMSaveFile"));
        pushButtonFMSaveFile->setGeometry(QRect(100, 60, 71, 23));
        pushButtonCloseFile = new QPushButton(groupBox_8);
        pushButtonCloseFile->setObjectName(QStringLiteral("pushButtonCloseFile"));
        pushButtonCloseFile->setGeometry(QRect(20, 60, 71, 23));
        labelFileMappingFInfo = new QLabel(groupBox_8);
        labelFileMappingFInfo->setObjectName(QStringLiteral("labelFileMappingFInfo"));
        labelFileMappingFInfo->setGeometry(QRect(30, 110, 471, 16));
        pushButtonFMLoadFile = new QPushButton(groupBox_8);
        pushButtonFMLoadFile->setObjectName(QStringLiteral("pushButtonFMLoadFile"));
        pushButtonFMLoadFile->setGeometry(QRect(100, 30, 71, 23));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 542, 21));
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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Parent process", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "1.2 One process", nullptr));
        pushButtonCalc->setText(QApplication::translate("MainWindow", "Calc", nullptr));
        pushButtonExitProcess->setText(QApplication::translate("MainWindow", "Exit Process", nullptr));
        pushButtonTerminateProcess->setText(QApplication::translate("MainWindow", "Terminate Process", nullptr));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "1.2d Three processes", nullptr));
        pushButtonRun3Processes->setText(QApplication::translate("MainWindow", "Run 3 processes", nullptr));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "1.3 STARTUPINFO", nullptr));
        pushButtonSoliter->setText(QApplication::translate("MainWindow", "Run cmd", nullptr));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "1.4 Child process", nullptr));
        pushButtonRunChildProc->setText(QApplication::translate("MainWindow", "Run Child process", nullptr));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "2 User message", nullptr));
        pushButtonSendMsg->setText(QApplication::translate("MainWindow", "Send message", nullptr));
        pushButtonPostMsg->setText(QApplication::translate("MainWindow", "Post message", nullptr));
        lineEditLparam->setPlaceholderText(QString());
        label->setText(QApplication::translate("MainWindow", "LPARAM", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "WPARAM", nullptr));
        pushButtonBrdCastPostMsg->setText(QApplication::translate("MainWindow", "Broadcast Post message", nullptr));
        pushButtonBrdCastSendMsg->setText(QApplication::translate("MainWindow", "Broadcast Send message", nullptr));
        groupBox_6->setTitle(QApplication::translate("MainWindow", "3 WM_COPYDATA", nullptr));
        groupBox_7->setTitle(QApplication::translate("MainWindow", "4.1 File mapping", nullptr));
        pushButtonCreateFileMapping->setText(QApplication::translate("MainWindow", "Create", nullptr));
        pushButtonCloseFileMapping->setText(QApplication::translate("MainWindow", "Close", nullptr));
        labelFileMappingInfo->setText(QApplication::translate("MainWindow", "INFO:", nullptr));
        pushButtonSaveFileMapping->setText(QApplication::translate("MainWindow", "Save", nullptr));
        pushButtonLoadFileMapping->setText(QApplication::translate("MainWindow", "Load", nullptr));
        pushButtonClearTextEdit->setText(QApplication::translate("MainWindow", "Clear", nullptr));
        groupBox_8->setTitle(QApplication::translate("MainWindow", "4.2 File mapping with File", nullptr));
        pushButtonFMOpenFile->setText(QApplication::translate("MainWindow", "Open", nullptr));
        pushButtonFMSaveFile->setText(QApplication::translate("MainWindow", "Save", nullptr));
        pushButtonCloseFile->setText(QApplication::translate("MainWindow", "Close", nullptr));
        labelFileMappingFInfo->setText(QApplication::translate("MainWindow", "INFO:", nullptr));
        pushButtonFMLoadFile->setText(QApplication::translate("MainWindow", "Load", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
