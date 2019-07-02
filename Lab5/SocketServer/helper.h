#ifndef HELPER_H
#define HELPER_H

#include <QObject>
#include <qmainwindow.h>
#include "windows.h"

class Helper
{
public:
    Helper();

public:
    HANDLE hPipeClientFinder;
    QMainWindow* mainWindow;

};

#endif // HELPER_H
