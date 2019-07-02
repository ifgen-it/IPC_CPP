#ifndef HELPERSOCKET_H
#define HELPERSOCKET_H

#include <QObject>
#include <qmainwindow.h>
#include "windows.h"

class HelperSocket
{
public:
    HelperSocket();

public:
    QMainWindow* mainWindow;
    SOCKET sClient;
};

#endif // HELPERSOCKET_H
