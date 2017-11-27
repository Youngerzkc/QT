#include "dialog.h"
#include "ui_dialog.h"
#include "qthreadread.h"
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QthreadRead *thread=new QthreadRead();
    thread->start();
}

Dialog::~Dialog()
{
    delete ui;
}
