#ifndef HEADER_H
#define HEADER_H

#include <QDialog>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork>
#include <QMessageBox>
#include <QByteArray>
#include <QNetworkReply>
#include <QRegularExpression>
#include <QString>
#include <QKeyEvent>
#include <QDebug>
#include <QStringListModel>
#include <QPair>
#include <QTreeWidgetItem>

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>


struct ServerState
{
    ServerState(QString jsonStr)
    {
        QJsonObject textObject = QJsonDocument::fromJson(jsonStr.toUtf8()).object();
        version = textObject.value("version").toString();
        build = textObject.value("build").toString();
        host = textObject.value("host").toString();


        QJsonObject chngs = textObject.value("changes").toObject();

        foreach (const QString& key, chngs.keys())
        {
            QJsonValue value = chngs.value(key);
            changes.append(QPair<QString,QString>(key, value.toString()));
        }

       // QJsonArray arr = chngs.toArray();
        //textObject = QJsonDocument::fromJson(chngsQJsonObject.toUtf8()).object();
    }

    QString version;
    QString build;
    QString host;
    QList<QPair<QString, QString>> changes;
};


#endif // HEADER_H
