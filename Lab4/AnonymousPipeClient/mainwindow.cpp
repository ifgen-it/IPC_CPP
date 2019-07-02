#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "windows.h"
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(int childArgC, char** childArgV, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // INFO FROM COMMAND LINE
    qDebug() << "info from command line:";
    char** ppArgV = childArgV;
    for(int i = 0; i < childArgC; i++){
        qDebug() << "argc:" << 1 + i;
        qDebug() << "argv:" << *ppArgV;

        QString msgArgC = QString::number(i + 1);

        QString msgArgV(*ppArgV);
        qDebug() << "msgArgc:" << msgArgC;
        QString msgText = "argC: " + msgArgC + "\n" +
                "argV: " + msgArgV;
 //       QMessageBox::information(this, "Command line parameters", msgText);
        ppArgV++;

        // COMMAND LINE: AppName clientNumber hR1 hW1 hR2 hW2
        // FETCH CLIENT'S NUMBER
        if(i == 1){
            qDebug() << "Client #" << msgText;
            this->setWindowTitle(this->windowTitle() + " " + msgArgV);
            clientNumber = msgArgV.toInt();
        }

        // FETCH READ AND WRITE HANDLES FOR PIPES
        if(clientNumber == 1){
            //hW1
            if(i == 3){
                hW = reinterpret_cast<HANDLE>(msgArgV.toInt());
            }
            //hR2
            if(i == 4){
                hR = reinterpret_cast<HANDLE>(msgArgV.toInt());
            }
        }
        else if (clientNumber ==2){
            //hR1
            if(i == 2){
                hR = reinterpret_cast<HANDLE>(msgArgV.toInt());
            }
            //hW2
            if(i == 5){
                hW = reinterpret_cast<HANDLE>(msgArgV.toInt());
            }
        }

    }
    QString strHandlePipes = QString("hR = " + QString::number((int)hR)) + QString(", hW = " + QString::number((int)hW));

    //QMessageBox::information(this, "Handles for pipes", strHandlePipes);

    ui->labelHR->setText("hR = " + QString::number((int)hR));
    ui->labelHW->setText("hW = " + QString::number((int)hW));
}

MainWindow::~MainWindow()
{
    if(hR != 0) CloseHandle(hR);
    if(hW != 0) CloseHandle(hW);

    delete ui;
}

void MainWindow::on_pushButtonSend_clicked()
{
    QString textSend = ui->textEditSend->toPlainText().trimmed();
    QString text = "Client " + QString::number(clientNumber) + QString(" : ");
    text = text + textSend;

    qDebug() << "Text to send:" << text;
    QString debugText = text;

    QByteArray bText = text.toUtf8();
    char* chText = bText.data();
    debugText += "\n" + QString(chText);

    DWORD wereWritten;
    WINBOOL writeRes = WriteFile(hW, chText, bText.size(), &wereWritten, 0);
    qDebug() << "Write res:" << writeRes;
    qDebug() << "Written sym:" << wereWritten;

    debugText += "\nwriteRes : " + QString(writeRes);
    debugText += "\nwireWritten : " + QString::number(wereWritten);

 //   QMessageBox::information(0, "send", debugText);
    notifyOtherClient();

    // UPDATE UI
    ui->textEditSend->setText("");
    ui->textEditReceive->append(text);

}

void MainWindow::notifyOtherClient(){

    UINT MyMessage = RegisterWindowMessageA("MyMessage");

    if(MyMessage == 0){
        QMessageBox::critical(0, "Fail", "Cannot register your message!");
        return;
    }
    qDebug() << "MyMessage:" << MyMessage;

    WPARAM wParam = clientNumber;
    LPARAM lParam = 0;
    PostMessageA(HWND_BROADCAST, MyMessage, wParam, lParam);
}

void MainWindow::receiveMessage(){

    DWORD wereRead;
    char buf[512];

    WINBOOL readRes = ReadFile(hR, buf, 512, &wereRead, 0);
    buf[wereRead] = 0;

    QString text = QString::fromUtf8(buf);

    qDebug() << "Read res:" << readRes;
    qDebug() << "Read sym:" << wereRead;

    qDebug() << "Loaded text:" << buf;
    QString debugText = QString(buf);

    debugText += "\nreadRes : " + QString(readRes);
    debugText += "\nwereRead : " + QString::number(wereRead);

 //   QMessageBox::information(0, "receive", debugText);

    // UPDATE UI
    ui->textEditReceive->append(text);

}

bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    UINT MyMessage = RegisterWindowMessageA("MyMessage");

    MSG* msg = static_cast<MSG*>(message);

    if(msg->message == MyMessage){
        WPARAM wp = msg->wParam;
        LPARAM lp = msg->lParam;
        QString msgText = "Wparam: " + QString::number((uint)wp) + "\n"+
                "Lparam: " + QString::number((long)lp);
  //      QMessageBox::information(0,"Client Info", msgText);

        int senderClientNumber = (int)wp;

        if(clientNumber != senderClientNumber)
           receiveMessage();

        *result = 0;
        return true;
    }

    else{
        //qDebug() << "Another message" << ++anotherMsgCounter;
        return false;
    }
}
