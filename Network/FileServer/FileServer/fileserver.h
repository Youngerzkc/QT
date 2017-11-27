#ifndef FILESERVER_H
#define FILESERVER_H

#include <QWidget>
#include<QtNetwork/QTcpServer>
#include<QtNetwork/QTcpSocket>
#include<QFile>
#include<QString>

namespace Ui {
class FileServer;
}

class FileServer : public QWidget
{
    Q_OBJECT
    
public:
    explicit FileServer(QWidget *parent = 0);
    ~FileServer();
    
private slots:
    void on_serverButton_clicked();
    void acceptConnection();
     void readClient();
private:
    Ui::FileServer *ui;
    QTcpServer *server;
    qint64 totalSize;
    qint64 byteReceived;
    QTcpSocket *receivedSocket;
    QFile *newFile;
    QByteArray inBlock;
    QString fileName;
};

#endif // FILESERVER_H
