#ifndef SHOWRESULTPAGE_H
#define SHOWRESULTPAGE_H

#include <QDialog>

namespace Ui {
class ShowResultPage;
}

class ShowResultPage : public QDialog
{
    Q_OBJECT
    
public:
    explicit ShowResultPage(QWidget *parent = 0);
    ~ShowResultPage();
    void setOkButtonMsg(QString msg);
    void setCancelButtonMsg(QString msg);
    void setResultButtonMsg(QString msg);
private slots:
    void on_okButton_clicked();

    void on_cancleButton_clicked();

private:
    Ui::ShowResultPage *ui;
};

#endif // SHOWRESULTPAGE_H
