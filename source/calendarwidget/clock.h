#ifndef CLOCK_H
#define CLOCK_H

#include <QWidget>
#include <QDialog>

class Clock : public QDialog
{
    Q_OBJECT
public:
    explicit Clock(QWidget *parent = 0);

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // CLOCK_H
