#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "windows.h"

#include "helpersocket.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

    SOCKET sClient;



public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    static DWORD WINAPI SendMessageThreadFunc(LPVOID lpParam);

    static HANDLE hTimer;
    static bool connStatus;
    static bool disconnectSocket;
    static bool sending;
    static HANDLE hThread;


    void WasDisconnected();


private slots:

    void on_pushButtonConnectServer_clicked();

    void on_pushButtonSend_clicked();

    void on_pushButtonDisconnect_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
