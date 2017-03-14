#include "citymodel.h"
#include <QApplication>
#include <QTableView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QStringList cities;
    cities << "Arvika" << "Boden" << "Eskilstuna" << "Falun";

    CityModel cityModel;
    cityModel.setCities(cities);

    QTableView tableView;
    tableView.setModel(&cityModel);
    tableView.setAlternatingRowColors(true);
    tableView.setWindowTitle(QObject::tr("Cities"));
    tableView.resize(600,300);
    tableView.show();
    return a.exec();
}
