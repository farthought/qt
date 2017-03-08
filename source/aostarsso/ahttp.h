#ifndef AHTTP_H
#define AHTTP_H

#include <QObject>
class QNetworkAccessManager;
class QNetworkReply;

class AHttp : public QObject
{
    Q_OBJECT
public:
    explicit AHttp(QObject *parent = 0);
    /*!
     * \brief loginBaseServer
     * \param username
     * \param passwd
     */
    void loginBaseServer(const QString &username, const QString &passwd);

    /*!
     * \brief loginServer
     * \param username
     * \param passwd
     */
    void loginServer(const QString &username, const QString &passwd);
    /*!
     * \brief getTGT
     * \return
     */
    QString getTGT()const
    {
        return m_tgtStr;
    }
    void updateTicket(const QString &tgt);
    void logout();
signals:
    void finishedSignal(bool);
private slots:
    void finishedSlot(QNetworkReply* reply);
private:
    void initConnects();
    void requestSt(const QString &tgt);
public slots:
private:
    QNetworkAccessManager *m_network;
    QString m_tgtStr;
    QString m_requestType;

};

#endif // AHTTP_H
