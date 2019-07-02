#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "windows.h"
#include <QDebug>
#include <QtWinExtras/QtWin>
#include <QPainter>
#include <QPicture>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ICON

    // LOAD LIBRARY
    HMODULE hDLL = LoadLibraryExA("DynamicLibIco.dll", 0, LOAD_LIBRARY_AS_DATAFILE);

    if(hDLL == 0){
        qDebug() << "Cannot load library";
        return;
    }
    else {
        qDebug() << "Library loaded";
    }

    // USE RESOURCE
    //HICON hIcon = LoadIconA(hDLL, "IDB_PNG1");
    HICON hIcon = LoadIconA(hDLL, MAKEINTRESOURCEA(101));

    qDebug() << "hIcon:" << hIcon;

    if(hIcon == 0){
        qDebug() << "Cannot get resource from library";
        return;
    }
    else{
        qDebug() << "Icon was loaded";


        // USE
       // QPixmap pixMap = QtWin::fromHICON(hIcon);
        pixMap = QtWin::fromHICON(hIcon);
        icon = QIcon(pixMap);

        setWindowIcon(icon);


    }
    // FREE
    FreeLibrary(hDLL);


    // ENG STRINGS
    // LOAD LIBRARY
    HMODULE hDLLStrEng = LoadLibraryExA("DynamicLibStringEng.dll", 0, LOAD_LIBRARY_AS_DATAFILE);

    if(hDLLStrEng == 0){
        qDebug() << "Cannot load library hDLLStrEng";
        return;
    }
    else {
        qDebug() << "hDLLStrEng Library loaded";
    }
    // USE RESOURCE
    int size = 100;
    char engStr[size];
    LoadStringA(hDLLStrEng, 101, engStr, size);
    qDebug() << "String from lib:" << engStr;

    // FREE
    FreeLibrary(hDLLStrEng);

    // RUS STRINGS
    // LOAD LIBRARY
    HMODULE hDLLStrRus = LoadLibraryExA("DynamicLibStringRus.dll", 0, LOAD_LIBRARY_AS_DATAFILE);

    if(hDLLStrRus == 0){
        qDebug() << "Cannot load library hDLLStrRus";
        return;
    }
    else {
        qDebug() << "hDLLStrRus Library loaded";
    }
    // USE RESOURCE
    int sizeR = 100;
    wchar_t rusStr[sizeR];
    LoadString(hDLLStrRus, 101, rusStr, sizeof(rusStr));



    QString rStr = QString::fromWCharArray(rusStr);
    qDebug() << "String from lib:" << rStr;

    // FREE
    FreeLibrary(hDLLStrRus);

    // SHOW
    ui->EngText->setText(QString(engStr));
    ui->RusText->setText(rStr);

    repaint();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.drawPixmap(190, 120, pixMap);
}
