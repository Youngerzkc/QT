#include "login.h"
#include "ui_login.h"
#include"QPixmap" //图像的类
#include "QDebug"
#include "chatpage.h"
#include "registerpage.h"
Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    ///home/younger/桌面/Network/Network/logo.png
    //header.png
    QString *logoPath=new \
    QString("/home/younger/桌面/Network/Network/logo.png");
    QPixmap *pix=new QPixmap(*logoPath);
    int w=ui->logLable->width();
    int h=ui->logLable->height();
    *pix=pix->scaled(w,h);
    ui->logLable->setPixmap(*pix);
    QString *logoPath1=new \
            QString("/home/younger/桌面/Network/Network/header.png");
   qDebug()<<*logoPath;
    QPixmap *pix1=new QPixmap(*logoPath1);
    w=ui->headLable->width();
    h=ui->headLable->height();
     *pix1=pix1->scaled(w,h);
    ui->headLable->setPixmap(*pix1);
     move(0,0);
}

Login::~Login()
{
    delete ui;
}

void Login::on_registerButton_clicked()
{
    RegisterPage *registerPage=new RegisterPage();
    registerPage->setAttribute(Qt::WA_DeleteOnClose);
    registerPage->show();
}


void Login::on_loginButton_clicked()
{
    ChatPage *chatPage=new ChatPage();
    chatPage->setAttribute(Qt::WA_DeleteOnClose);
    chatPage->show();
    close();
}
