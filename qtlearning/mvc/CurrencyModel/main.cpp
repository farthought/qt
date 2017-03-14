#include "currencymodel.h"
#include <QApplication>
#include <QTableView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMap<QString, double> data;
    data["NOK"] = 1.0000;
    data["NZD"] = 0.2254;
    data["SEK"] = 1.1991;
    data["SGD"] = 0.2592;
    data["USD"] = 0.1534;

    CurrencyModel *model = new CurrencyModel;
    model->setCurrencyMap(data);

    QTableView *view = new QTableView;
    view->setModel(model);
    view->resize(800, 400);
    view->show();

    return a.exec();
}
