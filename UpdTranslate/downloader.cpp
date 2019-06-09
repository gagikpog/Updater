#include "downloader.h"

FileDownloader::FileDownloader(QUrl fileUrl, QObject *parent) : QObject(parent)
{
    connect( &m_WebCtrl, SIGNAL (finished(QNetworkReply*)), this, SLOT (fileDownloaded(QNetworkReply*)));

    QNetworkRequest request(fileUrl);
    m_WebCtrl.get(request);
}

FileDownloader::~FileDownloader() { }

void FileDownloader::setFilename(QString filename)
{
    _filename = filename;
}

void FileDownloader::fileDownloaded(QNetworkReply* pReply)
{
    m_DownloadedData = pReply->readAll();
    if (m_DownloadedData.length() != 0)
    {
        SaveFromFile();
        emit downloaded(_filename);
    } else {
        qDebug() << "no connection";
    }
}

bool FileDownloader::SaveFromFile()
{
    QFile file(_filename);
    if (!file.open(QIODevice::WriteOnly))
    {
       fprintf(stderr, "Could not open %s for writing: %s\n",
               qPrintable(_filename),
               qPrintable(file.errorString()));
       return false;
    }

    file.write(m_DownloadedData);
    file.close();

    return true;
}
