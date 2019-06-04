#include "connecttoserver.h"


ConnectToServer::ConnectToServer(QObject* parent) : QObject(parent)
{
    //загружает настройки
    //объект для чтения
    QSettings settings(settingsFilename, QSettings::IniFormat);
    //загружает начтройкии
    version = settings.value("VERSION", "").toString();
    //если в файле нет информации или файла нет, то устанавливаем версию 0.0.0
    //это означает что будет скачано все файлы
    if (version == "")
    {
        version = "0.0.0";
    }

    //готовлюсь к отправке запроса
    QNetworkAccessManager *NAM = new QNetworkAccessManager(this);
    //назначаю процедуру для подучения ответа
    connect(NAM, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

    QString host = "http://k992302t.beget.tech/translate/update.php";
    //отправляю get запрос
    NAM->get(QNetworkRequest(QUrl(host+"?version="+version)));
}

ConnectToServer::~ConnectToServer(){}

//процедура которая вызывается для приема ответа от сервера
void ConnectToServer::replyFinished(QNetworkReply* reply)
{
    //преобразование полученных данных в массив байт
    QByteArray response = reply->readAll();
    //получаем из его Q строку
    QString DataAsString = QString::fromStdString(response.toStdString());
    //
    emit resultData(DataAsString);
}
