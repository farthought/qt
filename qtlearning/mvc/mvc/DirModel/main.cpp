#include "dirmodel.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DirModel w;
    w.show();

    return a.exec();
}
