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


class CommandLineMode: public QObject
{
    Q_OBJECT
public:
    explicit CommandLineMode(QObject* parent = 0) : QObject(parent){}
    virtual ~CommandLineMode(){}
public slots:
    void result(QString res)
    {
        ServerState state(res);
        qDebug() << "version:" << state.version << ",build:" << state.build;
        exit(0);
    }
};

#endif // CONNECTTOSERVER_H
