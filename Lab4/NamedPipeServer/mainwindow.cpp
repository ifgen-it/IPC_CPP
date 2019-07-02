#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "windows.h"
#include <QDebug>

#define PIPE_NAME L"\\\\.\\pipe\\MyNamedPipe"

int MainWindow::clientCounter = 0;
QSet<HANDLE>* MainWindow::hRunningThreads = new QSet<HANDLE>();
QList<HANDLE>* MainWindow::hOpenPipes = new QList<HANDLE>();

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

    while(true){
        // CREATE NAMED PIPE

        HANDLE hPipeClientFinder = CreateNamedPipe(
                    PIPE_NAME,
                    PIPE_ACCESS_DUPLEX, // | FILE_FLAG_OVERLAPPED,
                    PIPE_TYPE_BYTE | PIPE_READMODE_BYTE, //PIPE_WAIT,
                    PIPE_UNLIMITED_INSTANCES,
                    512, // out buffer
                    512, // in buffer
                    100, // timeout
                    0 // inheritance
                    );
        qDebug() << "hPipeClientFinder =" << hPipeClientFinder;
        if (hPipeClientFinder == INVALID_HANDLE_VALUE){
            qDebug() << "Create NamedPipe ClientFinder failed with error" << GetLastError();
            return 1;
        }
        qDebug() << "Server is running now..";
        emit mainW->signalSetServerStatusOn();

        WINBOOL conPipe = ConnectNamedPipe(hPipeClientFinder, 0);
        if(conPipe == 0){
            qDebug() << "ConnectNamedPipe fail with error";
            CloseHandle(hPipeClientFinder);
            return 2;
        }
        Helper* helper = new Helper();
        helper->mainWindow = mainWindow;
        helper->hPipeClientFinder = hPipeClientFinder;

        //  RUN THREAD
        HANDLE htServeClient = CreateThread(0, 0, ServeClientFunc, helper, 0, 0);

        qDebug() << "Running thread added:" << htServeClient;
        qDebug() << "Opening pipe added:" << hPipeClientFinder;

        hRunningThreads->insert(htServeClient);
        hOpenPipes->push_back(hPipeClientFinder);


    }

    qDebug() << "Thread finished";
    return 0;
}

DWORD MainWindow::ServeClientFunc(LPVOID lpParam)
{

    qDebug() << "Thread ServeClientFunc started";

    int clientNumber = ++clientCounter;
    QString strClient = "Client " + QString::number(clientNumber) + ": ";

    Helper* helper = reinterpret_cast<Helper*>(lpParam);
    HANDLE hPipe = helper->hPipeClientFinder;
    QMainWindow* mainWindow = helper->mainWindow;
    MainWindow* mainW = reinterpret_cast<MainWindow*>(mainWindow);

    qDebug() << "hPipe =" << hPipe;
    qDebug() << "QMainWindow in ServeClientFunc =" << mainWindow;
    qDebug() << "MainWindow in ServeClientFunc =" << mainW;


    bool disconnectPipe = false;

    while (true) {

        // READ
        DWORD bytesRead;
        char buffer[512];

        WINBOOL resRead = ReadFile(hPipe, buffer, sizeof(buffer), &bytesRead, 0);
        if(resRead <= 0 ){
            qDebug() << "ReadFile failed";
            CloseHandle(hPipe);
            return 2;
        }
        buffer[bytesRead] = 0;
        QString strBuffer = QString::fromUtf8(buffer);
        QString textRequest = strClient + strBuffer;

        qDebug() << "char buffer =" << textRequest;
        qDebug() << "QString buffer =" << textRequest;

        emit mainW->signalSendData(textRequest, 0);

        if(strBuffer == QString("DisconnectMe")){
            disconnectPipe = true;
        }

        // WRITE
        QString textResponse = strClient + "echo " + strBuffer;
        if(disconnectPipe){
            textResponse = strClient + "has disconnected";
        }
        qDebug() << "Response :" << textResponse;
        QByteArray bText = textResponse.toUtf8();
        const char* chText = bText.data();
        int chTextLength = bText.length() + 1;

        DWORD bytesWritten;

        WINBOOL resWrite = WriteFile(hPipe, chText, chTextLength, &bytesWritten, 0);
        if (resWrite == 0){
            qDebug() << "WriteFile failed";
            CloseHandle(hPipe);
            return 2;
        }
        qDebug() << "Was written bytes :" << bytesWritten;

        emit mainW->signalSendData(textResponse, 1);

        if(disconnectPipe)
            break;
    }


    // DISCONNECT PIPE
    WINBOOL resDisc = DisconnectNamedPipe(hPipe);
    if(resDisc == 0){
        qDebug() << "Disconnect NamedPipe failed";
        return 1;
    }
    qDebug() << "Disconnect result: " << resDisc;

    qDebug() << "Thread ServeClientFunc finished";
    CloseHandle(hPipe);
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

    /*
    qDebug() << "Close PIPES :";

    foreach(HANDLE hPipe, *hOpenPipes){
        qDebug() << "hPipe :" << hPipe;
        WINBOOL resDisc = DisconnectNamedPipe(hPipe);
        if(resDisc == 0){
            qDebug() << "Pipe disconnect failed";
        }
        CloseHandle(hPipe);
        qDebug() << "hPipe :" << hPipe << "closed";
    }
    */

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
