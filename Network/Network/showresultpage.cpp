#include "showresultpage.h"
#include "ui_showresultpage.h"

ShowResultPage::ShowResultPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowResultPage)
{
    ui->setupUi(this);
}
void ShowResultPage::setOkButtonMsg(QString msg)
{
ui->okButton->setText(msg);
}
void ShowResultPage::setCancelButtonMsg(QString msg)
{
ui->cancleButton->setText(msg);
}
void ShowResultPage::setResultButtonMsg(QString msg)
{
ui->label->setText(msg);
}

ShowResultPage::~ShowResultPage()
{
    delete ui;
}

void ShowResultPage::on_okButton_clicked()
{
    close();
}

void ShowResultPage::on_cancleButton_clicked()
{
    close();
}
