#ifndef QTHREADREAD_H
#define QTHREADREAD_H

#include <QThread>

class QthreadRead : public QThread
{
    Q_OBJECT
public:
    explicit QthreadRead(QObject *parent = 0);
 private:
    void run();
signals:
    
public slots:
    
};

#endif // QTHREADREAD_H
