#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "windows.h"
#include <QLibrary>

//#include "DynamicLib.h"

#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonAddition_clicked()
{
    double x, y;
    if(!checkInputs(x,y)) return;

    double result;
    if(!getResultFromFunctionFromLibrary("Add", x, y, result)){
        qDebug() << "Evaluation error";
        return;
    }

    ui->labelCalculationResult->setText(QString::number(result));
}

void MainWindow::on_pushButtonSubtraction_clicked()
{
    double x, y;
    if(!checkInputs(x,y)) return;

    double result;
    if(!getResultFromFunctionFromLibrary("Subtract", x, y, result)){
        qDebug() << "Evaluation error";
        return;
    }

    ui->labelCalculationResult->setText(QString::number(result));


}

void MainWindow::on_pushButtonMultiplication_clicked()
{
    double x, y;
    if(!checkInputs(x,y)) return;

    double result;
    if(!getResultFromFunctionFromLibrary("Multiply", x, y, result)){
        qDebug() << "Evaluation error";
        return;
    }

    ui->labelCalculationResult->setText(QString::number(result));


}

void MainWindow::on_pushButtonDivision_clicked(){

    double x, y;
    if(!checkInputs(x,y)) return;

    double result;
    if(!getResultFromFunctionFromLibrary("Divide", x, y, result)){
        qDebug() << "Evaluation error";
        return;
    }

    ui->labelCalculationResult->setText(QString::number(result));


}

bool MainWindow::checkInputs(double& x, double& y){

    QString strX = ui->lineEditFirstTerm->text().trimmed();
    QString strY = ui->lineEditSecondTerm->text().trimmed();

    if(strX == "" || strY == ""){
            QMessageBox::information(0, "Alert", "Fill inputs!");
            return false;
    }

    bool okX, okY;
    x = strX.toDouble(&okX);
    y = strY.toDouble(&okY);

    qDebug() << "okX:" << okX;
    qDebug() << "okY:" << okY;

    QString error = "";
    if(!okX) error += "Input double value in first input!\n";
    if(!okY) error += "Input double value in second input!\n";

    if(error != ""){
        QMessageBox::critical(0,"Fail", error);
        return  false;
    }


    return true;
}

bool MainWindow::getResultFromFunctionFromLibrary(const char *funcName, double x, double y, double& result)
{
    // LOAD LIBRARY
    //HMODULE hDLL = LoadLibraryA("");
    DLL = new QLibrary("DynamicLibDEF.dll");
    DLL->load();

    //if(hDLL == 0){
    if(DLL->isLoaded()){
        qDebug() << "Library loaded";
    }
    else {
        qDebug() << "Cannot load library";
        return false;
    }

    // USE EXPORTED FUNCTION
    //FARPROC pFar = GetProcAddress(hDLL, "Add");
    QFunctionPointer pFar = DLL->resolve(funcName);

    if(pFar == 0){
        qDebug() << "Cannot get function Add from library";
        return false;
    }
    else {
        qDebug() << "pFar =" << pFar;
    }

    double(*pFunc)(double, double) = reinterpret_cast<double(*)(double, double)>(pFar);
    qDebug() << "pFunc =" << pFunc;

    // USE
    result = pFunc(x,y);

    // FREE
   // FreeLibrary(hDLL);
    bool unloadRes = DLL->unload();
    qDebug() << "Unload dll:" << unloadRes;

    delete DLL;
    return true;
}

