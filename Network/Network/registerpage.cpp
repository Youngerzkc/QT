#include "registerpage.h"
#include "ui_registerpage.h"
#include "showresultpage.h"
RegisterPage::RegisterPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterPage)
{
    ui->setupUi(this);
}

RegisterPage::~RegisterPage()
{
    delete ui;
}

void RegisterPage::on_pushButton_clicked()
{
    ShowResultPage *showResultPage=new ShowResultPage();
    showResultPage->setAttribute(Qt::WA_DeleteOnClose);
    showResultPage->setOkButtonMsg(QString("马上登录"));
    showResultPage->setCancelButtonMsg(QString("再来一次"));
    showResultPage->setResultButtonMsg("注册成功");
    showResultPage->show();
}
