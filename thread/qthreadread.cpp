#include "qthreadread.h"
#include <QDebug>
extern "C" {
#include <stdio.h>
}
QthreadRead::QthreadRead(QObject *parent) :
    QThread(parent)
{

}
void QthreadRead::run()
{
    while(1)
    {
    ::sleep(2);
        qDebug()<<"New Thread --->Hello ";
    }
}
