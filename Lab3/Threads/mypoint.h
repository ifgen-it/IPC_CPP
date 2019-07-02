#ifndef MYPOINT_H
#define MYPOINT_H

#include <QPoint>
#include <QColor>
#include <QPainter>

class MyPoint
{

private:
    QPoint m_pt;
    QColor m_col;


public:
    MyPoint(const QPoint& pt = QPoint(), QColor col = Qt::black);
    void draw(QPainter& painter);

    QColor getColor();
    QPoint getPoint();

};

#endif // MYPOINT_H
