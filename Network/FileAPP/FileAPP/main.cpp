#include <QApplication>
#include "fileclient.h"
#include <QTextCodec>
int main(int argc, char *argv[])
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");//情况2
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QApplication a(argc, argv);
    FileClient w;
    w.show();
    
    return a.exec();
}
