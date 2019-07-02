#ifndef MYDATA_H
#define MYDATA_H

#include <QObject>
#include <QColor>
#include <windows.h>

#include "mypoint.h"

class MyData : public QObject
{
    Q_OBJECT

public:
    int y;
    QColor col;
    int maxX;
    HANDLE hObject;

public:
    explicit MyData(QObject *parent = nullptr);

    MyData(const MyData& other);




signals:
    void signalAddPoint(MyPoint point);

public slots:
};

#endif // MYDATA_H
