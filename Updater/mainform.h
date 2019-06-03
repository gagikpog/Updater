#ifndef MAINFORM_H
#define MAINFORM_H

#include <QMainWindow>

#include "header.h"
#include "downloader.h"

namespace Ui {
    class mainForm;
}

class mainForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainForm(QWidget *parent = 0);
    ~mainForm();

private slots:
    void replyFinished(QNetworkReply* reply);
    void on_btnDownload_clicked();
    void fileDownloaded(QString filename);

private:
    Ui::mainForm *ui;
    ServerState* state;
    void infoUpdate();
    const QString settingsFilename = "settings.ini";
    QString version = "0.0.0";
};

#endif // MAINFORM_H
