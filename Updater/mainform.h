#ifndef MAINFORM_H
#define MAINFORM_H

#include <QMainWindow>

#include "header.h"
#include "downloader.h"
#include "connecttoserver.h"

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
    void replyFinished(QString DataAsString);
    void on_btnDownload_clicked();
    void fileDownloaded(QString filename);

private:
    Ui::mainForm *ui;
    ServerState* state;
    void infoUpdate();
    ConnectToServer* serverConnection = NULL;
};

#endif // MAINFORM_H
