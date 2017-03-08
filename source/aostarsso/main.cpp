#include "adaemon.h"
#include <QApplication>
#include <QtSingleApplication>
#include <QTextCodec>
#include <QMessageBox>
#include "common.h"


int main(int argc, char *argv[])
{
    QtSingleApplication app(argc, argv);
    if (app.isRunning())
        return 0;
    QTranslator *translator = new QTranslator(qApp);
    translator->load(":/qt_zh_CN.qm");
    qApp->installTranslator(translator);

    myHelper::SetUTF8Code();
    QApplication::setQuitOnLastWindowClosed(false);
    ADaemon daemon;
    daemon.startDaemon();


    return app.exec();
}
