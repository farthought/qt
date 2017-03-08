#include "displaybutton.h"

DisplayButton::DisplayButton(QWidget *parent) :
    QToolButton(parent)
{
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    setToolButtonStyle(Qt::ToolButtonIconOnly);
    setAutoRaise(true);
}

QSize DisplayButton::sizeHint() const
{
    QSize _NewSize = QToolButton::sizeHint();
    _NewSize.rheight() += 6;
    _NewSize.rwidth() += 1;
    return _NewSize;
}
