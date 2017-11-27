#include "addfriend.h"
#include "ui_addfriend.h"

addFriend::addFriend(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addFriend)
{
    ui->setupUi(this);
}

addFriend::~addFriend()
{
    delete ui;
}

void addFriend::on_addFriendButton_clicked()
{

}
