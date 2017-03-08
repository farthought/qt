#ifndef SETBIRTHDAY_H
#define SETBIRTHDAY_H

#include <QDialog>
#include <QDateEdit>

class SetBirthday : public QDialog
{
    Q_OBJECT
public:
    explicit SetBirthday(QWidget *parent = 0);

signals:
    void send_date(const QDate &birthday);

private slots:
    virtual void accept();

private:
    QDateEdit *birthdayDateEdit;
};

#endif // SETBIRTHDAY_H
