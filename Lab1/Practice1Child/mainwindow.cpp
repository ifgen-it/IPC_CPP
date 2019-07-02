#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "windows.h"

#include <QDebug>
#include <QMessageBox>
#include <iostream>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // MANUAL SETTINGS

    connect(this,SIGNAL(CopyData(QString)),ui->labelMsgCopyData, SLOT(setText(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonSendCout_clicked()
{
    // INFO FROM COMMAND LINE
    qDebug() << "onClicked";
    char** ppArgV = childArgV;
    for(int i = 0; i < childArgC; i++){
        qDebug() << "argc:" << 1 + i;
        qDebug() << "argv:" << *ppArgV;

        QString msgArgC = QString::number(i + 1);

        QString msgArgV(*ppArgV);
        qDebug() << "msgArgc:" << msgArgC;
        QString msgText = "argC: " + msgArgC + "\n" +
                "argV: " + msgArgV;
        QMessageBox::information(this, "Command line parameters", msgText);
        ppArgV++;

        // FIND PARANT'S FILE HANDLE
        if(i == 2){
            hFileFromParent = reinterpret_cast<HANDLE>(msgArgV.toInt());
            qDebug() << "hFile child:" << hFileFromParent;
        }
    }

    // WORK

    //QString textForSend = ui->lineEditCout->text();
    QString textForSend = ui->textEditCout->toPlainText();
    std::string strTextForSend = textForSend.toStdString();
    int sizeOfTextStr = (int)strTextForSend.length(); // + 1;  - one more gap in the end file with +1
    const char* chTextForSend = strTextForSend.c_str();

    int sizeOfTextCh = sizeof(chTextForSend);

    qDebug() << "Sizeof new string text:" << sizeOfTextStr;
    qDebug() << "Sizeof new char* text:" << sizeOfTextCh;

    qDebug() << "Text from lineEdit:" << textForSend;
    qDebug() << "char * Text from lineEdit:" << chTextForSend;
    qDebug() << "sending works";

    std::cout << "cout works after closed app\n";   // don't write in file through stdout
    printf("printf works after closed app too\n");  // don't write in file through stdout

    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD wereWritten;
    char text[] = "Привет";
    qDebug() << "sizeof text:" << sizeof(text);

 //   WriteFile(hout, text, sizeof(text), &wereWritten, 0);
    WriteFile(hout, chTextForSend, (DWORD)sizeOfTextStr, &wereWritten, 0);

    qDebug() << "How much were written:" << wereWritten;
    QString textMesBox(chTextForSend);
    QMessageBox* qmb = new QMessageBox(this);
    qmb->setText(textMesBox);
    qmb->setWindowTitle("COUT");
   // qmb->resize(800,400);
  //  qmb->setStyleSheet("QLabel{min-width:250 px; }");
    qmb->show();



    // AFTER CREATION THIS CHILD PROCESS IT INHERITED HANDLER FOR FILE
    // HANDLER FOR FILE IS THE THIRD PARAMETER IN COMMAND LINE

//    QMessageBox::information(0,"Handle for file", QString::number((int)hFileFromParent));

    DWORD written;
 //   WINBOOL writeRes = WriteFile(hFileFromParent,"hello Parent!!",sizeof("hello Parent!!"), &written,0);

 //   QMessageBox::information(0, "write file Res", QString::number((int)writeRes));

    CloseHandle(hFileFromParent);
}

bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    UINT MyMessage = RegisterWindowMessageA("MyMessage");
    UINT MyFileMappingMsg = RegisterWindowMessageA("FileMappingChangedParent");

    MSG* msg = static_cast<MSG*>(message);

    if(msg->message == MyMessage){
        WPARAM wp = msg->wParam;
        LPARAM lp = msg->lParam;
        QString msgText = "Wparam: " + QString::number((uint)wp) + "\n"+
                "Lparam: " + QString::number((long)lp);
        QMessageBox::information(0,"Child Info", msgText);
        *result = 0;
        return true;
    }
    else if(msg->message == MyFileMappingMsg){

        // LOAD DATA FROM FILE MAPPING
        if(fileMappingWorking){

            char* p = static_cast<char*>(pMap);
            ui->textEditFileMapping->setText(QString::fromUtf8(p));

            if(fileMappingOnlinePrint == 1){
                ui->labelFileMappingInfo->setText("INFO: User typing.");
            }
            else if(fileMappingOnlinePrint == 2){
                ui->labelFileMappingInfo->setText("INFO: User typing..");
            }
            else if(fileMappingOnlinePrint == 3){
                ui->labelFileMappingInfo->setText("INFO: User typing...");
            }
            fileMappingOnlinePrint++;
            if(fileMappingOnlinePrint == 4) fileMappingOnlinePrint = 1;
        }

        *result = 0;
        return true;
    }
    else if(msg->message == WM_COPYDATA){

        COPYDATASTRUCT* data = (COPYDATASTRUCT*)msg->lParam;
        QString msgText((char*)data->lpData);

        //ui->labelMsgCopyData->setText(msgText);   // it works!
        emit CopyData(msgText);

        *result = 0;
        return true;
    }
    else{
        //qDebug() << "Another message" << ++anotherMsgCounter;
        return false;
    }
}

void MainWindow::on_pushButtonFMCreate_clicked()
{
    // CREATE FILE MAPPING
    if(fileMappingWorking){
        QMessageBox::information(0, "Info", "File mapping already created by this process!");
        return;
    }
    hfilemap = CreateFileMappingA(
                INVALID_HANDLE_VALUE,       // hFile
                0,                          // lpFileMappingAttributes
                PAGE_READWRITE,             // flProtect
                0,                          // dwMaximumSizeHigh
                sizeFMapping,                       // dwMaximumSizeLow
                "MyFileMapping"             // lpName
                );
    if (hfilemap == 0){
        QMessageBox::critical(0, "Fail", "Cannot create filemapping!");
        return;
    }
    if(GetLastError() == ERROR_ALREADY_EXISTS){
        QMessageBox::information(0, "Alert", "Got filemapping from Virtual Memory!");
    }

    // CREATE MAP VIEW OF FILE
    pMap = MapViewOfFile(
                hfilemap,        // hFileMappingObject
                FILE_MAP_WRITE,  // dwDesiredAccess
                0,               // dwFileOffsetHigh
                0,               // dwFileOffserLow
                0                // dwNumberOfBytesToMap
                );
    if(pMap == NULL){
        DWORD err = GetLastError();
        QMessageBox::critical(0,"Fail", "Cannot create MapViewOfFile, error: " + QString::number((int)err));

        CloseHandle(hfilemap);
        return;
    }

    // WORKING WITH FILE MAPPING
    fileMappingWorking = true;
    ui->labelFileMappingInfo->setText("INFO: File mapping created");
}

void MainWindow::on_pushButtonFMClose_clicked()
{
    if(fileMappingWorking){

        // CLOSE HANDLES
        UnmapViewOfFile(pMap);
        CloseHandle(hfilemap);
        fileMappingWorking = false;
        ui->labelFileMappingInfo->setText("INFO: File mapping closed");
    }
    else{
        QMessageBox::information(0,"Info", "File mapping did not created!");
    }
}

void MainWindow::on_pushButtonLoadFileMapping_clicked()
{
    if(fileMappingWorking){

        char* p = static_cast<char*>(pMap);

        ui->textEditFileMapping->setText(QString::fromUtf8(p));

        ui->labelFileMappingInfo->setText("INFO: File mapping loaded");
    }
    else{
        QMessageBox::information(0,"Info", "File mapping did not created!");
    }
}

void MainWindow::on_pushButtonSaveFileMapping_clicked()
{
    if(fileMappingWorking){

        QString fmText = ui->textEditFileMapping->toPlainText();
        qDebug() << "fmText:" << fmText;

   //     const char* chFmText = fmText.toStdString().c_str();
        QByteArray bFmText = fmText.toUtf8();
        char* chFmText = bFmText.data();

        qDebug() << "chFmText:" << chFmText;

        char* p = static_cast<char*>(pMap);
        qDebug() << "p:" << QString(p);

        //strcpy(p,chFmText);

        memcpy(p,chFmText,bFmText.length()+1);

        ui->labelFileMappingInfo->setText("INFO: File mapping saved");
    }
    else{
        QMessageBox::information(0,"Info", "File mapping did not created!");
    }
}



void MainWindow::on_pushButtonFMFCreate_clicked()
{
    // CREATE FILE MUST PARENT PROCESS

    // CREATE FILEMAPPING

    hfilemapF = CreateFileMappingA(
                //hfileF,                      // hFile
                INVALID_HANDLE_VALUE,
                0,                          // lpFileMappingAttributes
                PAGE_READWRITE,             // flProtect
                0,                          // dwMaximumSizeHigh
                sizeFMappingF,               // dwMaximumSizeLow
                "MyFMFile"                   // lpName
                );
    if (hfilemapF == 0){
        QMessageBox::critical(0, "Fail", "Cannot create filemapping!");
        return;
    }
    if(GetLastError() == ERROR_ALREADY_EXISTS){
        QMessageBox::information(0, "Alert", "Got filemapping from Virtual Memory!");
    }

    // CREATE MAP VIEW OF FILE
    pMapF = MapViewOfFile(
                hfilemapF,        // hFileMappingObject
                FILE_MAP_WRITE,  // dwDesiredAccess
                0,               // dwFileOffsetHigh
                0,               // dwFileOffserLow
                0                // dwNumberOfBytesToMap
                );
    if(pMapF == NULL){
        DWORD err = GetLastError();
        QMessageBox::critical(0,"Fail", "Cannot create MapViewOfFile, error: " + QString::number((int)err));

        CloseHandle(hfilemapF);
        return;
    }

    // LOADING DATA FROM FILE
    char* p = static_cast<char*>(pMapF);
    ui->textEditFMFile->setText(QString::fromUtf8(p));

    // WORKING WITH FILE MAPPING
    fileMappingWorkingF = true;
    ui->labelFileMappingFInfo->setText("INFO: File opened");


}

void MainWindow::on_pushButtonFMFClose_clicked()
{
    if(fileMappingWorkingF){

        // CLOSE HANDLES
        UnmapViewOfFile(pMapF);
        CloseHandle(hfilemapF);

        fileMappingWorkingF = false;
        ui->labelFileMappingFInfo->setText("INFO: File closed");
    }
    else{
        QMessageBox::information(0,"Info", "File did not opened!");
    }
}

void MainWindow::on_pushButtonFMFSave_clicked()
{
    if(fileMappingWorkingF){

        QString fmText = ui->textEditFMFile->toPlainText();
        qDebug() << "fmText:" << fmText;

        QByteArray bFmText = fmText.toUtf8();
        char* chFmText = bFmText.data();

        qDebug() << "chFmText:" << chFmText;

        char* p = static_cast<char*>(pMapF);
        qDebug() << "p:" << QString(p);

        memcpy(p, chFmText,bFmText.length() + 1);

        ui->labelFileMappingFInfo->setText("INFO: File saved");
 //       WINBOOL res = FlushViewOfFile(pMapF, sizeFMappingF);
  //      qDebug() << "flushed:" << res;

    }
    else{
        QMessageBox::information(0,"Info", "File did not opened!");
    }
}

void MainWindow::on_pushButtonFMFLoad_clicked()
{
    if(fileMappingWorkingF){

        char* p = static_cast<char*>(pMapF);

        ui->textEditFMFile->setText(QString::fromUtf8(p));

        ui->labelFileMappingFInfo->setText("INFO: File loaded");
    }
    else{
        QMessageBox::information(0,"Info", "File did not opened!");
    }
}
