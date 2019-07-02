#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mypoint.h"
#include "mydata.h"

#include <QColor>
#include <QDebug>
#include <QMessageBox>

int volatile MainWindow::m_X = 5;
CRITICAL_SECTION MainWindow::cs;
HANDLE MainWindow::hMutex = 0;
HANDLE MainWindow::hSystemMutex = 0;
HANDLE MainWindow::hSema = 0;
HANDLE MainWindow::hSystemSema = 0;

HANDLE MainWindow::hAutoEvent = 0;
HANDLE MainWindow::hManualEvent = 0;
HANDLE MainWindow::hSystemManualEvent = 0;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // POINTS
    dataRed = new MyData();
    dataRed->col = Qt::red;
    dataRed->y = 30;

    dataGreen = new MyData();
    dataGreen->col = Qt::green;
    dataGreen->y = 80;

    dataBlue = new MyData();
    dataBlue->col = Qt::blue;
    dataBlue->y = 130;

    // HANDLERS

    QMetaObject::Connection con1 =
    connect(ui->pushButtonThreadsGo,SIGNAL(clicked()), this, SLOT(slotThreadsGo()));
    qDebug() << "Slot ThreadsGo =" << con1;

    QMetaObject::Connection con2 =
    connect(ui->pushButtonClear,SIGNAL(clicked()), this, SLOT(slotClear()));
    qDebug() << "Slot Clear =" << con2;

    QMetaObject::Connection con3 =
    connect(this,SIGNAL(signalClearWidget()), ui->widgetField, SLOT(slotClearWidget()));
    qDebug() << "Slot ClearWidget =" << con3;


    // SYNCHRO OBJECTS CREATION
    hMutex = CreateMutex(0, FALSE, 0);
    qDebug() << "hMutex =" << hMutex;

    // SYSTEM MUTEX
    hSystemMutex = OpenMutex(MUTEX_ALL_ACCESS,0,L"SystemMutex");
    qDebug() << "OpenMutex hSystemMutex : " << hSystemMutex;

    if (hSystemMutex == 0){
        hSystemMutex = CreateMutex(0, FALSE, L"SystemMutex");
        qDebug() << "hSystemMutex Create =" << hSystemMutex;
    }

    // SEMAPHORE
    hSema = CreateSemaphore(0, 2, 2, 0);
    qDebug() << "hSema =" << hSema;

    // SYSTEM SEMAPHORE
    hSystemSema = OpenSemaphore(SEMAPHORE_ALL_ACCESS,0,L"SystemSema");
    qDebug() << "OpenSema hSystemSema : " << hSystemSema;

    if (hSystemSema == 0){
        hSystemSema = CreateSemaphore(0, 2, 2, L"SystemSema");
        qDebug() << "hSystemSema Create =" << hSystemSema;
    }

    // AUTO EVENT
    hAutoEvent = CreateEvent(0, FALSE, TRUE, 0); // free
    qDebug() << "hAutoEvent =" << hAutoEvent;

    // MANUAL EVENT
    hManualEvent = CreateEvent(0, TRUE, TRUE, 0);
    qDebug() << "hManualEvent =" << hManualEvent;

    // SYSTEM MANUAL EVENT
    hSystemManualEvent = OpenEvent(EVENT_ALL_ACCESS, 0, L"SystemManualEvent");
    qDebug() << "OpenEvent hSystemManualEvent : " << hSystemManualEvent;

    if  (hSystemManualEvent == 0){
        hSystemManualEvent = CreateEvent(0, TRUE, TRUE, L"SystemManualEvent"); // free
        qDebug() << "hSystemManualEvent =" << hSystemManualEvent;
    }


    InitializeCriticalSection(&cs);

    // SET PRIORITY
    ui->radioButtonRedNormal->click();
    ui->radioButtonGreenNormal->click();
    ui->radioButtonBlueNormal->click();
}

MainWindow::~MainWindow()
{
    delete dataRed;
    delete dataGreen;
    delete dataBlue;

    // SYNCHRO OBJECTS DELETION
    DeleteCriticalSection(&cs);
    CloseHandle(hMutex);
    CloseHandle(hSystemMutex);
    CloseHandle(hSema);
    CloseHandle(hSystemSema);

    CloseHandle(hAutoEvent);
    CloseHandle(hManualEvent);
    CloseHandle(hSystemManualEvent);


    delete ui;
}

void MainWindow::slotClear()
{
    m_X = 5;
    emit signalClearWidget();
}

DWORD MainWindow::ThreadFunc(LPVOID lpParam)
{
    qDebug() << "Thread started";
    MyData* data = reinterpret_cast<MyData*>(lpParam);

    qDebug() << "data =" << data;
    QColor col = data->col;
    int y = data->y;


    for (int num = 0; num < NUMBER; ++num) {

        QPoint pt = QPoint(m_X, y);

        MyPoint mpt = MyPoint(pt, col);
        data->signalAddPoint(mpt);

        m_X += 8;

        int temp = 0;
        for (int i = 0; i < DELAY; i++){
            temp++;
        }
        //Sleep(100);
    }

    qDebug() << "Thread finished";
    return 0;
}

DWORD MainWindow::CSFunc(LPVOID lpParam)
{
   EnterCriticalSection(&cs);
   ThreadFunc(lpParam);
   LeaveCriticalSection(&cs);
   return 0;
}

DWORD MainWindow::MutexFunc(LPVOID lpParam)
{
   WaitForSingleObject(hMutex, INFINITE);
   ThreadFunc(lpParam);
   ReleaseMutex(hMutex);
   return 0;
}

DWORD MainWindow::SystemMutexFunc(LPVOID lpParam)
{
   WaitForSingleObject(hSystemMutex, INFINITE);
   ThreadFunc(lpParam);
   ReleaseMutex(hSystemMutex);
   return 0;
}

DWORD MainWindow::SemaFunc(LPVOID lpParam)
{
   WaitForSingleObject(hSema, INFINITE);
   ThreadFunc(lpParam);
   ReleaseSemaphore(hSema, 1, 0);
   return 0;
}

DWORD MainWindow::SystemSemaFunc(LPVOID lpParam)
{
   WaitForSingleObject(hSystemSema, INFINITE);
   ThreadFunc(lpParam);
   ReleaseSemaphore(hSystemSema, 1, 0);
   return 0;
}

DWORD MainWindow::AutoEventFunc(LPVOID lpParam)
{
   WaitForSingleObject(hAutoEvent, INFINITE);
   ThreadFunc(lpParam);
   SetEvent(hAutoEvent);
   return 0;
}

DWORD MainWindow::ManualEventFunc(LPVOID lpParam)
{
   //WaitForSingleObject(hManualEvent, INFINITE);
   //ThreadFunc(lpParam);

    qDebug() << "Thread started";
    MyData* data = reinterpret_cast<MyData*>(lpParam);

    qDebug() << "data =" << data;
    QColor col = data->col;
    int y = data->y;


    for (int num = 0; num < NUMBER; ++num) {

        WaitForSingleObject(hManualEvent, INFINITE);
        QPoint pt = QPoint(m_X, y);

        MyPoint mpt = MyPoint(pt, col);
        data->signalAddPoint(mpt);

        m_X += 8;

        int temp = 0;
        for (int i = 0; i < DELAY; i++){
            temp++;
        }
        //Sleep(100);
    }

    qDebug() << "Thread finished";
    return 0;


}

DWORD MainWindow::SystemManualEventFunc(LPVOID lpParam)
{
    qDebug() << "Thread started";
    MyData* data = reinterpret_cast<MyData*>(lpParam);

    qDebug() << "data =" << data;
    QColor col = data->col;
    int y = data->y;


    for (int num = 0; num < NUMBER; ++num) {

        WaitForSingleObject(hSystemManualEvent, INFINITE);
        QPoint pt = QPoint(m_X, y);

        MyPoint mpt = MyPoint(pt, col);
        data->signalAddPoint(mpt);

        m_X += 8;

        int temp = 0;
        for (int i = 0; i < DELAY; i++){
            temp++;
        }
        //Sleep(100);
    }

    qDebug() << "Thread finished";
    return 0;
}


void MainWindow::slotThreadsGo()
{
    // CLEAR
    slotClear();

    // CREATE THREADS
    //SetProcessAffinityMask(GetCurrentProcess(), 1);
    HANDLE threads[3];

    // 1st THREAD
    QMetaObject::Connection con1 = connect(dataRed,SIGNAL(signalAddPoint(MyPoint)),ui->widgetField, SLOT(slotAddPoint(MyPoint)),Qt::QueuedConnection);
    qDebug() << "con1 =" << con1;

    threads[0] = CreateThread(0, 0, ThreadFunc, reinterpret_cast<LPVOID>(dataRed), CREATE_SUSPENDED, 0);
    qDebug() << "hFunc1 =" << threads[0];
    SetThreadAffinityMask(threads[0], 1);

    // 2nd THREAD
    QMetaObject::Connection con2 = connect(dataGreen,SIGNAL(signalAddPoint(MyPoint)),ui->widgetField, SLOT(slotAddPoint(MyPoint)),Qt::QueuedConnection);
    qDebug() << "con2 =" << con2;

    threads[1] = CreateThread(0, 0, ThreadFunc, reinterpret_cast<LPVOID>(dataGreen), CREATE_SUSPENDED, 0);
    qDebug() << "hFunc2 =" << threads[1];
    SetThreadAffinityMask(threads[1], 1);

    // 3d THREAD
    QMetaObject::Connection con3 = connect(dataBlue,SIGNAL(signalAddPoint(MyPoint)),ui->widgetField, SLOT(slotAddPoint(MyPoint)),Qt::QueuedConnection);
    qDebug() << "con3 =" << con3;

    threads[2] = CreateThread(0, 0, ThreadFunc, reinterpret_cast<LPVOID>(dataBlue), CREATE_SUSPENDED, 0);
    qDebug() << "hFunc3 =" << threads[2];
    SetThreadAffinityMask(threads[2], 1);

    // SET PRIORITY

    int redPriority, greenPriority, bluePriority;
    int high = THREAD_PRIORITY_ABOVE_NORMAL;
    int normal = THREAD_PRIORITY_NORMAL;
    int low = THREAD_PRIORITY_BELOW_NORMAL;


    if(ui->radioButtonRedHigh->isChecked()) redPriority = high;
    else if(ui->radioButtonRedNormal->isChecked()) redPriority = normal;
    else redPriority = low;

    if(ui->radioButtonGreenHigh->isChecked()) greenPriority = high;
    else if(ui->radioButtonGreenNormal->isChecked()) greenPriority = normal;
    else greenPriority = low;

    if(ui->radioButtonBlueHigh->isChecked()) bluePriority = high;
    else if(ui->radioButtonBlueNormal->isChecked()) bluePriority = normal;
    else bluePriority = low;


    SetThreadPriority(threads[0],redPriority);
    SetThreadPriority(threads[1],greenPriority);
    SetThreadPriority(threads[2],bluePriority);

    qDebug() << "Red priority =" << redPriority;
    qDebug() << "Green priority =" << greenPriority;
    qDebug() << "Blue priority =" << bluePriority;

    // RESUME
    for (int var = 0; var < 3; ++var) {
        ResumeThread(threads[var]);
    }

    // WAITING FOR THREADS WILL FINISH
    //WaitForMultipleObjects(3, threads, true, INFINITE);

    // CLOSE HANDLES
    for (int var = 0; var < 3; ++var) {
        CloseHandle(threads[var]);
    }

}

void MainWindow::on_pushButtonCriticalSection_clicked()
{
    slotClear();

    // CREATE THREADS
   // SetProcessAffinityMask(GetCurrentProcess(), 1);
    HANDLE threads[3];

    // 1st THREAD
    QMetaObject::Connection con1 = connect(dataRed,SIGNAL(signalAddPoint(MyPoint)),ui->widgetField, SLOT(slotAddPoint(MyPoint)),Qt::QueuedConnection);
    qDebug() << "con1 =" << con1;

    threads[0] = CreateThread(0, 0, CSFunc, reinterpret_cast<LPVOID>(dataRed), CREATE_SUSPENDED, 0);
    qDebug() << "hFunc1 =" << threads[0];
    SetThreadAffinityMask(threads[0], 1);

    // 2nd THREAD
    QMetaObject::Connection con2 = connect(dataGreen,SIGNAL(signalAddPoint(MyPoint)),ui->widgetField, SLOT(slotAddPoint(MyPoint)),Qt::QueuedConnection);
    qDebug() << "con2 =" << con2;

    threads[1] = CreateThread(0, 0, CSFunc, reinterpret_cast<LPVOID>(dataGreen), CREATE_SUSPENDED, 0);
    qDebug() << "hFunc2 =" << threads[1];
    SetThreadAffinityMask(threads[1], 1);

    // 3d THREAD
    QMetaObject::Connection con3 = connect(dataBlue,SIGNAL(signalAddPoint(MyPoint)),ui->widgetField, SLOT(slotAddPoint(MyPoint)),Qt::QueuedConnection);
    qDebug() << "con3 =" << con3;

    threads[2] = CreateThread(0, 0, CSFunc, reinterpret_cast<LPVOID>(dataBlue), CREATE_SUSPENDED, 0);
    qDebug() << "hFunc3 =" << threads[2];
    SetThreadAffinityMask(threads[2], 1);

    // SET PRIORITY

    int redPriority, greenPriority, bluePriority;
    int high = THREAD_PRIORITY_ABOVE_NORMAL;
    int normal = THREAD_PRIORITY_NORMAL;
    int low = THREAD_PRIORITY_BELOW_NORMAL;


    if(ui->radioButtonRedHigh->isChecked()) redPriority = high;
    else if(ui->radioButtonRedNormal->isChecked()) redPriority = normal;
    else redPriority = low;

    if(ui->radioButtonGreenHigh->isChecked()) greenPriority = high;
    else if(ui->radioButtonGreenNormal->isChecked()) greenPriority = normal;
    else greenPriority = low;

    if(ui->radioButtonBlueHigh->isChecked()) bluePriority = high;
    else if(ui->radioButtonBlueNormal->isChecked()) bluePriority = normal;
    else bluePriority = low;


    SetThreadPriority(threads[0],redPriority);
    SetThreadPriority(threads[1],greenPriority);
    SetThreadPriority(threads[2],bluePriority);

    qDebug() << "Red priority =" << redPriority;
    qDebug() << "Green priority =" << greenPriority;
    qDebug() << "Blue priority =" << bluePriority;

    // RESUME
    for (int var = 0; var < 3; ++var) {
        ResumeThread(threads[var]);
    }

    // WAITING FOR THREADS WILL FINISH
    //WaitForMultipleObjects(3, threads, true, INFINITE);

    // CLOSE HANDLES
    for (int var = 0; var < 3; ++var) {
        CloseHandle(threads[var]);
    }

}

void MainWindow::on_pushButtonMutex_clicked()
{
    slotClear();


    // CREATE THREADS
    HANDLE threads[3];

    // 1st THREAD
    QMetaObject::Connection con1 = connect(dataRed,SIGNAL(signalAddPoint(MyPoint)),ui->widgetField, SLOT(slotAddPoint(MyPoint)),Qt::QueuedConnection);
    qDebug() << "con1 =" << con1;

    threads[0] = CreateThread(0, 0, MutexFunc, reinterpret_cast<LPVOID>(dataRed), CREATE_SUSPENDED, 0);
    qDebug() << "hFunc1 =" << threads[0];
    SetThreadAffinityMask(threads[0], 1);

    // 2nd THREAD
    QMetaObject::Connection con2 = connect(dataGreen,SIGNAL(signalAddPoint(MyPoint)),ui->widgetField, SLOT(slotAddPoint(MyPoint)),Qt::QueuedConnection);
    qDebug() << "con2 =" << con2;

    threads[1] = CreateThread(0, 0, MutexFunc, reinterpret_cast<LPVOID>(dataGreen), CREATE_SUSPENDED, 0);
    qDebug() << "hFunc2 =" << threads[1];
    SetThreadAffinityMask(threads[1], 1);

    // 3d THREAD
    QMetaObject::Connection con3 = connect(dataBlue,SIGNAL(signalAddPoint(MyPoint)),ui->widgetField, SLOT(slotAddPoint(MyPoint)),Qt::QueuedConnection);
    qDebug() << "con3 =" << con3;

    threads[2] = CreateThread(0, 0, MutexFunc, reinterpret_cast<LPVOID>(dataBlue), CREATE_SUSPENDED, 0);
    qDebug() << "hFunc3 =" << threads[2];
    SetThreadAffinityMask(threads[2], 1);

    // SET PRIORITY

    int redPriority, greenPriority, bluePriority;
    int high = THREAD_PRIORITY_ABOVE_NORMAL;
    int normal = THREAD_PRIORITY_NORMAL;
    int low = THREAD_PRIORITY_BELOW_NORMAL;


    if(ui->radioButtonRedHigh->isChecked()) redPriority = high;
    else if(ui->radioButtonRedNormal->isChecked()) redPriority = normal;
    else redPriority = low;

    if(ui->radioButtonGreenHigh->isChecked()) greenPriority = high;
    else if(ui->radioButtonGreenNormal->isChecked()) greenPriority = normal;
    else greenPriority = low;

    if(ui->radioButtonBlueHigh->isChecked()) bluePriority = high;
    else if(ui->radioButtonBlueNormal->isChecked()) bluePriority = normal;
    else bluePriority = low;


    SetThreadPriority(threads[0],redPriority);
    SetThreadPriority(threads[1],greenPriority);
    SetThreadPriority(threads[2],bluePriority);

    qDebug() << "Red priority =" << redPriority;
    qDebug() << "Green priority =" << greenPriority;
    qDebug() << "Blue priority =" << bluePriority;

    // RESUME
    for (int var = 0; var < 3; ++var) {
        ResumeThread(threads[var]);
    }

    // WAITING FOR THREADS WILL FINISH
   // WaitForMultipleObjects(3, threads, true, INFINITE);

    // CLOSE HANDLES
    for (int var = 0; var < 3; ++var) {
        CloseHandle(threads[var]);
    }


}

void MainWindow::on_pushButtonSystemMutex_clicked()
{
    slotClear();

    // CREATE THREADS
    HANDLE threads[3];

    // 1st THREAD
    QMetaObject::Connection con1 = connect(dataRed,SIGNAL(signalAddPoint(MyPoint)),ui->widgetField, SLOT(slotAddPoint(MyPoint)),Qt::QueuedConnection);
    qDebug() << "con1 =" << con1;

    threads[0] = CreateThread(0, 0, SystemMutexFunc, reinterpret_cast<LPVOID>(dataRed), CREATE_SUSPENDED, 0);
    qDebug() << "hFunc1 =" << threads[0];
    SetThreadAffinityMask(threads[0], 1);

    // 2nd THREAD
    QMetaObject::Connection con2 = connect(dataGreen,SIGNAL(signalAddPoint(MyPoint)),ui->widgetField, SLOT(slotAddPoint(MyPoint)),Qt::QueuedConnection);
    qDebug() << "con2 =" << con2;

    threads[1] = CreateThread(0, 0, SystemMutexFunc, reinterpret_cast<LPVOID>(dataGreen), CREATE_SUSPENDED, 0);
    qDebug() << "hFunc2 =" << threads[1];
    SetThreadAffinityMask(threads[1], 1);

    // 3d THREAD
    QMetaObject::Connection con3 = connect(dataBlue,SIGNAL(signalAddPoint(MyPoint)),ui->widgetField, SLOT(slotAddPoint(MyPoint)),Qt::QueuedConnection);
    qDebug() << "con3 =" << con3;

    threads[2] = CreateThread(0, 0, SystemMutexFunc, reinterpret_cast<LPVOID>(dataBlue), CREATE_SUSPENDED, 0);
    qDebug() << "hFunc3 =" << threads[2];
    SetThreadAffinityMask(threads[2], 1);

    // SET PRIORITY

    int redPriority, greenPriority, bluePriority;
    int high = THREAD_PRIORITY_ABOVE_NORMAL;
    int normal = THREAD_PRIORITY_NORMAL;
    int low = THREAD_PRIORITY_BELOW_NORMAL;


    if(ui->radioButtonRedHigh->isChecked()) redPriority = high;
    else if(ui->radioButtonRedNormal->isChecked()) redPriority = normal;
    else redPriority = low;

    if(ui->radioButtonGreenHigh->isChecked()) greenPriority = high;
    else if(ui->radioButtonGreenNormal->isChecked()) greenPriority = normal;
    else greenPriority = low;

    if(ui->radioButtonBlueHigh->isChecked()) bluePriority = high;
    else if(ui->radioButtonBlueNormal->isChecked()) bluePriority = normal;
    else bluePriority = low;


    SetThreadPriority(threads[0],redPriority);
    SetThreadPriority(threads[1],greenPriority);
    SetThreadPriority(threads[2],bluePriority);

    qDebug() << "Red priority =" << redPriority;
    qDebug() << "Green priority =" << greenPriority;
    qDebug() << "Blue priority =" << bluePriority;

    // RESUME
    for (int var = 0; var < 3; ++var) {
        ResumeThread(threads[var]);
    }

    // CLOSE HANDLES
    for (int var = 0; var < 3; ++var) {
        CloseHandle(threads[var]);
    }
}

void MainWindow::on_pushButtonSemaphore_clicked()
{
    slotClear();

    // CREATE THREADS
    HANDLE threads[3];

    // 1st THREAD
    QMetaObject::Connection con1 = connect(dataRed,SIGNAL(signalAddPoint(MyPoint)),ui->widgetField, SLOT(slotAddPoint(MyPoint)),Qt::QueuedConnection);
    qDebug() << "con1 =" << con1;

    threads[0] = CreateThread(0, 0, SemaFunc, reinterpret_cast<LPVOID>(dataRed), CREATE_SUSPENDED, 0);
    qDebug() << "hFunc1 =" << threads[0];
    SetThreadAffinityMask(threads[0], 1);

    // 2nd THREAD
    QMetaObject::Connection con2 = connect(dataGreen,SIGNAL(signalAddPoint(MyPoint)),ui->widgetField, SLOT(slotAddPoint(MyPoint)),Qt::QueuedConnection);
    qDebug() << "con2 =" << con2;

    threads[1] = CreateThread(0, 0, SemaFunc, reinterpret_cast<LPVOID>(dataGreen), CREATE_SUSPENDED, 0);
    qDebug() << "hFunc2 =" << threads[1];
    SetThreadAffinityMask(threads[1], 1);

    // 3d THREAD
    QMetaObject::Connection con3 = connect(dataBlue,SIGNAL(signalAddPoint(MyPoint)),ui->widgetField, SLOT(slotAddPoint(MyPoint)),Qt::QueuedConnection);
    qDebug() << "con3 =" << con3;

    threads[2] = CreateThread(0, 0, SemaFunc, reinterpret_cast<LPVOID>(dataBlue), CREATE_SUSPENDED, 0);
    qDebug() << "hFunc3 =" << threads[2];
    SetThreadAffinityMask(threads[2], 1);

    // SET PRIORITY

    int redPriority, greenPriority, bluePriority;
    int high = THREAD_PRIORITY_ABOVE_NORMAL;
    int normal = THREAD_PRIORITY_NORMAL;
    int low = THREAD_PRIORITY_BELOW_NORMAL;


    if(ui->radioButtonRedHigh->isChecked()) redPriority = high;
    else if(ui->radioButtonRedNormal->isChecked()) redPriority = normal;
    else redPriority = low;

    if(ui->radioButtonGreenHigh->isChecked()) greenPriority = high;
    else if(ui->radioButtonGreenNormal->isChecked()) greenPriority = normal;
    else greenPriority = low;

    if(ui->radioButtonBlueHigh->isChecked()) bluePriority = high;
    else if(ui->radioButtonBlueNormal->isChecked()) bluePriority = normal;
    else bluePriority = low;


    SetThreadPriority(threads[0],redPriority);
    SetThreadPriority(threads[1],greenPriority);
    SetThreadPriority(threads[2],bluePriority);

    qDebug() << "Red priority =" << redPriority;
    qDebug() << "Green priority =" << greenPriority;
    qDebug() << "Blue priority =" << bluePriority;

    // RESUME
    for (int var = 0; var < 3; ++var) {
        ResumeThread(threads[var]);
    }


    // CLOSE HANDLES
    for (int var = 0; var < 3; ++var) {
        CloseHandle(threads[var]);
    }
}

void MainWindow::on_pushButtonSystemSemaphore_clicked()
{
    slotClear();

    // CREATE THREADS
    HANDLE threads[3];

    // 1st THREAD
    QMetaObject::Connection con1 = connect(dataRed,SIGNAL(signalAddPoint(MyPoint)),ui->widgetField, SLOT(slotAddPoint(MyPoint)),Qt::QueuedConnection);
    qDebug() << "con1 =" << con1;

    threads[0] = CreateThread(0, 0, SystemSemaFunc, reinterpret_cast<LPVOID>(dataRed), CREATE_SUSPENDED, 0);
    qDebug() << "hFunc1 =" << threads[0];
    SetThreadAffinityMask(threads[0], 1);

    // 2nd THREAD
    QMetaObject::Connection con2 = connect(dataGreen,SIGNAL(signalAddPoint(MyPoint)),ui->widgetField, SLOT(slotAddPoint(MyPoint)),Qt::QueuedConnection);
    qDebug() << "con2 =" << con2;

    threads[1] = CreateThread(0, 0, SystemSemaFunc, reinterpret_cast<LPVOID>(dataGreen), CREATE_SUSPENDED, 0);
    qDebug() << "hFunc2 =" << threads[1];
    SetThreadAffinityMask(threads[1], 1);

    // 3d THREAD
    QMetaObject::Connection con3 = connect(dataBlue,SIGNAL(signalAddPoint(MyPoint)),ui->widgetField, SLOT(slotAddPoint(MyPoint)),Qt::QueuedConnection);
    qDebug() << "con3 =" << con3;

    threads[2] = CreateThread(0, 0, SystemSemaFunc, reinterpret_cast<LPVOID>(dataBlue), CREATE_SUSPENDED, 0);
    qDebug() << "hFunc3 =" << threads[2];
    SetThreadAffinityMask(threads[2], 1);

    // SET PRIORITY

    int redPriority, greenPriority, bluePriority;
    int high = THREAD_PRIORITY_ABOVE_NORMAL;
    int normal = THREAD_PRIORITY_NORMAL;
    int low = THREAD_PRIORITY_BELOW_NORMAL;


    if(ui->radioButtonRedHigh->isChecked()) redPriority = high;
    else if(ui->radioButtonRedNormal->isChecked()) redPriority = normal;
    else redPriority = low;

    if(ui->radioButtonGreenHigh->isChecked()) greenPriority = high;
    else if(ui->radioButtonGreenNormal->isChecked()) greenPriority = normal;
    else greenPriority = low;

    if(ui->radioButtonBlueHigh->isChecked()) bluePriority = high;
    else if(ui->radioButtonBlueNormal->isChecked()) bluePriority = normal;
    else bluePriority = low;


    SetThreadPriority(threads[0],redPriority);
    SetThreadPriority(threads[1],greenPriority);
    SetThreadPriority(threads[2],bluePriority);

    qDebug() << "Red priority =" << redPriority;
    qDebug() << "Green priority =" << greenPriority;
    qDebug() << "Blue priority =" << bluePriority;

    // RESUME
    for (int var = 0; var < 3; ++var) {
        ResumeThread(threads[var]);
    }

    // CLOSE HANDLES
    for (int var = 0; var < 3; ++var) {
        CloseHandle(threads[var]);
    }
}



void MainWindow::on_pushButtonAutoEvent_clicked()
{
    slotClear();

    // CREATE THREADS
    HANDLE threads[3];

    // 1st THREAD
    QMetaObject::Connection con1 = connect(dataRed,SIGNAL(signalAddPoint(MyPoint)),ui->widgetField, SLOT(slotAddPoint(MyPoint)),Qt::QueuedConnection);
    qDebug() << "con1 =" << con1;

    threads[0] = CreateThread(0, 0, AutoEventFunc, reinterpret_cast<LPVOID>(dataRed), CREATE_SUSPENDED, 0);
    qDebug() << "hFunc1 =" << threads[0];
    SetThreadAffinityMask(threads[0], 1);

    // 2nd THREAD
    QMetaObject::Connection con2 = connect(dataGreen,SIGNAL(signalAddPoint(MyPoint)),ui->widgetField, SLOT(slotAddPoint(MyPoint)),Qt::QueuedConnection);
    qDebug() << "con2 =" << con2;

    threads[1] = CreateThread(0, 0, AutoEventFunc, reinterpret_cast<LPVOID>(dataGreen), CREATE_SUSPENDED, 0);
    qDebug() << "hFunc2 =" << threads[1];
    SetThreadAffinityMask(threads[1], 1);

    // 3d THREAD
    QMetaObject::Connection con3 = connect(dataBlue,SIGNAL(signalAddPoint(MyPoint)),ui->widgetField, SLOT(slotAddPoint(MyPoint)),Qt::QueuedConnection);
    qDebug() << "con3 =" << con3;

    threads[2] = CreateThread(0, 0, AutoEventFunc, reinterpret_cast<LPVOID>(dataBlue), CREATE_SUSPENDED, 0);
    qDebug() << "hFunc3 =" << threads[2];
    SetThreadAffinityMask(threads[2], 1);

    // SET PRIORITY

    int redPriority, greenPriority, bluePriority;
    int high = THREAD_PRIORITY_ABOVE_NORMAL;
    int normal = THREAD_PRIORITY_NORMAL;
    int low = THREAD_PRIORITY_BELOW_NORMAL;


    if(ui->radioButtonRedHigh->isChecked()) redPriority = high;
    else if(ui->radioButtonRedNormal->isChecked()) redPriority = normal;
    else redPriority = low;

    if(ui->radioButtonGreenHigh->isChecked()) greenPriority = high;
    else if(ui->radioButtonGreenNormal->isChecked()) greenPriority = normal;
    else greenPriority = low;

    if(ui->radioButtonBlueHigh->isChecked()) bluePriority = high;
    else if(ui->radioButtonBlueNormal->isChecked()) bluePriority = normal;
    else bluePriority = low;


    SetThreadPriority(threads[0],redPriority);
    SetThreadPriority(threads[1],greenPriority);
    SetThreadPriority(threads[2],bluePriority);

    qDebug() << "Red priority =" << redPriority;
    qDebug() << "Green priority =" << greenPriority;
    qDebug() << "Blue priority =" << bluePriority;

    // RESUME
    for (int var = 0; var < 3; ++var) {
        ResumeThread(threads[var]);
    }


    // CLOSE HANDLES
    for (int var = 0; var < 3; ++var) {
        CloseHandle(threads[var]);
    }
}

void MainWindow::on_pushButtonManualEvent_clicked()
{
    slotClear();

    // CREATE THREADS
    HANDLE threads[3];

    // 1st THREAD
    QMetaObject::Connection con1 = connect(dataRed,SIGNAL(signalAddPoint(MyPoint)),ui->widgetField, SLOT(slotAddPoint(MyPoint)),Qt::QueuedConnection);
    qDebug() << "con1 =" << con1;

    threads[0] = CreateThread(0, 0, ManualEventFunc, reinterpret_cast<LPVOID>(dataRed), CREATE_SUSPENDED, 0);
    qDebug() << "hFunc1 =" << threads[0];
    SetThreadAffinityMask(threads[0], 1);

    // 2nd THREAD
    QMetaObject::Connection con2 = connect(dataGreen,SIGNAL(signalAddPoint(MyPoint)),ui->widgetField, SLOT(slotAddPoint(MyPoint)),Qt::QueuedConnection);
    qDebug() << "con2 =" << con2;

    threads[1] = CreateThread(0, 0, ManualEventFunc, reinterpret_cast<LPVOID>(dataGreen), CREATE_SUSPENDED, 0);
    qDebug() << "hFunc2 =" << threads[1];
    SetThreadAffinityMask(threads[1], 1);

    // 3d THREAD
    QMetaObject::Connection con3 = connect(dataBlue,SIGNAL(signalAddPoint(MyPoint)),ui->widgetField, SLOT(slotAddPoint(MyPoint)),Qt::QueuedConnection);
    qDebug() << "con3 =" << con3;

    threads[2] = CreateThread(0, 0, ManualEventFunc, reinterpret_cast<LPVOID>(dataBlue), CREATE_SUSPENDED, 0);
    qDebug() << "hFunc3 =" << threads[2];
    SetThreadAffinityMask(threads[2], 1);

    // SET PRIORITY

    int redPriority, greenPriority, bluePriority;
    int high = THREAD_PRIORITY_ABOVE_NORMAL;
    int normal = THREAD_PRIORITY_NORMAL;
    int low = THREAD_PRIORITY_BELOW_NORMAL;


    if(ui->radioButtonRedHigh->isChecked()) redPriority = high;
    else if(ui->radioButtonRedNormal->isChecked()) redPriority = normal;
    else redPriority = low;

    if(ui->radioButtonGreenHigh->isChecked()) greenPriority = high;
    else if(ui->radioButtonGreenNormal->isChecked()) greenPriority = normal;
    else greenPriority = low;

    if(ui->radioButtonBlueHigh->isChecked()) bluePriority = high;
    else if(ui->radioButtonBlueNormal->isChecked()) bluePriority = normal;
    else bluePriority = low;


    SetThreadPriority(threads[0],redPriority);
    SetThreadPriority(threads[1],greenPriority);
    SetThreadPriority(threads[2],bluePriority);

    qDebug() << "Red priority =" << redPriority;
    qDebug() << "Green priority =" << greenPriority;
    qDebug() << "Blue priority =" << bluePriority;

    // RESUME
    for (int var = 0; var < 3; ++var) {
        ResumeThread(threads[var]);
    }


    // CLOSE HANDLES
    for (int var = 0; var < 3; ++var) {
        CloseHandle(threads[var]);
    }
}

void MainWindow::on_pushButtonManualEventGo_clicked()
{
    SetEvent(hSystemManualEvent);
}

void MainWindow::on_pushButtonManualEventReset_clicked()
{
    ResetEvent(hSystemManualEvent);
}

void MainWindow::on_pushButtonSystemManualEvent_clicked()
{
    slotClear();

    // CREATE THREADS
    HANDLE threads[3];

    // 1st THREAD
    QMetaObject::Connection con1 = connect(dataRed,SIGNAL(signalAddPoint(MyPoint)),ui->widgetField, SLOT(slotAddPoint(MyPoint)),Qt::QueuedConnection);
    qDebug() << "con1 =" << con1;

    threads[0] = CreateThread(0, 0, SystemManualEventFunc, reinterpret_cast<LPVOID>(dataRed), CREATE_SUSPENDED, 0);
    qDebug() << "hFunc1 =" << threads[0];
    SetThreadAffinityMask(threads[0], 1);

    // 2nd THREAD
    QMetaObject::Connection con2 = connect(dataGreen,SIGNAL(signalAddPoint(MyPoint)),ui->widgetField, SLOT(slotAddPoint(MyPoint)),Qt::QueuedConnection);
    qDebug() << "con2 =" << con2;

    threads[1] = CreateThread(0, 0, SystemManualEventFunc, reinterpret_cast<LPVOID>(dataGreen), CREATE_SUSPENDED, 0);
    qDebug() << "hFunc2 =" << threads[1];
    SetThreadAffinityMask(threads[1], 1);

    // 3d THREAD
    QMetaObject::Connection con3 = connect(dataBlue,SIGNAL(signalAddPoint(MyPoint)),ui->widgetField, SLOT(slotAddPoint(MyPoint)),Qt::QueuedConnection);
    qDebug() << "con3 =" << con3;

    threads[2] = CreateThread(0, 0, SystemManualEventFunc, reinterpret_cast<LPVOID>(dataBlue), CREATE_SUSPENDED, 0);
    qDebug() << "hFunc3 =" << threads[2];
    SetThreadAffinityMask(threads[2], 1);

    // SET PRIORITY

    int redPriority, greenPriority, bluePriority;
    int high = THREAD_PRIORITY_ABOVE_NORMAL;
    int normal = THREAD_PRIORITY_NORMAL;
    int low = THREAD_PRIORITY_BELOW_NORMAL;


    if(ui->radioButtonRedHigh->isChecked()) redPriority = high;
    else if(ui->radioButtonRedNormal->isChecked()) redPriority = normal;
    else redPriority = low;

    if(ui->radioButtonGreenHigh->isChecked()) greenPriority = high;
    else if(ui->radioButtonGreenNormal->isChecked()) greenPriority = normal;
    else greenPriority = low;

    if(ui->radioButtonBlueHigh->isChecked()) bluePriority = high;
    else if(ui->radioButtonBlueNormal->isChecked()) bluePriority = normal;
    else bluePriority = low;


    SetThreadPriority(threads[0],redPriority);
    SetThreadPriority(threads[1],greenPriority);
    SetThreadPriority(threads[2],bluePriority);

    qDebug() << "Red priority =" << redPriority;
    qDebug() << "Green priority =" << greenPriority;
    qDebug() << "Blue priority =" << bluePriority;

    // RESUME
    for (int var = 0; var < 3; ++var) {
        ResumeThread(threads[var]);
    }


    // CLOSE HANDLES
    for (int var = 0; var < 3; ++var) {
        CloseHandle(threads[var]);
    }
}
