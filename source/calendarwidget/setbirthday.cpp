#include "setbirthday.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

SetBirthday::SetBirthday(QWidget *parent) :
    QDialog(parent)
{
    QLabel* birthdayLabel = new QLabel(tr("birthday:"));

    birthdayDateEdit = new QDateEdit(QDate::currentDate(), this);
    birthdayDateEdit->setDisplayFormat("yyyy-MM-dd");
    QHBoxLayout* editLayout = new QHBoxLayout;
    editLayout->addWidget(birthdayLabel);
    editLayout->addWidget(birthdayDateEdit);

    QPushButton* okBtn = new QPushButton(tr("ok"));
    QPushButton* cancelBtn = new QPushButton(tr("cancle"));
    QHBoxLayout* btnLayout = new QHBoxLayout;
    btnLayout->setSpacing(20);
    btnLayout->addWidget(okBtn);
    btnLayout->addWidget(cancelBtn);

    QVBoxLayout* dlgLayout = new QVBoxLayout;
    dlgLayout->setMargin(10);
    dlgLayout->addLayout(editLayout);
    dlgLayout->addStretch(10);
    dlgLayout->addLayout(btnLayout);
    setLayout(dlgLayout);

    connect(okBtn, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelBtn, SIGNAL(clicked()), this, SLOT(reject()));

    setWindowTitle(tr("set_birthday"));
    resize(200, 100);
}
void SetBirthday::accept()
{
    // 发射信号，将行内容发射出去
    emit send_date(birthdayDateEdit->date());
    QDialog::accept();
}
