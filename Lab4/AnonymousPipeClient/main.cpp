#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    qDebug() << "argc:" << argc;
    qDebug() << "argv:" << *argv;

    QApplication a(argc, argv);
    MainWindow w(argc, argv);
    //w.childArgC = argc;
   // w.childArgV = argv;

    w.show();

    return a.exec();
}
