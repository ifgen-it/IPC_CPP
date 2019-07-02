#ifndef MYDEMOWIDGET_H
#define MYDEMOWIDGET_H
#include <QWidget>
#include "mypoint.h"


class MyDemoWidget : public QWidget
{
    Q_OBJECT

private:
    QVector<MyPoint> m_vector;
    QVector<int> m_lines;
    static const int lineMinY = 15;
    static const int lineMaxY = 145 + 6;

public:
    explicit MyDemoWidget(QWidget *parent = nullptr);

signals:

public slots:
    void slotAddPoint(MyPoint point);
    void slotClearWidget();



    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;
};

#endif // MYDEMOWIDGET_H
