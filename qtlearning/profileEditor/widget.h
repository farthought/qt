#ifndef WIDGET_H
#define WIDGET_H

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

struct _key {
	QString section;
	QString key;
	QList<int> valuelist;
};
typedef QList<struct _key> KEYLIST;

class Widget : public QWidget
{
	Q_OBJECT

public:
	Widget(QWidget *parent = 0);
	~Widget();

	//widget
	QLabel *label_fineName;
	QTableView *tableView;
	QPushButton *button_Read, *button_Save, *button_Exit;

	QPushButton *button_Addrow, *button_Addcol;

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
private:

private slots:
	void on_button_Read_clicked();
	void on_button_Save_clicked();
	void on_button_Exit_clicked();
	void on_button_Addrow_clicked();
	void on_button_Addcol_clicked();
};

#endif // WIDGET_H
