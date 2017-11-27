    #include "fileserver.h"
    #include "ui_fileserver.h"
    #include"QHostAddress"
    #include<QDir>
    FileServer::FileServer(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::FileServer)
    {
        ui->setupUi(this);

    }

    FileServer::~FileServer()
    {
        delete ui;
    }
    void FileServer::acceptConnection()
    {

        qDebug()<<"接受";
     ui->receivedStatusLabel->setText(tr("已连接，正在准备接收文件!"));
    receivedSocket=server->nextPendingConnection();
    connect(receivedSocket,SIGNAL(readyRead()),this,SLOT(readClient()));
    }
    void FileServer::readClient()
    {
         ui->receivedStatusLabel->setText(tr("正在接收文件..."));
        if(byteReceived==0)
        {
            QDataStream in(receivedSocket);
            in>>totalSize>>byteReceived>>fileName;
            fileName =QDir::homePath()+"/"+fileName;
            qDebug()<<fileName;
            newFile =new QFile(fileName);
            newFile->open(QFile::WriteOnly);
            qDebug()<<"0000000";
        }
        else
        {
        inBlock=receivedSocket->readAll();
        byteReceived+=inBlock.size();
        newFile->write(inBlock);
        newFile->flush();
        qDebug()<<"++++++";
        }
        if(byteReceived==totalSize)
        {
        inBlock.clear();
        byteReceived=0;
        totalSize=0;
        qDebug()<<"---------";
        }

    }
    void FileServer::on_serverButton_clicked()
    {
        totalSize=0;
        byteReceived=0;
        server=new QTcpServer(this);
        server->listen(QHostAddress("127.0.0.1"),4096);
        connect(server,SIGNAL(newConnection()),this,SLOT(acceptConnection()));
        ui->receivedStatusLabel->setText(tr("开始监听..."));
    }
