#include "fileclient.h"
#include "ui_fileclient.h"
#include<QFileDialog>
#include <QHostAddress>
#include<string>
FileClient::FileClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileClient)
{
    ui->setupUi(this);
    sendTimes=0;
    tcpClient=new QTcpSocket(this);
    connect(tcpClient,SIGNAL(connected()),this,SLOT(send()));
    connect(tcpClient,SIGNAL(bytesWritten(qint64)),\
                    this,SLOT(goOnSend(qint64)));
}

FileClient::~FileClient()
{
    delete ui;
}
void FileClient::goOnSend(qint64 numBytes)
{
byteToWrite-=numBytes;
outBlock=localFile->read(qMin(byteToWrite,loadSize));

}


void FileClient::on_openButton_clicked()
{
    ui->sendStautsLabel->setText(QString("正在打开文件......"));
    loadSize=0;
    byteToWrite=0;
    totalSize=0;
    outBlock.clear();
    fileName=QFileDialog::getOpenFileName(this);
    localFile=new QFile(fileName);
    localFile->open(QFile::ReadOnly);
    ui->sendStautsLabel->setText(QString("已经打开文件%1").arg(fileName));
}
void FileClient::send()
{
byteToWrite=localFile->size();
totalSize=localFile->size();
loadSize=4*1024;
QDataStream out(&outBlock,QIODevice::WriteOnly);
 QString currentFileName = fileName.right(fileName.size() - fileName.lastIndexOf('/')-1);
out <<qint64(0)<<qint64(0)<<currentFileName;
totalSize+=outBlock.size();
byteToWrite+=outBlock.size();
out.device()->seek(0);
out<<totalSize<<qint64(outBlock.size());
tcpClient->write(outBlock);
}



void FileClient::on_sendButton_clicked()
{
    if(sendTimes==0)
    {

        tcpClient->connectToHost(QHostAddress("192.168.0.103"),4096);
        sendTimes=1;
    }
    else
        send();
    ui->sendStautsLabel->setText(QString("正在发送文件%1").arg(fileName));
}
