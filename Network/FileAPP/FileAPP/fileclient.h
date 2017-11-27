#ifndef FILECLIENT_H
#define FILECLIENT_H

#include <QDialog>
#include<QTcpSocket>
#include <QFile>
namespace Ui {
class FileClient;
}

class FileClient : public QDialog
{
    Q_OBJECT
    
public:
    explicit FileClient(QWidget *parent = 0);
    ~FileClient();
    
private slots:
    void on_openButton_clicked();
    void send();  //传送文件头信息
   void goOnSend(qint64);  //传送文件内容
    void on_sendButton_clicked();

private:
    Ui::FileClient *ui;
      QTcpSocket *tcpClient;
       QFile *localFile;
       QString fileName;  //文件名

       QByteArray outBlock;  //分次传
       qint64 loadSize;  //每次发送数据的大小
       qint64 byteToWrite;  //剩余数据大小
       qint64 totalSize;  //文件总大小
       int sendTimes;
};

#endif // FILECLIENT_H
