#include "mydemowidget.h"
#include <QtDebug>
#include <QColor>


MyDemoWidget::MyDemoWidget(QWidget *parent) : QWidget(parent)
{
    qRegisterMetaType<MyPoint>("MyPoint");

    m_vector = QVector<MyPoint>();
    m_lines = QVector<int>();
}

void MyDemoWidget::slotAddPoint(MyPoint point)
{
    if(m_vector.size() >= 1){

        MyPoint endPoint = m_vector[m_vector.size()-1];
        QPoint newPoint = point.getPoint();
        QPoint oldPoint = endPoint.getPoint();
 //       qDebug() << "endPoint : x =" << oldPoint.x() << ", y =" << oldPoint.y();

        if(newPoint.y() != oldPoint.y()){
            int lineX = (newPoint.x() + oldPoint.x()) / 2;
            m_lines.push_back(lineX);
    //        qDebug() << "lineX =" << lineX << "line size =" << m_lines.size();
        }

    }
    m_vector.push_back(point);
//    qDebug() << "Vector size:" << m_vector.size();
    repaint();
 //   qDebug() << "repainted";
}

void MyDemoWidget::slotClearWidget()
{
    qDebug() << "begin to clear";
    m_vector.clear();
    m_lines.clear();
    repaint();
    qDebug() << "Cleared";

}

void MyDemoWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // LINES
    auto itLineb = m_lines.begin();
    auto itLinee = m_lines.end();
    while (itLineb != itLinee) {
        int tempX = *itLineb;

        QPen pen = QPen(QBrush(Qt::gray), 0.7);
        painter.setPen(pen);
        QPoint pt1 = QPoint(tempX, lineMinY);
        QPoint pt2 = QPoint(tempX, lineMaxY);
        painter.drawLine(pt1, pt2);

        ++itLineb;
    }

    // POINTS
    auto itb = m_vector.begin();
    auto ite = m_vector.end();
    while (itb != ite) {
        MyPoint temp = *itb;
        temp.draw(painter);
        ++itb;
    }

}
