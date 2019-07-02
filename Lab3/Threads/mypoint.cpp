#include "mypoint.h"



MyPoint::MyPoint(const QPoint &pt, QColor col)
{
    m_pt = pt;
    m_col = col;
}

void MyPoint::draw(QPainter &painter)
{
    //painter.setBrush(QBrush(m_col));
    QPen pen = QPen(QBrush(m_col), 7);
    painter.setPen(pen);
    QPoint pt2 = QPoint(m_pt.x(), m_pt.y() + 6);
    painter.drawLine(m_pt, pt2);
}

QColor MyPoint::getColor()
{
    return m_col;
}

QPoint MyPoint::getPoint()
{
    return m_pt;
}
