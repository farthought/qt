#include "widget.h"

Widget::Widget(QWidget *parent)
	: QWidget(parent)
{

	filename.clear();
	isSaved = 0;

	this->resize(1024,768);


	label_fineName = new QLabel("NO File!");
	tableView = new QTableView();
	button_Read = new QPushButton("Load");
	button_Save = new QPushButton("Save"),
	button_Exit = new QPushButton("Exit");
	button_Addcol = new QPushButton("Col");
	button_Addrow = new QPushButton("Row");

	model = new QStandardItemModel(tableView);
	QVBoxLayout *V1 = new QVBoxLayout();
	QHBoxLayout *H1 = new QHBoxLayout();
	QHBoxLayout *H2 = new QHBoxLayout();

	button_Read->setMinimumSize(10,5);
	button_Save->setMinimumSize(10,5);
	button_Exit->setMinimumSize(10,5);

	button_Addcol->setMinimumSize(10,5);
	button_Addrow->setMinimumSize(10,5);


	H1->addWidget(button_Read);
	H1->addWidget(button_Save);
	H1->addWidget(button_Addrow);
	H1->addWidget(button_Addcol);
	H1->addWidget(button_Exit);

	label_fineName->resize(600,20);
	H2->addWidget(label_fineName);
	H2->addLayout(H1);


	V1->addWidget(tableView);
	V1->addLayout(H2);



	connect (button_Read, SIGNAL(clicked()), this, SLOT(on_button_Read_clicked()));
	connect (button_Save, SIGNAL(clicked()), this, SLOT(on_button_Save_clicked()));
	connect (button_Exit, SIGNAL(clicked()), this, SLOT(on_button_Exit_clicked()));
	connect (button_Addcol,SIGNAL(clicked()), this, SLOT(on_button_Addcol_clicked()));
	connect (button_Addrow, SIGNAL(clicked()), this, SLOT(on_button_Addrow_clicked()));


	this->setLayout(V1);
	this->show();
}

Widget::~Widget()
{

}


void Widget::model_init()
{
	//设置表头

	model->setColumnCount(2);

	model->setHeaderData(0,Qt::Horizontal,QString("Params "));

	model->setHeaderData(1,Qt::Horizontal,QString("Value"));

	tableView->setSortingEnabled(false);

	//model->setSortRole(Qt::DecorationRole);


	tableView->setModel(model);

	//表头信息显示居左
	tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);


	//设置列宽
	tableView->setColumnWidth(0,200);

	tableView->setColumnWidth(1,100);
}

void Widget::on_button_Read_clicked()
{
	//QString section("FPGA3");
	filename = QFileDialog::getOpenFileName(this,tr("Open profile"), ".", tr("profile(*.ini)"));
	if (0 == filename.length()) {
		QMessageBox::information(NULL, tr("Profile"), tr("You didn't select any files."));
		label_fineName->setText("NO file!");
		return ;
	} else {
		//QMessageBox::information(NULL, tr("Profile"), tr("You selected ") + filename);
		label_fineName->setText(filename);
	}

	model->clear();
	model_init();
	isSaved = 0;

	//added by jiawentao ,new method to read ini file
	KEYLIST keys;
	int x = 0;
	int y = 0;
	parse(filename, &keys);
	for (x = 0; x != keys.size(); x++) {
		y = 0;
		model->setItem(x, y, new QStandardItem(keys[x].key));
		qDebug()<<"y:"<<y<<"->"<<keys[x].key;
		foreach (int value, keys[x].valuelist) {
			y++;
			model->setItem(x, y, new QStandardItem(QString::number(value)));
			qDebug()<<"y:"<<y<<"->"<<value;
		}
	}

//	QSettings *configIniRead = new QSettings(filename, QSettings::IniFormat);


//	QStringList Keylist = configIniRead->allKeys();

//	QStringList valueList;
//	QStringList::Iterator it1,it2;
//	QString str1, str2;
//	int x = 0;
//	int y = 0;

//	//foreach (QString str, Keylist) {
//	//for(it1 = Keylist.begin(); it1 != Keylist.end(); it1++) {
//	for (int i = 0; i < Keylist.size(); i++) {

//		y = 0;
//		//str1 = *it1;
//		str1 = Keylist[i];
//		model->setItem(x, y, new QStandardItem(QString(str1).right(str1.length() - str1.indexOf('/') -1 )));

//		valueList = configIniRead->value(str1).toStringList();
//		//foreach (QString str2, valueList) {
//		for (it2 = valueList.begin(); it2 != valueList.end(); it2++) {
//			y++;
//			str2 = *it2;
//			model->setItem(x, y, new QStandardItem(QString(str2)));
//		}
//		x++;
//		qDebug()<<str1<<valueList;
//	}

//	//读入入完成后删除指针
//	delete configIniRead;
}

void Widget::on_button_Save_clicked()
{

	QString section("FPGA3");
	QString Key;
	QStringList ValueList;
	int column = 1;

	filename = QFileDialog::getSaveFileName(this,tr("Save profile"), filename, tr("profile(*.ini)"));
	if (filename.isNull()) {
		return ;
	}

	QSettings *configIniSave = new QSettings(filename, QSettings::IniFormat);
	configIniSave->clear();
	configIniSave->beginGroup(section);

	for (int row =0 ;row < model->rowCount(); row++) {
		//qDebug()<<"-----"<<model->item(row, 0)->text();
		int sum = 0;
		Key.clear();
		ValueList.clear();
		if (model->item(row, 0) == NULL)
			continue;
		if (model->item(row,0)->text().isNull())
			continue;
		Key = model->item(row,0)->text();
		for (column = 1; column < model->columnCount(); column++){
			if (model->item(row, column) == NULL || model->item(row, column)->text().isEmpty() || model->item(row, column)->text() == "\r\n")
				continue;
			else
				sum++, ValueList.append(model->item(row, column)->text());
		}
		if (sum == 0)
			continue;

		qDebug()<<"save"<<Key<<ValueList;
		configIniSave->setValue(Key, ValueList);
	}
	configIniSave->endGroup();

	delete configIniSave;
	configIniSave = NULL;

	isSaved = 1;
	label_fineName->setText(filename);
}

void Widget::on_button_Exit_clicked()
{
	if (isSaved == 0) {
		int ret = QMessageBox::information(this,"Not Save", "Don't save and Exit?",QMessageBox::Save, QMessageBox::Yes,QMessageBox::No );
		switch (ret) {
			case QMessageBox::Save:
				on_button_Save_clicked();
				break;
			case QMessageBox::Yes:
				this->close();
				break;
			case QMessageBox::No:
				break;
			default:
				break;
		}
	} else {
		this->close();
	}
}

void Widget::on_button_Addcol_clicked()
{
	if (model->columnCount()==0)
		model_init();
	model->insertColumn(model->columnCount());
	//qDebug()<<model->columnCount();
}

void Widget::on_button_Addrow_clicked()
{
	if (model->columnCount()==0)
		model_init();
	model->insertRow(model->rowCount());
	//qDebug()<<model->rowCount();
}


void Widget::parse(QString filename, KEYLIST *keys)
{

	QString curLine;
	QString section;

	struct _key tmpKey;

	int sum = 0;
	QFile *ini = new QFile(filename);
	if (!ini->open(QFile::ReadOnly)){
		qDebug()<<"Open file error!";
		return ;
	}

	while(!ini->atEnd()){

		curLine = QString (ini->readLine());
		qDebug()<<"Current Line :"<<curLine;

		//section,such as "[FPGA3]"
		if (curLine.contains('[') && curLine.contains(']')){
			section = curLine.right(curLine.size() - curLine.indexOf('[') - 1) ;
			section = section.left(section.lastIndexOf(']') - 1 );
			qDebug()<<"get section"<<section;
			continue;
		}

		//Key,values
		if (curLine.contains('=')) {

			tmpKey.section = section;
			tmpKey.valuelist.clear();

			tmpKey.key = curLine.split('=').first();
			if (tmpKey.key.isEmpty())
				continue;

			//',' 逗号作为分隔符
			if (curLine.size() - tmpKey.key.size() - 1 <=0)
				continue;

			QStringList tmp = curLine.right(curLine.size() - tmpKey.key.size() - 1).split(',');
			if (tmp.isEmpty() || tmp.first() == "\r\n" ||tmp.first() == "\n") {
				continue;
			}
			//只保留数字，过滤其它字符
			foreach (QString s, tmp) {
				QString num;
				for (int index = 0; index < s.size(); index++) {
					if (s[index].isDigit())
						num.append(s[index]);
				}
				tmpKey.valuelist.append(num.toLong());
			}

			keys->append(tmpKey);
			qDebug()<<keys->value(sum).section<<keys->value(sum).key<<keys->value(sum).valuelist;
			sum++;
		}

	}
	ini->close();

	return ;
}
