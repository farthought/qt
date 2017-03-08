#include "widget.h"
#include <QApplication>
#include <QTextCodec>
#include <QTranslator>
#include <QIcon>
#include <QString>

int main(int argc, char *argv[])
{

//    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
//    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
//    QTextCodec * codec = QTextCodec::codecForName("UTF-8");
//    QString  *e = new QString(QString::fromLatin1("我是汉字"));
//    QString  *f = new QString(QString::fromLocal8Bit("我是汉字"));
//    QString  *g = new QString("\xce\xd2\xca\xc7\xba\xba\xd7\xd6");
//    QString  *h = new QString("\xe6\x88\x91\xe6\x98\xaf\xe6\xb1\x89\xe5\xad\x97");
//    QString  *i = new QString(codec->toUnicode("我是汉字"));
//    qDebug() << *e << *f << *g << *h << *i;

	QApplication a(argc, argv);

//    QTranslator translator(0);
//    QTranslator *translator = new QTranslator(0);
//    translator.load(":/ipcfg.qm");
//    translator->load(":/ipcfg.qm");
//    a.installTranslator(&translator);
//    a.installTranslator(translator);
//    qApp->installTranslator(translator);

    Widget w;
    QIcon icon = QIcon(":/icon/network-wired.png");
    w.setWindowIcon(icon);

	return a.exec();
}
