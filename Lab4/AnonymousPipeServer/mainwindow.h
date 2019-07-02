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
    HANDLE hR1 = 0;
    HANDLE hW1 = 0;
    HANDLE hR2 = 0;
    HANDLE hW2 = 0;

    QString hStrPipes = "";


public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void createClient(int clientNumber);

private slots:
    void on_pushButtonCreatePipes_clicked();

    void on_pushButtonCreateClient1_clicked();

    void on_pushButtonCreateClient2_clicked();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
