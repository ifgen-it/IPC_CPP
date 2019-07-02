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
    HANDLE hR = 0;
    HANDLE hW = 0;
    int clientNumber = 0;

public:
    explicit MainWindow(int argc, char** argv, QWidget *parent = nullptr);
    void receiveMessage();
    void notifyOtherClient();

    ~MainWindow();

private slots:
    void on_pushButtonSend_clicked();

private:
    Ui::MainWindow *ui;

    // QWidget interface
protected:
    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result) override;


};

#endif // MAINWINDOW_H
