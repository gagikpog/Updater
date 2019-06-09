#ifndef CONNECTTOSERVER_H
#define CONNECTTOSERVER_H

#include "header.h"

#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSettings>



class ConnectToServer : public QObject
{
    Q_OBJECT
public:
    explicit ConnectToServer(QObject *parent = 0);
    virtual ~ConnectToServer();
    QString getVersion(){return version;}
signals:
    void resultData(QString data);
private:
    const QString settingsFilename = "settings.ini";
    QString version = "0.0.0";
private slots:
    void replyFinished(QNetworkReply* reply);
};


#endif // CONNECTTOSERVER_H
