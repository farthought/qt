#ifndef PROFILEEDITOR_H
#define PROFILEEDITOR_H

#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QDebug>
#include <QTableView>
#include <QPushButton>
#include <QList>
#include <QChar>
#include <QString>
#include <QSettings>
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QCloseEvent>

struct _key {
    QString section;
    QString key;
    QString valuelist;
};
typedef QList<struct _key> KEYLIST;

class ProfileEditor : public QWidget
{
    Q_OBJECT

public:
    explicit ProfileEditor(QWidget *parent = 0);
    ~ProfileEditor();

    //widget
    QLabel *label_fineName;
    QTableView *tableView;
    QPushButton *button_Read, *button_Save, *button_Exit;
    QPushButton *button_Addrow, *button_help;

    //model
    QStandardItemModel  *model;

    //file
    QString filename;
    //model
    void model_init();

    //parse, the QSettings API 'allKeys' get a QStringList was been sort,
    // i can't avoid the sort,so i rewrite a parse function
    void parse(QString filename, KEYLIST *keys);

    //flag
    int isSaved;

    void widgetClose();
    void profiledraw();

protected:
    void closeEvent(QCloseEvent *e);

signals:
    void ProfileEditorActivate();

private slots:
    void on_button_Read_clicked();
    void on_button_Save_clicked();
    void on_button_Exit_clicked();
    void on_button_Addrow_clicked();
    void on_button_help_clicked();
};

#endif // PROFILEEDITOR_H
