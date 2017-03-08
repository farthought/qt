#ifndef STATICBUTTON_H
#define STATICBUTTON_H


#include <QAbstractButton>
class QLabel;
typedef enum{
    BUTTON_FIRST,
    BUTTON_SCALED,
    BUTTON_ENTER,
    BUTTON_LEAVE,
    BUTTON_PRESSED,
    BUTTON_DISABLE
}BUTTONSTATUS;

class StaticButton : public QAbstractButton
{
    Q_OBJECT
public:
    explicit StaticButton(QWidget *parent = 0);
    explicit StaticButton(const QString &icon,int num = 4, QWidget *parent = 0); //默认为一张图片的icon
    explicit StaticButton(const QString &icon,bool isDivision, int num = 3, QWidget *parent = 0);
    void setOneButtonInfo(const QString &icon,int num = 4);
    void setDivisionButtonInfo(const QString &icon,int num = 3);
    void setCursorEnabled(bool enalbed);
    void setButtonStatus(BUTTONSTATUS status);
    /*!
     * \brief 设置按钮文字，用于用图片做背景
     * \param text
     */
    void setButtonText(const QString &text);
    /*!
     * \brief 对button中的text设置样式表
     * \param style
     */
    void setTextStyle(const QString &style);
signals:
    void buttonClicked();
    void enterSignal();
    void leaveSignal();
protected:
    void paintEvent(QPaintEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void changeEvent(QEvent *e);
private:
    void addTextLabel();
private:
    QPixmap m_currentPix;
    QList<QPixmap> m_pixList;
    int m_num;
    QCursor m_preCursor;
    bool m_isCursor;
    QLabel  *m_textLabel;
};

#endif // STATICBUTTON_H
