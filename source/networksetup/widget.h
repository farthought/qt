#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QDebug>
#include <QTableView>
#include <QPushButton>
#include <QString>
#include <QSettings>
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QProcess>
#include <QComboBox>
#include <QTranslator>

class Widget : public QWidget
{
	Q_OBJECT

public:
    Widget(QWidget *parent = 0);
	~Widget();

    //widget
    QTranslator * translator;
	QLabel *label_fineName;
	QTableView *tableView;
	QPushButton *button_Read, *button_Save, *button_Exit;

    QPushButton *button_Addrow, *button_Addcol, *button_Ipcfg;


	QStandardItemModel  *model;
	//file
	QString filename;
    QString cardText;
    QProcess * cardProcess;
    QComboBox *combox;
    QVBoxLayout *V1;
    QHBoxLayout *H1;
    QHBoxLayout *H2;
	//model
	void model_init();

	//flag
    int isSaved;
    void initWidget();
    void retranslate();
protected:
    void changeEvent(QEvent *event);
private:
    Widget *ui;

private slots:
	void on_button_Read_clicked();
	void on_button_Save_clicked();
	void on_button_Exit_clicked();
	void on_button_Addrow_clicked();
	void on_button_Addcol_clicked();
    void on_button_Ipcfg_clicked();
    void readFromStdOut();
    void languageCBoxChanged();
};

#endif // WIDGET_H
