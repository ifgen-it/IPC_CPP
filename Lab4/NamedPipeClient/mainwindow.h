#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "windows.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

    HANDLE hPipe;
    bool connStatus = false;
    bool disconnectPipe = false;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButtonConnectServer_clicked();

    void on_pushButtonSend_clicked();

    void on_pushButtonDisconnect_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
