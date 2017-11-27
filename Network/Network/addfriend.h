#ifndef ADDFRIEND_H
#define ADDFRIEND_H

#include <QDialog>

namespace Ui {
class addFriend;
}

class addFriend : public QDialog
{
    Q_OBJECT
    
public:
    explicit addFriend(QWidget *parent = 0);
    ~addFriend();
    
private slots:
    void on_addFriendButton_clicked();

private:
    Ui::addFriend *ui;
};

#endif // ADDFRIEND_H
