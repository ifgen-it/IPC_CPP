#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLibrary>

//#include "DynamicLib.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonAddition_clicked();

    void on_pushButtonSubtraction_clicked();

    void on_pushButtonMultiplication_clicked();

    void on_pushButtonDivision_clicked();


private:
    Ui::MainWindow *ui;

    QLibrary* DLL;

    bool checkInputs(double& x, double& y);

    bool getResultFromFunctionFromLibrary(const char* funcName, double x, double y, double& result);
};

#endif // MAINWINDOW_H
