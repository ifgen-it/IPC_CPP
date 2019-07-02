#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QIcon icon;
    QPixmap pixMap;

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;
};

#endif // MAINWINDOW_H
