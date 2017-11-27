#include "chatpage.h"
#include "ui_chatpage.h"
#include "addfriend.h"
#include "setuppage.h"
ChatPage::ChatPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChatPage)
{
    ui->setupUi(this);
    QString *headPath=new \
            QString("/home/younger/桌面/Network/Network/head.png");
    QPixmap *headPix=new QPixmap(*headPath);
    *headPix=headPix->scaled(\
                ui->headLable->size());
    ui->headLable->setPixmap(*headPix);
    QString *addPath=new \
            QString("/home/younger/桌面/Network/Network/add.png");
    QPixmap *addPix=new QPixmap(*addPath);
    *addPix=addPix->scaled(\
                ui->addButton->size());
    ui->addButton->setIcon(QIcon(*addPix));


}

ChatPage::~ChatPage()
{
    delete ui;
}

void ChatPage::on_addButton_clicked()
{
    addFriend *add=new addFriend();
    add->setAttribute(Qt::WA_DeleteOnClose);
    add->show();
}


void ChatPage::on_setupButton_clicked()
{
    SetupPage *setup=new SetupPage();
    setup->setAttribute(Qt::WA_DeleteOnClose);
    setup->show();
}
