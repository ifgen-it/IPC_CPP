#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "windows.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    int childArgC;
    char** childArgV;
    HANDLE hFileFromParent = INVALID_HANDLE_VALUE;
    int anotherMsgCounter = 0;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonSendCout_clicked();

    void on_pushButtonFMCreate_clicked();

    void on_pushButtonFMClose_clicked();

    void on_pushButtonLoadFileMapping_clicked();

    void on_pushButtonSaveFileMapping_clicked();


    void on_pushButtonFMFCreate_clicked();

    void on_pushButtonFMFClose_clicked();

    void on_pushButtonFMFSave_clicked();

    void on_pushButtonFMFLoad_clicked();

private:
    Ui::MainWindow *ui;

    // FILEMAPPING
    int fileMappingOnlinePrint = 1;
    bool fileMappingWorking = false;
    LPVOID pMap;
    HANDLE hfilemap;
    int sizeFMapping = 512;

    // FILEMAPPING WITH FILE
 //   HANDLE hfileF;
    bool fileMappingWorkingF = false;
    LPVOID pMapF;
    HANDLE hfilemapF;
    int sizeFMappingF = 1024;




    // QWidget interface
protected:
    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result) override;

signals:
    void CopyData(const QString& data);
};

#endif // MAINWINDOW_H
