#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "windows.h"
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



}

MainWindow::~MainWindow()
{
    if(hR1 != 0) CloseHandle(hR1);
    if(hW1 != 0) CloseHandle(hW1);
    if(hR2 != 0) CloseHandle(hR2);
    if(hW2 != 0) CloseHandle(hW2);

    delete ui;
}

void MainWindow::on_pushButtonCreatePipes_clicked()
{
    // CREATE PIPE

    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof (sa);
    sa.lpSecurityDescriptor = 0;
    sa.bInheritHandle = TRUE;

    DWORD nSize = 512;

    WINBOOL resPipe1 = CreatePipe(&hR1, &hW1, &sa, nSize);
    qDebug() << "resPipe1 =" << resPipe1;
    qDebug() << "hRead1 =" << hR1;
    qDebug() << "hWrite1 =" << hW1;

    WINBOOL resPipe2 = CreatePipe(&hR2, &hW2, &sa, nSize);
    qDebug() << "resPipe2 =" << resPipe2;
    qDebug() << "hRead2 =" << hR2;
    qDebug() << "hWrite2 =" << hW2;

    hStrPipes = " " + QString::number((int)hR1) +
            + " "  + QString::number((int)hW1) +
            + " " + QString::number((int)hR2) +
            + " " + QString::number((int)hW2);
    qDebug() << "hStrPipes =" << hStrPipes;

    // UPDATE LABELS
    ui->labelHR1->setText("hR1 = " + QString::number((int)hR1));
    ui->labelHW1->setText("hW1 = " + QString::number((int)hW1));
    ui->labelHR2->setText("hR2 = " + QString::number((int)hR2));
    ui->labelHW2->setText("hW2 = " + QString::number((int)hW2));
}

void MainWindow::createClient(int clientNumber){

    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);

    PROCESS_INFORMATION pi;

    // MAKE APP STRING
    // wchar_t strApp[] = {L"..\\AnonymousPipeClient\\debug\\AnonymousPipeClient 1"};

    qDebug() << "hStrPipes from ClickMakeClient =" << hStrPipes;
    QString strApp("..\\AnonymousPipeClient\\debug\\AnonymousPipeClient "+ QString::number(clientNumber) + hStrPipes);
    qDebug() << "strApp : " << strApp;

    wchar_t app1[strApp.length() + 1];
    strApp.toWCharArray(app1);
    app1[strApp.length()] = 0;

    BOOL appRun = CreateProcess(0,  //lpApplicationName
                  app1,             //lpCommandLine
                  0,                //lpProcessAttributes
                  0,                //lpThreadAttributes
                  TRUE,            //bInheritHandles
                  0,                //dwCreationFlags
                  0,                //lpEnvironment
                  0,                //lpCurrentDirectory
                  &si,              //lpStartupInfo
                  &pi               //lpProcessInformation
                  );
    if(!appRun){
        MessageBoxA(0,"CreateProcess failed!", "Info", MB_OK);

        return;
    }

    // CLOSE THREAD HANDLE
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

}

void MainWindow::on_pushButtonCreateClient1_clicked()
{
   createClient(1);
}

void MainWindow::on_pushButtonCreateClient2_clicked()
{
   createClient(2);
}


