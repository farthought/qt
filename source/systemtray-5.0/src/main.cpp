#include "widget.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); 
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));
    if (argc < 3)
    {
        qDebug() << "Usage:systemtray argv[1] argv[2] argv[3] argv[4] argv[5]";
        return -1;
    }
    Widget w(argv[1], argv[2], argv[3], argv[4], argv[5]);
    w.hide();

    return a.exec();
}
