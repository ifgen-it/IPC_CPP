#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "DynamicLib.h"

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

    double res = Add(x,y);
    ui->labelCalculationResult->setText(QString::number(res));

}

void MainWindow::on_pushButtonSubtraction_clicked()
{
    double x, y;
    if(!checkInputs(x,y)) return;

    double res = Subtract(x,y);
    ui->labelCalculationResult->setText(QString::number(res));
}

void MainWindow::on_pushButtonMultiplication_clicked()
{
    double x, y;
    if(!checkInputs(x,y)) return;

    double res = Multiply(x,y);
    ui->labelCalculationResult->setText(QString::number(res));
}

void MainWindow::on_pushButtonDivision_clicked()
{
    double x, y;
    if(!checkInputs(x,y)) return;

    double res = Divide(x,y);
    ui->labelCalculationResult->setText(QString::number(res));
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
