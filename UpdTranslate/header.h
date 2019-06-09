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
        force = textObject.value("force").toString() == "true";

        QJsonObject chngs = textObject.value("changes").toObject();

        foreach (const QString& key, chngs.keys())
        {
            QJsonValue value = chngs.value(key);
            changes.append(QPair<QString,QString>(key, value.toString()));
        }
    }

    QString version;
    QString build;
    QString host;
    bool force;
    QList<QPair<QString, QString>> changes;
};


#endif // HEADER_H
