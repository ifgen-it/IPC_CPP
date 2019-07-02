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
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QPushButton *pushButtonSendCout;
    QLabel *label;
    QTextEdit *textEditCout;
    QGroupBox *groupBox_2;
    QLabel *labelMsgCopyData;
    QGroupBox *groupBox_3;
    QPushButton *pushButtonFMCreate;
    QPushButton *pushButtonFMClose;
    QPushButton *pushButtonLoadFileMapping;
    QTextEdit *textEditFileMapping;
    QLabel *labelFileMappingInfo;
    QPushButton *pushButtonSaveFileMapping;
    QGroupBox *groupBox_4;
    QTextEdit *textEditFMFile;
    QPushButton *pushButtonFMFCreate;
    QPushButton *pushButtonFMFClose;
    QPushButton *pushButtonFMFLoad;
    QPushButton *pushButtonFMFSave;
    QLabel *labelFileMappingFInfo;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(434, 617);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 411, 121));
        pushButtonSendCout = new QPushButton(groupBox);
        pushButtonSendCout->setObjectName(QStringLiteral("pushButtonSendCout"));
        pushButtonSendCout->setGeometry(QRect(20, 80, 371, 23));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 91, 16));
        textEditCout = new QTextEdit(groupBox);
        textEditCout->setObjectName(QStringLiteral("textEditCout"));
        textEditCout->setGeometry(QRect(120, 20, 271, 51));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 140, 411, 61));
        labelMsgCopyData = new QLabel(groupBox_2);
        labelMsgCopyData->setObjectName(QStringLiteral("labelMsgCopyData"));
        labelMsgCopyData->setGeometry(QRect(20, 30, 331, 16));
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 210, 411, 171));
        pushButtonFMCreate = new QPushButton(groupBox_3);
        pushButtonFMCreate->setObjectName(QStringLiteral("pushButtonFMCreate"));
        pushButtonFMCreate->setGeometry(QRect(20, 20, 75, 23));
        pushButtonFMClose = new QPushButton(groupBox_3);
        pushButtonFMClose->setObjectName(QStringLiteral("pushButtonFMClose"));
        pushButtonFMClose->setGeometry(QRect(20, 50, 75, 23));
        pushButtonLoadFileMapping = new QPushButton(groupBox_3);
        pushButtonLoadFileMapping->setObjectName(QStringLiteral("pushButtonLoadFileMapping"));
        pushButtonLoadFileMapping->setGeometry(QRect(20, 80, 75, 23));
        textEditFileMapping = new QTextEdit(groupBox_3);
        textEditFileMapping->setObjectName(QStringLiteral("textEditFileMapping"));
        textEditFileMapping->setGeometry(QRect(110, 20, 281, 111));
        labelFileMappingInfo = new QLabel(groupBox_3);
        labelFileMappingInfo->setObjectName(QStringLiteral("labelFileMappingInfo"));
        labelFileMappingInfo->setGeometry(QRect(20, 140, 371, 16));
        pushButtonSaveFileMapping = new QPushButton(groupBox_3);
        pushButtonSaveFileMapping->setObjectName(QStringLiteral("pushButtonSaveFileMapping"));
        pushButtonSaveFileMapping->setGeometry(QRect(20, 110, 75, 23));
        groupBox_4 = new QGroupBox(centralWidget);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 390, 411, 171));
        textEditFMFile = new QTextEdit(groupBox_4);
        textEditFMFile->setObjectName(QStringLiteral("textEditFMFile"));
        textEditFMFile->setGeometry(QRect(110, 20, 281, 91));
        pushButtonFMFCreate = new QPushButton(groupBox_4);
        pushButtonFMFCreate->setObjectName(QStringLiteral("pushButtonFMFCreate"));
        pushButtonFMFCreate->setGeometry(QRect(20, 20, 75, 23));
        pushButtonFMFClose = new QPushButton(groupBox_4);
        pushButtonFMFClose->setObjectName(QStringLiteral("pushButtonFMFClose"));
        pushButtonFMFClose->setGeometry(QRect(20, 50, 75, 23));
        pushButtonFMFLoad = new QPushButton(groupBox_4);
        pushButtonFMFLoad->setObjectName(QStringLiteral("pushButtonFMFLoad"));
        pushButtonFMFLoad->setGeometry(QRect(20, 80, 75, 23));
        pushButtonFMFSave = new QPushButton(groupBox_4);
        pushButtonFMFSave->setObjectName(QStringLiteral("pushButtonFMFSave"));
        pushButtonFMFSave->setGeometry(QRect(20, 110, 75, 23));
        labelFileMappingFInfo = new QLabel(groupBox_4);
        labelFileMappingFInfo->setObjectName(QStringLiteral("labelFileMappingFInfo"));
        labelFileMappingFInfo->setGeometry(QRect(20, 140, 371, 16));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 434, 21));
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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Child process", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "1.5 STDOUT", nullptr));
        pushButtonSendCout->setText(QApplication::translate("MainWindow", "Send Text to STDOUT", nullptr));
        label->setText(QApplication::translate("MainWindow", "Text for STDOUT:", nullptr));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "3 WM_COPYDATA", nullptr));
        labelMsgCopyData->setText(QApplication::translate("MainWindow", "Message from Parent", nullptr));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "4.1 File mapping", nullptr));
        pushButtonFMCreate->setText(QApplication::translate("MainWindow", "Create", nullptr));
        pushButtonFMClose->setText(QApplication::translate("MainWindow", "Close", nullptr));
        pushButtonLoadFileMapping->setText(QApplication::translate("MainWindow", "Load", nullptr));
        labelFileMappingInfo->setText(QApplication::translate("MainWindow", "INFO:", nullptr));
        pushButtonSaveFileMapping->setText(QApplication::translate("MainWindow", "Save", nullptr));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "4.2 File mapping with file", nullptr));
        pushButtonFMFCreate->setText(QApplication::translate("MainWindow", "Create", nullptr));
        pushButtonFMFClose->setText(QApplication::translate("MainWindow", "Close", nullptr));
        pushButtonFMFLoad->setText(QApplication::translate("MainWindow", "Load", nullptr));
        pushButtonFMFSave->setText(QApplication::translate("MainWindow", "Save", nullptr));
        labelFileMappingFInfo->setText(QApplication::translate("MainWindow", "INFO:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
