#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "windows.h"
#include <QDebug>
#include <QMessageBox>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonCalc_clicked()
{
    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);

    PROCESS_INFORMATION pi;

    wchar_t app1[] = {L"calc"};
    wchar_t app2[] = {L"notepad hello"};

    DWORD dwCreationFlags = CREATE_SUSPENDED;

    BOOL appRun = CreateProcess(0,  //lpApplicationName
                  app1,             //lpCommandLine
                  0,                //lpProcessAttributes
                  0,                //lpThreadAttributes
                  FALSE,            //bInheritHandles
                  dwCreationFlags,                //dwCreationFlags
                  0,                //lpEnvironment
                  0,                //lpCurrentDirectory
                  &si,              //lpStartupInfo
                  &pi               //lpProcessInformation
                  );
    if(!appRun){
        MessageBoxA(0,"CreateProcess failed!", "Info", MB_OK);
        return;
    }
    else{
        MessageBoxA(0,"CreateProcess successed!", "Info", MB_OK);
//        QMessageBox* msb = new QMessageBox();
//        msb->setText("Success");
//        msb->setWindowTitle("Info");
//        msb->setFixedWidth(400);
//        msb->show();


        DWORD tResumeRes = ResumeThread(pi.hThread);

        // CHILD PROCESS IS WORKING HERE
        qDebug() << "Info about chind app:";
        qDebug() << "ProcessID:" << pi.dwProcessId;
        qDebug() << "ThreadID:" << pi.dwThreadId;
        qDebug() << "HandleProcess:" << pi.hProcess;
        qDebug() << "HandleThread:" << pi.hThread;
        DWORD dwExitCode;
        GetExitCodeProcess(pi.hProcess, &dwExitCode);
        qDebug() << "Exit code:" << dwExitCode;
        qDebug() << "App thread resume res:" << tResumeRes;









        if(WaitForSingleObject(pi.hProcess, INFINITE)!= WAIT_FAILED){
            DWORD dwExitCode;

            GetExitCodeProcess(pi.hProcess, &dwExitCode);
            qDebug() << "Exitcode:" << dwExitCode;

            FILETIME pCreationTime, pExitTime, pKernelTime, pUserTime;
            FILETIME tCreationTime, tExitTime, tKernelTime, tUserTime;
            SYSTEMTIME stProc, stThread;

            // PROCESS TIME
            BOOL getProcRes = GetProcessTimes(pi.hProcess, &pCreationTime, &pExitTime, &pKernelTime, &pUserTime);
            qlonglong deltaProc = *reinterpret_cast<qlonglong*>(&pExitTime) - *reinterpret_cast<qlonglong*>(&pCreationTime);
            FileTimeToSystemTime(reinterpret_cast<FILETIME*>(&deltaProc), &stProc);

            // THREAD TIME
            BOOL getThreadRes = GetThreadTimes(pi.hThread, &tCreationTime, &tExitTime, &tKernelTime, &tUserTime);
            qlonglong deltaThread = *reinterpret_cast<qlonglong*>(&tExitTime) - *reinterpret_cast<qlonglong*>(&tCreationTime);
            FileTimeToSystemTime(reinterpret_cast<FILETIME*>(&deltaThread), &stThread);

            // PRIORITY
            DWORD pPriority = GetPriorityClass(pi.hProcess);
            int tPriority = GetThreadPriority(pi.hThread);

            qDebug() << "getProcRes:" << getProcRes;
            qDebug() << "process workingTime:" << stProc.wSecond << ":" << stProc.wMilliseconds;

            qDebug() << "getThreadRes:" << getThreadRes;
            qDebug() << "Thread workingTime:" << stThread.wSecond << ":" << stThread.wMilliseconds;

            qDebug() << "process priority:" << pPriority;
            qDebug() << "thread prioriry:" << tPriority;

            QString pWorkTime = QString::number(stProc.wSecond) + "sec " + QString::number(stProc.wMilliseconds) + "msec";
            QMessageBox::information(this, "Info about app working time",pWorkTime);

        }


        /*BOOL res = TerminateProcess(pi.hProcess,66);
        qDebug() << "app terminated" << res;

        DWORD dwExitCode;
        GetExitCodeProcess(pi.hProcess, &dwExitCode);
        qDebug() << "Exitcode:" << dwExitCode;*/


        // CLOSE THREAD HANDLE
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);


    }
}

void MainWindow::on_pushButtonExitProcess_clicked()
{
    ExitProcess(33);
}

void MainWindow::on_pushButtonTerminateProcess_clicked()
{
    HANDLE thisProc = GetCurrentProcess();
    TerminateProcess(thisProc, 11);
}

void MainWindow::on_pushButtonRun3Processes_clicked()
{

    wchar_t app1[] = {L"calc"};
    wchar_t app2[] = {L"notepad"};
    wchar_t app3[] = {L"cmd"};

    wchar_t* apps[3];
    apps[0] = app1;
    apps[1] = app2;
    apps[2] = app3;

    HANDLE appsHandProc[3];
    HANDLE appsHandThread[3];

    for(int i = 0; i < 3; i++){

        STARTUPINFO si;
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);

        PROCESS_INFORMATION pi;

        BOOL appRun = CreateProcess(0,  //lpApplicationName
                      apps[i],             //lpCommandLine
                      0,                //lpProcessAttributes
                      0,                //lpThreadAttributes
                      FALSE,            //bInheritHandles
                      0,                //dwCreationFlags
                      0,                //lpEnvironment
                      0,                //lpCurrentDirectory
                      &si,              //lpStartupInfo
                      &pi               //lpProcessInformation
                      );
        if(!appRun){
            MessageBoxA(0,"CreateProcess failed!", "Info", MB_OK);
            return;
        }
        else{
            appsHandProc[i] = pi.hProcess;
            appsHandThread[i] = pi.hThread;
        }
    }

    // WORKING WITH PROCESSES HERE

    while(true){
        DWORD res = MsgWaitForMultipleObjects(
                    3,              // amount of awaiting objects
                    appsHandProc,   // pointer on Array of process handlers
                    FALSE,          // true - wait for all
                    INFINITE,       // wait duration
                    QS_ALLEVENTS    // type of event
                    );

        qDebug() << "res =" << res;

        if(res == WAIT_OBJECT_0){
            qDebug() << "obj 1 - calc";

            BOOL res1 = TerminateProcess(appsHandProc[1],404);
            BOOL res2 = TerminateProcess(appsHandProc[2],404);

            qDebug() << "notepad terminated -" << res1;
            qDebug() << "cmd terminated -" << res2;

            break;
        }
        if(res == WAIT_OBJECT_0 + 1){
            qDebug() << "obj 2 - notepad";

            BOOL res1 = TerminateProcess(appsHandProc[0],404);
            BOOL res2 = TerminateProcess(appsHandProc[2],404);

            qDebug() << "calc terminated -" << res1;
            qDebug() << "cmd terminated -" << res2;

            break;
        }
        if(res == WAIT_OBJECT_0 + 2){
            qDebug() << "obj 3 - cmd";

            BOOL res1 = TerminateProcess(appsHandProc[0],404);
            BOOL res2 = TerminateProcess(appsHandProc[1],404);

            qDebug() << "calc terminated -" << res1;
            qDebug() << "notepad terminated -" << res2;

            break;
        }
        // else message:
        MSG m;
        int counter =0;
        while(PeekMessageA(&m,0,0,0,PM_REMOVE))
        {
            DispatchMessageA(&m);
            qDebug() << "message" << ++counter;
        }




    }




    // CLOSE HANDLERS
    for(int i = 0; i < 3; i++){
        qDebug() << "Close handler thread"<< i << ":" << CloseHandle(appsHandThread[i]);
        qDebug() << "Close handler process"<< i << ":" << CloseHandle(appsHandProc[i]);
    }



}

void MainWindow::on_pushButtonSoliter_clicked()
{
    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));

    // STARTUPINFO - COMMON
    si.cb = sizeof(si);
    si.dwFlags = STARTF_FORCEONFEEDBACK
            | STARTF_USEPOSITION
            | STARTF_USESIZE
     //       | STARTF_USESHOWWINDOW
            | STARTF_USEFILLATTRIBUTE
            | STARTF_USECOUNTCHARS


            ;
    si.dwX = 100;
    si.dwY = 100;
    si.dwXSize = 100;
    si.dwYSize = 100;
    si.lpDesktop = 0;

    // hStdInput, hStdOutput, hStdError

    // STARTUPINFO - GUI
    //si.wShowWindow = SW_SHOWMAXIMIZED;

    // STARTUPINFO - CONSOLE
    //dwXCountChars, dwYCountChars, dwFillAttribute, lpTitle
    si.lpTitle = {L"++ My cmd ++"};
    si.dwXCountChars = 100;
    si.dwYCountChars = 100;
    si.dwFillAttribute = FOREGROUND_RED | BACKGROUND_GREEN;


    PROCESS_INFORMATION pi;

    //wchar_t app1[] = {L"C:\\Program Files\\Microsoft Games\\Solitaire\\Solitaire"};
    //wchar_t app1[] = {L"explorer"};
    wchar_t app1[] = {L"cmd"};

    BOOL appRun = CreateProcess(0,  //lpApplicationName
                  app1,             //lpCommandLine
                  0,                //lpProcessAttributes
                  0,                //lpThreadAttributes
                  FALSE,            //bInheritHandles
                  CREATE_NEW_CONSOLE, //dwCreationFlags
                  0,                //lpEnvironment
                  0,                //lpCurrentDirectory
                  &si,              //lpStartupInfo
                  &pi               //lpProcessInformation
                  );
    if(!appRun){
        MessageBoxA(0,"CreateProcess failed!", "Info", MB_OK);
        return;
    }
    else{







        // CLOSE THREAD HANDLE
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);


    }
}

void MainWindow::on_pushButtonRunChildProc_clicked()
{
    // SECURITY ATTRIBUTES -> FOR HANDLE INHERITANCE FOR CHILD PROCESS
    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof (sa);
    sa.lpSecurityDescriptor = 0;
    sa.bInheritHandle = TRUE;

    // CREATE FILE
    char filePath[] = "..\\file.txt";

    HANDLE hfile = CreateFileA(
                filePath,                                 // fileName
                GENERIC_READ | GENERIC_WRITE,             // dw desiredAccess
                FILE_SHARE_READ | FILE_SHARE_WRITE,       // dw share mode
                &sa,                                       // lp Security attributes
                CREATE_ALWAYS,                           // dw Creation disposition
                FILE_ATTRIBUTE_NORMAL,                   // dw flags Attributes
                0                                        // h template file
                );
    if(hfile == INVALID_HANDLE_VALUE){
        DWORD err = GetLastError();
        QString errMsg = "File not created! Error code: " + QString::number((int)err);
        QMessageBox::critical(0,"Alert", errMsg);
        return;
    }
    qDebug() << "handle file:" << hfile;
    QString strHFile = QString::number((int)hfile);
    qDebug() << "intHandle file:" << strHFile;

    DWORD written;
 //   WriteFile(hfile,"hello child!",sizeof("hello child!"), &written,0);


    // CREATE CHILD PROCESS

    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));

    // STARTUPINFO - COMMON
    si.cb = sizeof(si);
    si.dwFlags =
             STARTF_FORCEONFEEDBACK
            | STARTF_USEPOSITION
            | STARTF_USESIZE
            | STARTF_USESHOWWINDOW
            | STARTF_USESTDHANDLES
            ;
    si.dwX = 100;
    si.dwY = 100;
    si.dwXSize = 300;
    si.dwYSize = 300;
    si.lpDesktop = 0;
    si.hStdOutput = hfile;
    // hStdInput, hStdOutput, hStdError

    // STARTUPINFO - GUI
    si.wShowWindow = SW_SHOWDEFAULT;

    // STARTUPINFO - CONSOLE
    //dwXCountChars, dwYCountChars, dwFillAttribute, lpTitle


    PROCESS_INFORMATION pi;



    //wchar_t app1[] = {L"..\\Practice1Child\\debug\\Practice1Child nextWillBeHandleForFile "};

    QString strApp("..\\Practice1Child\\debug\\Practice1Child nextWillBeHandleForFile");
    strApp += " " + strHFile;

    wchar_t app1[strApp.length() + 1];
    strApp.toWCharArray(app1);
    app1[strApp.length()] = 0;



    qDebug() << "Current path:" << QDir::currentPath();

    DWORD resDir;
    char strPath[200];
    resDir = GetCurrentDirectoryA(200, strPath);
    qDebug() << "Current path Win32:" << strPath;

    BOOL appRun = CreateProcess(0,  //lpApplicationName
                  app1,             //lpCommandLine
                  0,                //lpProcessAttributes
                  0,                //lpThreadAttributes
                  TRUE,            //bInheritHandles
                  0,                //dwCreationFlags
                  0,                //lpEnvironment
                  0,                //lpCurrentDirectory
                  &si,              //lpStartupInfo
                  &pi               //lpProcessInformation
                  );
    if(!appRun){
        MessageBoxA(0,"CreateProcess failed!", "Info", MB_OK);

        // CLOSE FILE HANDLE
        CloseHandle(hfile);
        qDebug() << "hfile closed";
        return;
    }

    // CLOSE FILE HANDLE
    CloseHandle(hfile);
    qDebug() << "hfile closed";



    // CLOSE THREAD HANDLE
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);



}

void MainWindow::on_pushButtonSendMsg_clicked()
{
    HWND h = FindWindowA(0, "Child process");

    if(h == 0)
    {
        QMessageBox::critical(0,"Fail", "Cannot find window 'Child process'!");
        return;
    }
    qDebug() << "Found window handle:" << h;

    static UINT MyMessage = RegisterWindowMessageA("MyMessage");

    if(MyMessage == 0){
        QMessageBox::critical(0, "Fail", "Cannot register your message!");
        return;
    }
    qDebug() << "MyMessage:" << MyMessage;

    WPARAM wParam = ui->lineEditWparam->text().toUInt();
    LPARAM lParam = ui->lineEditLparam->text().toLong();
    SendMessageA(h, MyMessage, wParam, lParam);

}

void MainWindow::on_pushButtonPostMsg_clicked()
{
    HWND h = FindWindowA(0, "Child process");

    if(h == 0)
    {
        QMessageBox::critical(0,"Fail", "Cannot find window 'Child process'!");
        return;
    }
    qDebug() << "Found window handle:" << h;

    static UINT MyMessage = RegisterWindowMessageA("MyMessage");

    if(MyMessage == 0){
        QMessageBox::critical(0, "Fail", "Cannot register your message!");
        return;
    }
    qDebug() << "MyMessage:" << MyMessage;

    WPARAM wParam = ui->lineEditWparam->text().toUInt();
    LPARAM lParam = ui->lineEditLparam->text().toLong();
    PostMessageA(h, MyMessage, wParam, lParam);

}

void MainWindow::on_pushButtonBrdCastPostMsg_clicked()
{
    UINT MyMessage = RegisterWindowMessageA("MyMessage");

    if(MyMessage == 0){
        QMessageBox::critical(0, "Fail", "Cannot register your message!");
        return;
    }
    qDebug() << "MyMessage:" << MyMessage;

    WPARAM wParam = ui->lineEditWparam->text().toUInt();
    LPARAM lParam = ui->lineEditLparam->text().toLong();
    PostMessageA(HWND_BROADCAST, MyMessage, wParam, lParam);
}

void MainWindow::on_pushButtonBrdCastSendMsg_clicked()
{
    UINT MyMessage = RegisterWindowMessageA("MyMessage");

    if(MyMessage == 0){
        QMessageBox::critical(0, "Fail", "Cannot register your message!");
        return;
    }
    qDebug() << "MyMessage:" << MyMessage;

    WPARAM wParam = ui->lineEditWparam->text().toUInt();
    LPARAM lParam = ui->lineEditLparam->text().toLong();
    SendMessageA(HWND_BROADCAST, MyMessage, wParam, lParam);
}

void MainWindow::on_lineEditCopyData_textChanged(const QString &arg1)
{
    HWND hChild = FindWindowA(0, "Child process");
    HWND hParent = FindWindowA(0, "Parent process");

    if(hParent == 0)
    {
        QMessageBox::critical(0,"Fail", "Cannot find window 'Parent process'!");
        return;
    }
    if(hChild == 0)
    {
        QMessageBox::critical(0,"Fail", "Cannot find window 'Child process'!");
        return;
    }
    qDebug() << "Parent window handle:" << hParent;
    qDebug() << "Found window handle:" << hChild;

    QString msgText = ui->lineEditCopyData->text();
    std::string strMsgText = msgText.toStdString();
    int countBytesStrMsgText = (int)strMsgText.length() + 1;
    const char* chMsgText = strMsgText.c_str();

    qDebug() << "msgText:" << msgText;
    qDebug() << "chMsgText:" << chMsgText;
    qDebug() << "countBytesStrMsgText:" << countBytesStrMsgText;

    COPYDATASTRUCT data;
    data.dwData = 33;
    data.cbData = (DWORD)countBytesStrMsgText;
    data.lpData = (LPVOID)chMsgText;

    SendMessageA(hChild,WM_COPYDATA, (WPARAM)hParent, (LPARAM)&data);



}

void MainWindow::on_pushButtonCreateFileMapping_clicked()
{
    // CREATE FILE MAPPING
    if(fileMappingWorking){
        QMessageBox::information(0, "Info", "File mapping already created by this process!");
        return;
    }
    hfilemap = CreateFileMappingA(
                INVALID_HANDLE_VALUE,       // hFile
                0,                          // lpFileMappingAttributes
                PAGE_READWRITE,             // flProtect
                0,                          // dwMaximumSizeHigh
                sizeFMapping,                       // dwMaximumSizeLow
                "MyFileMapping"             // lpName
                );
    if (hfilemap == 0){
        QMessageBox::critical(0, "Fail", "Cannot create filemapping!");
        return;
    }
    if(GetLastError() == ERROR_ALREADY_EXISTS){
        QMessageBox::information(0, "Alert", "Got filemapping from Virtual Memory!");
    }

    // CREATE MAP VIEW OF FILE
    pMap = MapViewOfFile(
                hfilemap,        // hFileMappingObject
                FILE_MAP_WRITE,  // dwDesiredAccess
                0,               // dwFileOffsetHigh
                0,               // dwFileOffserLow
                0                // dwNumberOfBytesToMap
                );
    if(pMap == NULL){
        DWORD err = GetLastError();
        QMessageBox::critical(0,"Fail", "Cannot create MapViewOfFile, error: " + QString::number((int)err));

        CloseHandle(hfilemap);
        return;
    }

    // WORKING WITH FILE MAPPING
    fileMappingWorking = true;
    ui->labelFileMappingInfo->setText("INFO: File mapping created");

}

void MainWindow::on_pushButtonCloseFileMapping_clicked()
{
    if(fileMappingWorking){

        // CLOSE HANDLES
        UnmapViewOfFile(pMap);
        CloseHandle(hfilemap);
        fileMappingWorking = false;
        ui->labelFileMappingInfo->setText("INFO: File mapping closed");
    }
    else{
        QMessageBox::information(0,"Info", "File mapping did not created!");
    }
}

void MainWindow::on_pushButtonLoadFileMapping_clicked()
{
    if(fileMappingWorking){

        char* p = static_cast<char*>(pMap);

        ui->textEditFileMapping->setText(QString::fromUtf8(p));

        ui->labelFileMappingInfo->setText("INFO: File mapping loaded");
    }
    else{
        QMessageBox::information(0,"Info", "File mapping did not created!");
    }
}

void MainWindow::on_pushButtonSaveFileMapping_clicked()
{
    if(fileMappingWorking){

        QString fmText = ui->textEditFileMapping->toPlainText();
        qDebug() << "fmText:" << fmText;

   //     const char* chFmText = fmText.toStdString().c_str();
        QByteArray bFmText = fmText.toUtf8();
        const char* chFmText = bFmText.data();

        qDebug() << "chFmText:" << chFmText;

        char* p = static_cast<char*>(pMap);
        qDebug() << "p:" << QString(p);

        //strcpy(p,chFmText);
        memcpy(p,chFmText,bFmText.length()+1);

        ui->labelFileMappingInfo->setText("INFO: File mapping saved");
    }
    else{
        QMessageBox::information(0,"Info", "File mapping did not created!");
    }
}

void MainWindow::on_pushButtonClearTextEdit_clicked()
{
    ui->textEditFileMapping->setText("");
    ui->labelFileMappingInfo->setText("INFO: Text field cleared");
}

void MainWindow::on_textEditFileMapping_textChanged()
{
    if(fileMappingWorking){

        // SAVE FILEMAPPING
        if(fileMappingWorking){
            QString fmText = ui->textEditFileMapping->toPlainText();
            QByteArray bFmText = fmText.toUtf8();
            const char* chFmText = bFmText.constData();
            char* p = static_cast<char*>(pMap);

         //   strcpy(p,chFmText);
            memcpy(p,chFmText,bFmText.length()+1);
        }

        // BROADCAST MESSAGE
        UINT MyFileMappingMsg = RegisterWindowMessageA("FileMappingChangedParent");

        if(MyFileMappingMsg == 0){
            QMessageBox::critical(0, "Fail", "Cannot register your message!");
            return;
        }
        //qDebug() << "MyMessage:" << MyMessage;

        WPARAM wParam = 0;
        LPARAM lParam = 0;
        PostMessageA(HWND_BROADCAST, MyFileMappingMsg, wParam, lParam);
    }
}

void MainWindow::on_pushButtonFMOpenFile_clicked()
{
    // CREATE FILE

        if(fileMappingWorkingF){
            QMessageBox::information(0, "Info", "File already opened!");
            return;
        }

    char filePath[] = "..\\fileMapping.txt";

    hfileF = CreateFileA(
                filePath,                                 // fileName
                GENERIC_READ | GENERIC_WRITE,             // dw desiredAccess
                FILE_SHARE_READ | FILE_SHARE_WRITE,       // dw share mode
                0,                                       // lp Security attributes
                OPEN_EXISTING,                           // dw Creation disposition
                FILE_ATTRIBUTE_NORMAL,                   // dw flags Attributes
                0                                        // h template file
                );
    if(hfileF == INVALID_HANDLE_VALUE){
        DWORD err = GetLastError();
        QString errMsg = "Could not open file! Error code: " + QString::number((int)err);
        QMessageBox::critical(0,"Alert", errMsg);
        return;
    }

    // CREATE FILEMAPPING

    hfilemapF = CreateFileMappingA(
                hfileF,                      // hFile
                0,                          // lpFileMappingAttributes
                PAGE_READWRITE,             // flProtect
                0,                          // dwMaximumSizeHigh
                sizeFMappingF,               // dwMaximumSizeLow
                "MyFMFile"                   // lpName
                );
    if (hfilemapF == 0){
        QMessageBox::critical(0, "Fail", "Cannot create filemapping!");
        return;
    }
    if(GetLastError() == ERROR_ALREADY_EXISTS){
        QMessageBox::information(0, "Alert", "Got filemapping from Virtual Memory!");
    }

    // CREATE MAP VIEW OF FILE
    pMapF = MapViewOfFile(
                hfilemapF,        // hFileMappingObject
                FILE_MAP_WRITE,  // dwDesiredAccess
                0,               // dwFileOffsetHigh
                0,               // dwFileOffserLow
                0                // dwNumberOfBytesToMap
                );
    if(pMapF == NULL){
        DWORD err = GetLastError();
        QMessageBox::critical(0,"Fail", "Cannot create MapViewOfFile, error: " + QString::number((int)err));

        CloseHandle(hfilemapF);
        return;
    }

    // LOADING DATA FROM FILE
    char* p = static_cast<char*>(pMapF);
    ui->textEditFMFile->setText(QString::fromUtf8(p));

    // WORKING WITH FILE MAPPING
    fileMappingWorkingF = true;
    ui->labelFileMappingFInfo->setText("INFO: File opened");



}

void MainWindow::on_pushButtonCloseFile_clicked()
{
    if(fileMappingWorkingF){

        // CLOSE HANDLES
        UnmapViewOfFile(pMapF);
        CloseHandle(hfilemapF);
        CloseHandle(hfileF);

        fileMappingWorkingF = false;
        ui->labelFileMappingFInfo->setText("INFO: File closed");
    }
    else{
        QMessageBox::information(0,"Info", "File did not opened!");
    }
}

void MainWindow::on_pushButtonFMSaveFile_clicked()
{
    if(fileMappingWorkingF){

        QString fmText = ui->textEditFMFile->toPlainText();
        qDebug() << "fmText:" << fmText;

   //     const char* chFmText = fmText.toStdString().c_str();
        QByteArray bFmText = fmText.toUtf8();
        char* chFmText = bFmText.data();

        qDebug() << "chFmText:" << chFmText;

        char* p = static_cast<char*>(pMapF);
        qDebug() << "p:" << QString(p);

        //strcpy(p,chFmText);
        memcpy(p, chFmText,bFmText.length() + 1);

        ui->labelFileMappingFInfo->setText("INFO: File saved");
        WINBOOL res = FlushViewOfFile(pMapF, sizeFMappingF);
        qDebug() << "flushed:" << res;

    }
    else{
        QMessageBox::information(0,"Info", "File did not opened!");
    }
}

void MainWindow::on_pushButtonFMLoadFile_clicked()
{
    if(fileMappingWorkingF){

        char* p = static_cast<char*>(pMapF);

        ui->textEditFMFile->setText(QString::fromUtf8(p));

        ui->labelFileMappingFInfo->setText("INFO: File loaded");
    }
    else{
        QMessageBox::information(0,"Info", "File did not opened!");
    }
}
