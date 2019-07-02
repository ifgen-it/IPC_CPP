#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "windows.h"
#include <QDebug>

#define PIPE_NAME L"\\\\.\\pipe\\MyNamedPipe"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButtonDisconnect->setDisabled(true);
    ui->pushButtonSend->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonConnectServer_clicked()
{

    //  CONNECT TO THE SERVER PIPE
    WINBOOL resWait = WaitNamedPipe(PIPE_NAME,NMPWAIT_WAIT_FOREVER);
    if(resWait == 0) {
        qDebug() << "WaitNamedPipe failed";
        return;
    }

    // CREATE THE NAMED PIPE FILE HANDLE
    hPipe = CreateFile(
                PIPE_NAME,
                GENERIC_READ | GENERIC_WRITE,
                0,
                0,
                OPEN_EXISTING,
                FILE_ATTRIBUTE_NORMAL,
                0 );

    qDebug() << "hPipe =" << hPipe;

    if(hPipe == INVALID_HANDLE_VALUE){
        qDebug() << "CreateFile failed";
        return;
    }

    connStatus = true;
    ui->labelConnStatus->setText("Status: CONNECTED");
    ui->pushButtonConnectServer->setEnabled(false);
    ui->pushButtonDisconnect->setEnabled(true);
    ui->pushButtonSend->setEnabled(true);

}


void MainWindow::on_pushButtonSend_clicked()
{
    if(!connStatus){
        qDebug() << "Connect to the Server";
        return;
    }

    // WRITE
    QString text = ui->lineEditMessage->text();
    QString request = text;

    if(disconnectPipe){
        request = "DisconnectMe";
    }
    qDebug() << "request:" << request;
    QByteArray bText = request.toUtf8();
    const char* chText = bText.data();
    int chTextLength = bText.length() + 1;

    DWORD bytesWritten;

    WINBOOL resWrite = WriteFile(hPipe, chText, chTextLength, &bytesWritten, 0);
    if (resWrite == 0){
        qDebug() << "WriteFile failed";
        CloseHandle(hPipe);
        return;
    }
    qDebug() << "Was written bytes :" << bytesWritten;

    // READ
    DWORD bytesRead;
    char buffer[512];

    WINBOOL resRead = ReadFile(hPipe, buffer, sizeof(buffer), &bytesRead, 0);
    if(resRead <= 0 ){
        qDebug() << "ReadFile failed";
        CloseHandle(hPipe);
        return;
    }
    buffer[bytesRead] = 0;
    QString strBuffer = QString::fromUtf8(buffer);
    qDebug() << "char buffer =" << buffer;
    qDebug() << "QString buffer =" << strBuffer;

    ui->textEditResponse->append(strBuffer);

}

void MainWindow::on_pushButtonDisconnect_clicked()
{
    disconnectPipe = true;
    on_pushButtonSend_clicked();
    CloseHandle(hPipe);

    ui->labelConnStatus->setText("Status: DISCONNECTED");
    connStatus = false;
    disconnectPipe = false;

    ui->pushButtonConnectServer->setEnabled(true);
    ui->pushButtonDisconnect->setEnabled(false);
    ui->pushButtonSend->setEnabled(false);
}
