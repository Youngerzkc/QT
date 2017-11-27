#ifndef REGISTERPAGE_H
#define REGISTERPAGE_H

#include <QDialog>

namespace Ui {
class RegisterPage;
}

class RegisterPage : public QDialog
{
    Q_OBJECT
    
public:
    explicit RegisterPage(QWidget *parent = 0);
    ~RegisterPage();

    
private slots:
    void on_pushButton_clicked();

private:
    Ui::RegisterPage *ui;
};

#endif // REGISTERPAGE_H
