#include "mydata.h"

MyData::MyData(QObject *parent) : QObject(parent)
{
    y = 0;
    col = nullptr;
    maxX = 0;
    hObject = 0;

}

MyData::MyData(const MyData &other)
{
    this->y = other.y;
    this->col = other.col;
    this->maxX = other.maxX;
    this->hObject = other.hObject;
}
