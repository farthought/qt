#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_loginButton_clicked()
{
    if(ui->usrlineEdit->text().trimmed() == tr("gengshixin")
            && ui->pwdlineEdit->text() == tr("123456"))
    {
        accept();
    }
    else
    {
        QMessageBox::warning(this,tr("Waring"),
                             tr("user name or password error!"),
                             QMessageBox::Yes);
        ui->usrlineEdit->clear();
        ui->pwdlineEdit->clear();
        ui->usrlineEdit->setFocus();
    }
}
