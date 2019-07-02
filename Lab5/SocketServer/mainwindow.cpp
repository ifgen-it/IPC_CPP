#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "windows.h"
#include "winsock2.h"

#include <QDebug>

#define PIPE_NAME L"\\\\.\\pipe\\MyNamedPipe"

int MainWindow::clientCounter = 0;
QSet<HANDLE>* MainWindow::hRunningThreads = new QSet<HANDLE>();
QList<SOCKET>* MainWindow::hOpenSockets = new QList<SOCKET>();
SOCKET MainWindow::sListen = NULL;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() << "this = mainWindow: "<< this;
    // MANUAL SETTINGS

    connect(this,SIGNAL(signalSendData(QString, int)), this, SLOT(slotReceiveData(QString, int)), Qt::QueuedConnection);
    connect(this,SIGNAL(signalSetServerStatusOn(void)), this, SLOT(slotSetServerStatusOn(void)), Qt::QueuedConnection);

    ui->pushButtonStopServer->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

DWORD MainWindow::StartServerFunc(LPVOID lpParam)
{
    qDebug() << "Thread StartServer started";


    // GET POINTER OF MAIN WINDOW
    QMainWindow* mainWindow = reinterpret_cast<QMainWindow*>(lpParam);
    MainWindow* mainW = reinterpret_cast<MainWindow*>(mainWindow);

    qDebug() << "QMainWindow in StartServerFunc : " << mainWindow;

    // CHECK DLL
    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD(2,2);
    int res = WSAStartup(wVersionRequested,&wsaData);
    if(res != 0){
        qDebug() << "Cannot find DLL or version 2.2 is not supported";
    }
    qDebug() << "DLL found!";

    // CREATE LISTENING SOCKET

    sListen = socket(AF_INET, SOCK_STREAM,0);
    if(sListen == INVALID_SOCKET){
        qDebug() << "Cannot create Listening socket";
        closesocket(sListen);
        WSACleanup();
        return 1;
    }
    qDebug() << "Listening socket created";

    // ADDRESS
    sockaddr_in localAddr;
    ZeroMemory(&localAddr, sizeof(sockaddr_in));
    localAddr.sin_family = AF_INET;
    localAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    localAddr.sin_port = htons(15666);

    // BIND LISTENING SOCKET TO THE ADDRESS
    int resBind = bind(sListen, reinterpret_cast<sockaddr*>(&localAddr), sizeof(localAddr));
    if(resBind == SOCKET_ERROR){
        qDebug() << "Error bind";
        closesocket(sListen);
        return 1;
    }
    qDebug() << "Listening socket bound successfully!";

    // MAKE LISTENING
    int listRes = listen(sListen, 15);
    if(listRes == SOCKET_ERROR){
        qDebug() << "Error listening";
        closesocket(sListen);
        return 1;
    }
    qDebug() << "Start listen: host =" << inet_ntoa(localAddr.sin_addr) <<
                ", port =" << ntohs(localAddr.sin_port);
    qDebug() << "Server is running now..";
    emit mainW->signalSetServerStatusOn();



    // GET CLIENT
    while (true) {

        qDebug() << "Waiting for Client..";
        SOCKET sClient = accept(sListen, NULL, NULL);   // BLOCKING FUNCTION

        if(sClient != SOCKET_ERROR){
            qDebug() << "Client connected" << ", sClient =" << sClient;
        }
        else {
            qDebug() << "Client connection error";
        }

        // RUN THREAD FOR CLIENT READ-WRITE

        HelperSocket* helperSocket = new HelperSocket();
        helperSocket->mainWindow = mainWindow;
        helperSocket->sClient = sClient;

        HANDLE htServeClient = CreateThread(0, 0, ServeClientFunc, helperSocket, 0, 0);

        qDebug() << "Running thread added:" << htServeClient;
        qDebug() << "Opening Socket added:" << sClient;

        hRunningThreads->insert(htServeClient);
        hOpenSockets->push_back(sClient);
    }


    qDebug() << "ListeningSocket Thread finished";
    return 0;
}

DWORD MainWindow::ServeClientFunc(LPVOID lpParam)
{

    qDebug() << "Thread ServeClientFunc started";

    int clientNumber = ++clientCounter;
    QString strClient = "Client " + QString::number(clientNumber) + ": ";

    HelperSocket* helperSocket = reinterpret_cast<HelperSocket*>(lpParam);
    SOCKET sClient = helperSocket->sClient;
    QMainWindow* mainWindow = helperSocket->mainWindow;
    MainWindow* mainW = reinterpret_cast<MainWindow*>(mainWindow);

    qDebug() << "sClient =" << sClient;
    qDebug() << "QMainWindow in ServeClientFunc =" << mainWindow;
    qDebug() << "MainWindow in ServeClientFunc =" << mainW;

    bool disconnectSocket = false;

    while (true) {

        // READ
        int bytesRead = SOCKET_ERROR;
        char buffer[512] = "";

        while(bytesRead == SOCKET_ERROR){
            bytesRead = ::recv(sClient, buffer, sizeof (buffer), 0);

            if(bytesRead == 0 || bytesRead == WSAECONNRESET){
                qDebug() << "All data was received or connection was closed";
                break;
            }

        }


        QString strBuffer = QString::fromUtf8(buffer);
        QString textRequest = strClient + strBuffer;

        qDebug() << "char buffer =" << textRequest;
        qDebug() << "QString buffer =" << textRequest;

        emit mainW->signalSendData(textRequest, 0);

        if(strBuffer == QString("DisconnectMe")){
            disconnectSocket = true;
        }

        // WRITE
        QString textResponse = strClient + "echo " + strBuffer;
        if(disconnectSocket){
            textResponse = strClient + "has disconnected";
        }
        qDebug() << "Response :" << textResponse;
        QByteArray bText = textResponse.toUtf8();
        const char* chText = bText.data();
        int chTextLength = bText.length() + 1;

        int bytesWritten = send(sClient, chText, chTextLength, 0);
        if (bytesWritten <= 0){
            qDebug() << "Send failed";
            closesocket(sClient);
            WSACleanup();
            return 1;
        }
        qDebug() << "Was written bytes :" << bytesWritten << ", message =" << chText;

        emit mainW->signalSendData(textResponse, 1);

        if(disconnectSocket)
            break;
    }

    // CLOSE SOCKET
    shutdown(sClient, 2);
    closesocket(sClient);

    return 0;

}


void MainWindow::on_pushButtonStartServer_clicked()
{
    htClientFinder = CreateThread(0, 0, StartServerFunc, this, 0, 0);
    qDebug() << "hThreadClientFinder =" << htClientFinder;

    ui->pushButtonStartServer->setEnabled(false);
    ui->pushButtonStopServer->setEnabled(true);
}

void MainWindow::on_pushButtonStopServer_clicked()
{

    // CLOSE PIPES HANDLES
    // проблема чтобы закрыть каналы, т.к. ReadFile - синхронный он блокирует Канал и его не закрыть
    // надо видимо использовать LPOverLapped - чтобы был асинхронный ReadFile?


    qDebug() << "Close Sockets :";

    foreach(SOCKET sClient, *hOpenSockets){
        qDebug() << "sClient :" << sClient;

        shutdown(sClient,2);
        closesocket(sClient);
        qDebug() << "sClient :" << sClient << "closed";
    }


    // CLOSE THREADS HANDLES

    // Закрывать поток - нехорошо без уведомления клиента, Клиент зависнет при попытке отправить в несущ. Серверный поток

    qDebug() << "Close THREADS :";

    foreach(HANDLE hThread, *hRunningThreads){
        qDebug() << "hThread :" << hThread;
        TerminateThread(hThread,33);
        CloseHandle(hThread);
        qDebug() << "hThread :" << hThread << "closed";
    }

    qDebug() << "Size of hRunningThreads:" << hRunningThreads->size();
    hRunningThreads->clear();
    qDebug() << "Size of hRunningThreads:" << hRunningThreads->size();





    // STOP CLIENTS FINDER THREAD
    // повторно запускается но не работает - после Дисконнекта
    // т.к. Ждущий канал не закрываем, поэтому Клиент в старый Канал обращается, а не в новый?

    closesocket(sListen);
    WSACleanup();

    TerminateThread(htClientFinder, 11);
    CloseHandle(htClientFinder);
    qDebug() << "Server stopped";
    ui->labelServerStatus->setText("Status: STOPPED");

    ui->pushButtonStartServer->setEnabled(true);
    ui->pushButtonStopServer->setEnabled(false);

}

void MainWindow::slotReceiveData(const QString &data, int textEdit)
{
    qDebug() << "slotReceiveData works: " << data;
    if (textEdit == 0){
        ui->textEditRequest->append(data);
    }
    else if (textEdit == 1){
        ui->textEditResponse->append(data);
    }

}

void MainWindow::slotSetServerStatusOn()
{
    ui->labelServerStatus->setText("Status: RUNNING");
}
