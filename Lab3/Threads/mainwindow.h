#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "mypoint.h"
#include "mydata.h"
#include <windows.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static DWORD WINAPI ThreadFunc(LPVOID lpParam);
    static DWORD WINAPI CSFunc(LPVOID lpParam);
    static DWORD WINAPI MutexFunc(LPVOID lpParam);
    static DWORD WINAPI SystemMutexFunc(LPVOID lpParam);
    static DWORD WINAPI SemaFunc(LPVOID lpParam);
    static DWORD WINAPI SystemSemaFunc(LPVOID lpParam);

    static DWORD WINAPI AutoEventFunc(LPVOID lpParam);
    static DWORD WINAPI ManualEventFunc(LPVOID lpParam);
    static DWORD WINAPI SystemManualEventFunc(LPVOID lpParam);

    static volatile int m_X;
    static const int DELAY = 18000000;
    static const int NUMBER = 24;

    static CRITICAL_SECTION cs;
    static HANDLE hMutex;
    static HANDLE hSystemMutex;
    static HANDLE hSema;
    static HANDLE hSystemSema;

    static HANDLE hAutoEvent;
    static HANDLE hManualEvent;
    static HANDLE hSystemManualEvent;




signals:
    void signalClearWidget();

private:
    Ui::MainWindow *ui;

    MyData* dataRed;
    MyData* dataGreen;
    MyData* dataBlue;



public slots:
    void slotThreadsGo();
    void slotClear();



private slots:
    void on_pushButtonCriticalSection_clicked();
    void on_pushButtonMutex_clicked();
    void on_pushButtonSystemMutex_clicked();

    void on_pushButtonSemaphore_clicked();
    void on_pushButtonSystemSemaphore_clicked();

    void on_pushButtonAutoEvent_clicked();
    void on_pushButtonManualEvent_clicked();
    void on_pushButtonManualEventGo_clicked();
    void on_pushButtonManualEventReset_clicked();
    void on_pushButtonSystemManualEvent_clicked();
};





#endif // MAINWINDOW_H
