#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "windows.h"
#include "winsock2.h"

#include "helpersocket.h"
#include <QDebug>


HANDLE MainWindow::hTimer = NULL;
HANDLE MainWindow::hThread = NULL;
bool MainWindow::connStatus = false;
bool MainWindow::disconnectSocket = false;
bool MainWindow::sending = false;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonConnectServer_clicked()
{

    if(connStatus == true)
        return;

    qDebug() << "ConnectServer started..";

    // CHECK DLL
    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD(2,2);
    int res = WSAStartup(wVersionRequested,&wsaData);
    if(res != 0){
        qDebug() << "Cannot find DLL or version 2.2 is not supported";
    }
    qDebug() << "DLL found!";

    // CREATE SOCKET
    sClient = socket(AF_INET, SOCK_STREAM,0);
    if(sClient == INVALID_SOCKET){
        qDebug() << "Cannot create Client socket";
        closesocket(sClient);
        WSACleanup();
        return;
    }
    qDebug() << "Client socket created";

    // ADDRESS
    sockaddr_in serverAddr;
    ZeroMemory(&serverAddr, sizeof(sockaddr_in));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(15666);

    // CONNECT TO THE SERVER
    int resConn = ::connect(sClient, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr));

    if(resConn == SOCKET_ERROR){
        qDebug() << "Error connect to the Server";
        closesocket(sClient);
        return;
    }
    qDebug() << "Connected to the Server successfully!";


    connStatus = true;
    ui->labelConnStatus->setText("Status: CONNECTED");

}

void MainWindow::on_pushButtonSend_clicked()
{
    if(sending == true || connStatus == false)
        return;

    // TIMER PARSE
    int timerTime = ui->lineEditTimer->text().toInt();
    if(timerTime == 0)
        timerTime = 1000;
    QString period = "Period: " + QString::number(timerTime);
    ui->labelPeriod->setText(period);


    HelperSocket* helperSocket = new HelperSocket();
    helperSocket->mainWindow = this;
    helperSocket->sClient = sClient;


    // TIMER - AUTO TIMER - SYNCHRONIZATION
    hTimer = CreateWaitableTimer(0, FALSE, 0);
    if(hTimer != 0){

        qDebug() << "Timer created";

        LARGE_INTEGER time;
        time.QuadPart = -10000000LL;
        WINBOOL timerRes = SetWaitableTimer(hTimer, &time, timerTime, 0, 0, FALSE);
        qDebug() << "Timer result = " << timerRes;

        hThread = CreateThread(0, 0, SendMessageThreadFunc, helperSocket, 0, 0);
        qDebug() << "Thread SendMessageThreadFunc: " << hThread;
        CloseHandle(hThread);
    }

    sending = true;
}

DWORD MainWindow::SendMessageThreadFunc(LPVOID lpParam)
{
    HelperSocket* helperSocket = reinterpret_cast<HelperSocket*>(lpParam);
    SOCKET sClient = helperSocket->sClient;
    QMainWindow* mainWindow = helperSocket->mainWindow;
    MainWindow* mainW = reinterpret_cast<MainWindow*>(mainWindow);

    while (true) {

        WaitForSingleObject(hTimer, INFINITE);

        if(!connStatus){
            qDebug() << "Connect to the Server";
            return 3;
        }


        qDebug() << "sClient =" << sClient;
        qDebug() << "QMainWindow in ServeClientFunc =" << mainWindow;
        qDebug() << "MainWindow in ServeClientFunc =" << mainW;

        // WRITE
        QString text = mainW->ui->lineEditMessage->text();
        QString request = text;

        if(disconnectSocket){
            request = "DisconnectMe";
        }

        qDebug() << "request:" << request;
        QByteArray bText = request.toUtf8();
        const char* chText = bText.data();
        int chTextLength = bText.length() + 1;

        int bytesWritten = send(sClient, chText, chTextLength, 0);
        if (bytesWritten <= 0){
            qDebug() << "WriteFile failed";
            closesocket(sClient);
            WSACleanup();
            return 1;
        }
        qDebug() << "Was written bytes :" << bytesWritten << ", message =" << chText;


        // READ

        int bytesRead = SOCKET_ERROR;
        char buffer[512] = "";

        while(bytesRead == SOCKET_ERROR){
            bytesRead = ::recv(sClient, buffer, sizeof (buffer), 0);

            if(bytesRead == 0 || bytesRead == WSAECONNRESET){
                qDebug() << "All data was received or Server was closed connection";
                break;
            }

        }

        QString strBuffer = QString::fromUtf8(buffer);
        qDebug() << "char buffer =" << buffer;
        qDebug() << "QString buffer =" << strBuffer;

        mainW->ui->textEditResponse->append(strBuffer);

        qDebug() << "ANSWER : " << strBuffer;

        // EXIT
        if(disconnectSocket){
            break;
            qDebug() << "breaked while";
        }


    } // WHILE

    // CLOSE RESOURCES

    qDebug() << "Close resources";
    mainW->WasDisconnected();

    qDebug() << "Close socket";
    shutdown(sClient, 2);
    closesocket(sClient);
    WSACleanup();

    qDebug() << "Close timer";
    CancelWaitableTimer(hTimer);
    CloseHandle(hTimer);


}

void MainWindow::on_pushButtonDisconnect_clicked()
{
    if(connStatus == false || sending == false)
        return;

    if(disconnectSocket == false){
        disconnectSocket = true;
    }

}

void MainWindow::WasDisconnected(){

    ui->labelConnStatus->setText("Status: DISCONNECTED");
    connStatus = false;
    disconnectSocket = false;
    sending = false;

}




