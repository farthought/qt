#ifndef CITYMODEL_H
#define CITYMODEL_H

#include <QAbstractTableModel>

class CityModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    CityModel(QAbstractTableModel *parent = 0);
    ~CityModel();
    void setCities(const QStringList &cityNames);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

private:
    int offsetOf(int row, int column) const;

    QStringList cities;
    QVector<int> distances;
};

#endif // CITYMODEL_H
