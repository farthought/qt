#include "sortfilterproxy.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SortFilterProxy w;
    w.show();

    return a.exec();
}
