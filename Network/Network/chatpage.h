#ifndef CHATPAGE_H
#define CHATPAGE_H

#include <QDialog>

namespace Ui {
class ChatPage;
}

class ChatPage : public QDialog
{
    Q_OBJECT
    
public:
    explicit ChatPage(QWidget *parent = 0);
    ~ChatPage();
    
private slots:
    void on_addButton_clicked();

    void on_setupButton_clicked();

private:
    Ui::ChatPage *ui;
};

#endif // CHATPAGE_H
