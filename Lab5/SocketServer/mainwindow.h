#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "windows.h"
#include "helper.h"
#include "helpersocket.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    HANDLE htClientFinder;


public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static DWORD WINAPI StartServerFunc(LPVOID lpParam);
    static DWORD WINAPI ServeClientFunc(LPVOID lpParam);

    static int clientCounter;
    static QSet<HANDLE>* hRunningThreads;
    static QList<SOCKET>* hOpenSockets;

    static SOCKET sListen;

private slots:
    void on_pushButtonStartServer_clicked();

    void on_pushButtonStopServer_clicked();

private:
    Ui::MainWindow *ui;

signals:
    void signalSendData(const QString& data, int textEdit);
    void signalSetServerStatusOn(void);

public slots:
    void slotReceiveData(const QString& data, int textEdit);
    void slotSetServerStatusOn(void);

};

#endif // MAINWINDOW_H
