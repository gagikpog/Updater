#include "mainform.h"
#include "ui_mainform.h"

mainForm::mainForm(QWidget *parent) : QMainWindow(parent), ui(new Ui::mainForm)
{
    ui->setupUi(this);
    serverConnection = new ConnectToServer(this);
    connect(serverConnection, SIGNAL(resultData(QString)), this, SLOT(replyFinished(QString)));
}

mainForm::~mainForm()
{
    delete ui;
}

//процедура которая вызывается для приема ответа от сервера
void mainForm::replyFinished(QString DataAsString)
{
    QMessageBox msg;
    msg.setWindowTitle("Info");
    if (DataAsString == "")
    {
        msg.setText("Could not connect to server");
        msg.exec();
    }
    state = new ServerState(DataAsString);
    //выводит информацию полученную с сервера
    infoUpdate();
    //если у нас последняя версия, сообщаем об этом
    if (state->version == serverConnection->getVersion())
    {
        msg.setText("You have the latest version");
        msg.exec();
    }
}

void mainForm::infoUpdate()
{
    if (state)
    {
        ui->lblVersionInfo->setText(state->version);
        ui->lblBuildInfo->setText(state->build);
        foreach (auto val, state->changes)
        {
            QTreeWidgetItem* topLevelItem = new QTreeWidgetItem(ui->treeWidget);
            ui->treeWidget->addTopLevelItem(topLevelItem);
            topLevelItem->setIcon(0, *(new QIcon(":/icons/download.png")));
            topLevelItem->setText(0, val.first);
        }
    }
}

void mainForm::on_btnDownload_clicked()
{
    QString host = state->host + "?version=" + state->version + "&filename=";
    foreach (auto val, state->changes)
    {
        QUrl url ( host + QUrl::toPercentEncoding(val.second));
        int n = val.second.lastIndexOf("/");
        if (n > 0)
        {
            QDir dir(val.second.mid(0,n));
            if (!dir.exists())
            {
                dir.mkpath(".");
            }
        }

        FileDownloader* currentDownloadFile = new FileDownloader(url, this);
        currentDownloadFile->setFilename(val.second);
        connect(currentDownloadFile, SIGNAL (downloaded(QString)), this, SLOT (fileDownloaded(QString)));
    }
}

void mainForm::fileDownloaded(QString filename)
{
    int n = filename.lastIndexOf("/");
    if (n > 0)
    {
        filename = filename.mid(n + 1);
    }

    for (int i = 0; i < ui->treeWidget->topLevelItemCount(); i++)
    {
        if (ui->treeWidget->topLevelItem(i)->text(0) == filename)
        {
            ui->treeWidget->topLevelItem(i)->setIcon(0, *(new QIcon(":/icons/done.png")));
        }
    }
}
