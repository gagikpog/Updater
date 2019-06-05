#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>

class FileDownloader : public QObject
{
    Q_OBJECT
  public:
    explicit FileDownloader(QUrl fileUrl, QObject *parent = 0);
    virtual ~FileDownloader();

    bool SaveFromFile();
    void setFilename(QString filename);
  signals:
    void downloaded(QString filename);
  private slots:
    void fileDownloaded(QNetworkReply* pReply);

  private:
    QNetworkAccessManager m_WebCtrl;
    QByteArray m_DownloadedData;
    QString _filename;
};


#endif // DOWNLOADER_H
