#include "ahttp.h"
#include "common.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QRegExp>
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <QDir>
#include"widget.h"
#include<QProcess>


#define SSO_SERVICE "http://10.238.205.30:8166/isc_mp/view/accredit/bizrole/jsp/bizrole.jsp"
AHttp::AHttp(QObject *parent) :
    QObject(parent)
{
    m_network = new QNetworkAccessManager(this);
    this->initConnects();
}

void AHttp::loginBaseServer(const QString &username, const QString &passwd)
{
    QString basePasswd = QString(passwd.toUtf8().toBase64());
    this->loginServer(username, basePasswd);

 //   emit finishedSignal(true);  // 测试
}

void AHttp::loginServer(const QString &username, const QString &passwd)
{
    QUrl url("http://10.238.205.30:8166/isc_sso/v1/tickets");
    QString post = QString("username=%1&password=%2&wangsheng=sgcc&service=%3").arg(username)
            .arg(passwd).arg(SSO_SERVICE);
    m_requestType = "TGT";
    qDebug() << "tgt" << post;
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded;charset=UTF-8");
    request.setHeader(QNetworkRequest::ContentLengthHeader, post.length());
    m_network->post(request, post.toUtf8());
}

void AHttp::updateTicket(const QString &tgt)
{
    requestSt(tgt);
}

void AHttp::logout()
{
    QUrl url("http://10.238.205.30:8166/isc_sso/logout/");
    QString post = QString("&tgt=%1").arg(m_tgtStr);
    m_requestType = "LOGOUT";
    qDebug() << "tgt" << post;
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded;charset=UTF-8");
    request.setHeader(QNetworkRequest::ContentLengthHeader, post.length());
    m_network->post(request, post.toUtf8());
}

void AHttp::finishedSlot(QNetworkReply *reply)
{
//    QVariant statusCodeV =
//         reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
//         // Or the target URL if it was a redirect:
//         QVariant redirectionTargetUrl =
//         reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
         // see CS001432 on how to handle this
        qDebug() << "finishedSlot";
         // no error received?
         if (reply->error() == QNetworkReply::NoError)
         {
             QByteArray bytes = reply->readAll();  // bytes
             QString string = QString::fromUtf8(bytes);
             qDebug() << "tgt post:" << string;
             if(m_requestType == "TGT")
             {
                 QRegExp rx("action=\".*\" method");
                 int pos = string.indexOf(rx);
                 if(pos >= 0)
                 {
                     m_tgtStr = rx.cap(0);

                     m_tgtStr.remove("action=\"");
                     m_tgtStr.remove("\" method");
                     qDebug() << "tgy" << m_tgtStr;
                     requestSt(m_tgtStr);
                 }else
                     emit finishedSignal(false);
             }else if(m_requestType == "ST")
             {

            //     qDebug()<<"**********:::"<<myHelper::get_username();
//                 QProcess *poc=new QProcess();
                 QString cmd_string=QString("sudo bash /usr/bin/mount_volume.sh %1 &").arg(myHelper::get_username());
//                 poc->start(string);
                QProcess::startDetached(cmd_string);
                QString stfile = "/tmp/ovd/pmis_parameter.ini";
                QFileInfo fileinfo(stfile);
                if(!fileinfo.absoluteDir().exists())
                {
                    fileinfo.absoluteDir().mkpath(fileinfo.absolutePath());
                }
                QFile file(stfile);
                QString writeStr = "?ticket=" + string;
                if(file.open(QIODevice::WriteOnly))
                {
                    file.setPermissions(file.permissions() | QFile::WriteOther | QFile::WriteGroup);
                    file.write(writeStr.toUtf8());
                    file.close();
                }
                emit finishedSignal(true);




             }
         }
         // Some http error received
         else
         {
             emit finishedSignal(false);
             // handle errors here
         }
         reply->deleteLater();
}

void AHttp::initConnects()
{
    connect(m_network, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(finishedSlot(QNetworkReply*)));
}

void AHttp::requestSt(const QString &tgt)
{
    QUrl url(tgt);
    QString post = QString("service=%1").arg(SSO_SERVICE);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded;charset=UTF-8");
    request.setHeader(QNetworkRequest::ContentLengthHeader, post.length());
    m_requestType = "ST";
    m_network->post(request, post.toUtf8());
}
