#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <windows.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT



public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_pushButtonCalc_clicked();


    void on_pushButtonExitProcess_clicked();

    void on_pushButtonTerminateProcess_clicked();

    void on_pushButtonRun3Processes_clicked();

    void on_pushButtonSoliter_clicked();

    void on_pushButtonRunChildProc_clicked();

    void on_pushButtonSendMsg_clicked();

    void on_pushButtonPostMsg_clicked();

    void on_pushButtonBrdCastPostMsg_clicked();

    void on_pushButtonBrdCastSendMsg_clicked();

    void on_lineEditCopyData_textChanged(const QString &arg1);

    void on_pushButtonCreateFileMapping_clicked();

    void on_pushButtonCloseFileMapping_clicked();

    void on_pushButtonLoadFileMapping_clicked();

    void on_pushButtonSaveFileMapping_clicked();

    void on_pushButtonClearTextEdit_clicked();

    void on_textEditFileMapping_textChanged();

    void on_pushButtonFMOpenFile_clicked();

    void on_pushButtonCloseFile_clicked();

    void on_pushButtonFMSaveFile_clicked();


    void on_pushButtonFMLoadFile_clicked();

private:
    Ui::MainWindow *ui;

    // FILEMAPPING
    bool fileMappingWorking = false;
    LPVOID pMap;
    HANDLE hfilemap;
    int sizeFMapping = 512;

    // FILEMAPPING WITH FILE
    HANDLE hfileF;
    bool fileMappingWorkingF = false;
    LPVOID pMapF;
    HANDLE hfilemapF;
    int sizeFMappingF = 1024;



};

#endif // MAINWINDOW_H
