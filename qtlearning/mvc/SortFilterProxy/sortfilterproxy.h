#ifndef SORTFILTERPROXY_H
#define SORTFILTERPROXY_H

#include <QWidget>
#include <QListView>
#include <QStringListModel>
#include <QSortFilterProxyModel>
#include <QComboBox>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>


class SortFilterProxy : public QWidget
{
    Q_OBJECT

public:
    SortFilterProxy(QWidget *parent = 0);
    ~SortFilterProxy();
private slots:
    void filterChanged(QString text);
private:
    QListView *view;
    QStringListModel *model;
    QSortFilterProxyModel *modelProxy;
    QComboBox *syntaxBox;

};

#endif // SORTFILTERPROXY_H
