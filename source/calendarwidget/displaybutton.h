#ifndef DISPLAYBUTTON_H
#define DISPLAYBUTTON_H

#include <QToolButton>
#include <QSize>

class DisplayButton : public QToolButton
{
    Q_OBJECT
public:
    explicit DisplayButton(QWidget *parent = 0);

signals:

public slots:

protected:
    QSize sizeHint() const;
};

#endif // DISPLAYBUTTON_H
