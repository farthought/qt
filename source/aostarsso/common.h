#ifndef COMMON_H
#define COMMON_H
#include <QtCore>
#include <QTextCodec>
#include <QWidget>
#include <QDesktopWidget>
#define USER_INI    "/.config/isoft/user.ini"

class myHelper: public QObject
{

public:

    static QMap<QString,QString> readGroupConfig(const QString &path, const QString &group)
    {
        QMap<QString,QString> tempInfo;
        QSettings *config = new QSettings(path, QSettings::IniFormat);
        config->beginGroup(group);
        QStringList keys = config->allKeys();
        foreach (QString key, keys) {
            tempInfo.insert(key, config->value(key).toString());
        }
        config->endGroup();
        delete config;
        return tempInfo;
    }


    static void writeGroupConfig(const QString &path, const QString &group,
                                 const QMap<QString,QString> &info)
    {
        QSettings *config = new QSettings(path, QSettings::IniFormat);
        config->beginGroup(group);
        foreach (QString key, info.keys()) {
            config->setValue(key, info.value(key));
        }
        config->endGroup();
        delete config;
    }

    //设置编码为UTF8
    static void SetUTF8Code()
    {
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        QTextCodec::setCodecForLocale(codec);
        QTextCodec::setCodecForCStrings(codec);
        QTextCodec::setCodecForTr(codec);
#endif
    }

    //窗体居中显示
    static void FormInCenter(QWidget *frm)
    {
        int frmX = frm->width();
        int frmY = frm->height();
        QDesktopWidget w;
        int deskWidth = w.width();
        int deskHeight = w.height();
        QPoint movePoint(deskWidth / 2 - frmX / 2, deskHeight / 2 - frmY / 2);
        frm->move(movePoint);
    }

    static void bottomRightWidget(QWidget *widget)
    {
        int frmX = widget->width();
        int frmY = widget->height();
        QDesktopWidget w;
        int deskWidth = w.width();
        int deskHeight = w.height();
        QPoint movePoint(deskWidth - frmX, deskHeight - frmY);
        widget->move(movePoint);
    }
    static void set_username(QString username)
    {

       myHelper::username=username;

    }
    static QString get_username()
    {
        return myHelper::username;
    }
 private:
    static QString username;
};






#endif // COMMON_H
