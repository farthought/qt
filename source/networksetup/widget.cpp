#include "widget.h"
#include <QApplication>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    initWidget();
    connect (combox, SIGNAL(currentIndexChanged(int)),this, SLOT(languageCBoxChanged()));
	connect (button_Read, SIGNAL(clicked()), this, SLOT(on_button_Read_clicked()));
	connect (button_Save, SIGNAL(clicked()), this, SLOT(on_button_Save_clicked()));
	connect (button_Exit, SIGNAL(clicked()), this, SLOT(on_button_Exit_clicked()));
//	connect (button_Addcol,SIGNAL(clicked()), this, SLOT(on_button_Addcol_clicked()));
//	connect (button_Addrow, SIGNAL(clicked()), this, SLOT(on_button_Addrow_clicked()));

    connect (button_Ipcfg, SIGNAL(clicked()), this, SLOT(on_button_Ipcfg_clicked()));

    this->setLayout(V1);

}

Widget::~Widget()
{

}

void Widget::initWidget()
{
    filename.clear();
    isSaved = 0;

    translator = new QTranslator(0);
    translator->load(":/ipcfg.qm");
    this->resize(600,400);
    label_fineName = new QLabel(tr("NO File!"));
    tableView = new QTableView();
    button_Read = new QPushButton(tr("Load"));
    button_Save = new QPushButton(tr("Save")),
    button_Exit = new QPushButton(tr("Exit"));
    button_Addcol = new QPushButton(tr("Col"));
    button_Addrow = new QPushButton(tr("Row"));
    button_Ipcfg = new QPushButton(tr("Card"));
    combox = new QComboBox(this);

    button_Read->setMinimumSize(10,5);
    button_Save->setMinimumSize(10,5);
    button_Exit->setMinimumSize(10,5);

    button_Addcol->setMinimumSize(10,5);
    button_Addrow->setMinimumSize(10,5);
    combox->addItem(tr("Chinese"));
    combox->addItem(tr("English"));
    combox->addItem(tr("Korean"));
    label_fineName->resize(600,20);
    V1 = new QVBoxLayout();
    H1 = new QHBoxLayout();
    H2 = new QHBoxLayout();

    model = new QStandardItemModel(tableView);

    H1->addWidget(button_Read);
    H1->addWidget(button_Save);
    H1->addWidget(button_Ipcfg);
//  H1->addWidget(button_Addrow)
//	H1->addWidget(button_Addcol);
    H1->addWidget(button_Exit);
    H1->addWidget(combox);

    label_fineName->resize(600,20);
    H2->addWidget(label_fineName);
    H2->addLayout(H1);


    V1->addWidget(tableView);
    V1->addLayout(H2);

    this->setWindowTitle(tr("Network settings"));
    qApp->installTranslator(translator);
//    this->retranslate();
    this->show();
}

void Widget::retranslate()
{
    label_fineName->setText(tr("NO File!"));
    button_Read->setText(tr("Load"));
    button_Exit->setText(tr("Exit"));
    button_Save->setText(tr("Save"));
    button_Ipcfg->setText(tr("Card"));
    combox->setItemText(0,tr("Chinese"));
    combox->setItemText(1,tr("English"));
    combox->setItemText(2,tr("Korean"));
    this->setWindowTitle(tr("Network settings"));
}

void Widget::changeEvent(QEvent* event)
{
    if(event->type() == QEvent::LanguageChange) {
        this->retranslate();
        //this->ui->retranslateUi(this); //当程序中使用ui文件时，ui文件用此函数切换语言
    } else
    QWidget::changeEvent(event);
}

void Widget::model_init()
{
	//设置表头

	model->setColumnCount(2);

    model->setHeaderData(0,Qt::Horizontal,QString(tr("Params ")));

    model->setHeaderData(1,Qt::Horizontal,QString(tr("Value")));

	tableView->setModel(model);

	//表头信息显示居左
	tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);

	//设置列宽
	tableView->setColumnWidth(0,200);

    tableView->setColumnWidth(1,300);
}

void Widget::on_button_Read_clicked()
{
    filename = QFileDialog::getOpenFileName(this,tr("Open profile"), "/etc/sysconfig/network-scripts/ifcfg-Wired_connection_1", tr("profile(*.ini)"));
	if (0 == filename.length()) {
        QMessageBox::information(NULL, tr("Profile"), tr("You didn't select any files."),tr("Ok"));
        label_fineName->setText(tr("NO file!"));
		return ;
	} else {
		//QMessageBox::information(NULL, tr("Profile"), tr("You selected ") + filename);
		label_fineName->setText(filename);
	}
	model->clear();
	model_init();
	isSaved = 0;

	QSettings *configIniRead = new QSettings(filename, QSettings::IniFormat);

	QStringList Keylist = configIniRead->allKeys();

	QStringList valueList;
	int x = 0;
	int y = 0;
	foreach (QString str, Keylist) {
		y = 0;
		model->setItem(x, y, new QStandardItem(QString(str).right(str.length() - str.indexOf('/') -1 )));

		valueList = configIniRead->value(str).toStringList();
		foreach (QString str2, valueList) {
			y++;
			model->setItem(x, y, new QStandardItem(QString(str2)));
		}
		x++;
		//qDebug()<<str<<valueList;
	}

	//读入入完成后删除指针
	delete configIniRead;
}

void Widget::on_button_Save_clicked()
{

    QString section("network settings");
	QString Key;
	QStringList ValueList;
	int column = 1;
    QString newFilename = QString("/etc/sysconfig/network-scripts/ifcfg-Wired_connection_1");
    filename = QFileDialog::getSaveFileName(this,tr("Save profile"), newFilename, tr("profile(*.ini)"));
	if (filename.isNull()) {
		return ;
	}

	QSettings *configIniSave = new QSettings(filename, QSettings::IniFormat);
	configIniSave->clear();
    configIniSave->beginGroup(section);
	//qDebug()<<model->rowCount()<<model->columnCount();


	for (int row =0 ;row < model->rowCount(); row++){
		//qDebug()<<"-----"<<model->item(row, 0)->text();
		Key.clear();
		ValueList.clear();
		Key = model->item(row,0)->text();
		if (Key.isNull())
			continue;
		column = 1;
		while ( column < model->columnCount()){
			if (model->item(row, column) == NULL)
				break;
			else
				ValueList.append(model->item(row, column)->text());
			column++;
		}

		configIniSave->setValue(Key, ValueList);
	}
	configIniSave->endGroup();
	delete configIniSave;
	isSaved = 1;
	label_fineName->setText(filename);
}

void Widget::on_button_Exit_clicked()
{
    if (isSaved == 0) {
        int ret = QMessageBox::information(this,tr("Not Save"), tr("Don't save and Exit?"),tr("Save"), tr("Yes"),tr("No") );
		switch (ret) {
            case 0:
				on_button_Save_clicked();
				break;
            case 1:
				this->close();
				break;
            case 2:
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
    qDebug()<<model->columnCount();
}

void Widget::on_button_Ipcfg_clicked()
{
    cardProcess = new QProcess(this);
    connect(cardProcess, SIGNAL(readyReadStandardOutput()),this, SLOT(readFromStdOut()));
    cardProcess->start("/usr/local/bin/cardcfg");

}

void Widget::readFromStdOut()
{
    cardText = cardProcess->readAllStandardOutput();
    QMessageBox::information(this,tr("Network card information"),cardText ,tr("yes"));
}

void Widget::languageCBoxChanged()
{
    translator = new QTranslator(qApp);

    switch(combox->currentIndex())
    {
    case 0:
        qApp->removeTranslator(translator);
        qDebug() << "Chinese";
        translator->load(":/ipcfg.qm");
        qDebug() << "right";
        break;
    case 1:
        qApp->removeTranslator(translator);
        qDebug() << "English";
        translator->load(":/ipcfg_english.qm");
        qDebug() << "right";
        break;
    case 2:
        qApp->removeTranslator(translator);
        qDebug() << "Korean";
        translator->load(":/ipcfg_ko.qm");
        qDebug() << "right";
        break;
    }
    qApp->installTranslator(translator);
//    this->retranslate();
}

void Widget::on_button_Addrow_clicked()
{
	if (model->columnCount()==0)
		model_init();
	model->insertRow(model->rowCount());
	qDebug()<<model->rowCount();
}
