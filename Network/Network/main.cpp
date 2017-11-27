#include <QApplication>
#include "login.h"
#include"QTextCodec"
int main(int argc, char *argv[])
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");//情况2
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QApplication a(argc, argv);
    Login w;
    w.show();
    
    return a.exec();
}
