#ifndef DIRMODEL_H
#define DIRMODEL_H

#include <QWidget>
#include <QFileSystemModel>
#include <QTreeView>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QMessageBox>

class DirModel : public QWidget
{
    Q_OBJECT

public:
    DirModel(QWidget *parent = 0);
    ~DirModel();
private:
    QFileSystemModel *model;
    QTreeView *treeView;
private slots:
    void mkdir();
    void rm();
};

#endif // DIRMODEL_H
