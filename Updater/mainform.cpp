#include "mainform.h"
#include "ui_mainform.h"

mainForm::mainForm(QWidget *parent) : QMainWindow(parent), ui(new Ui::mainForm)
{
    ui->setupUi(this);
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

mainForm::~mainForm()
{
    delete ui;
}

//процедура которая вызывается для приема ответа от сервера
void mainForm::replyFinished(QNetworkReply* reply)
{
    //преобразование полученных данных в массив байт
    QByteArray response = reply->readAll();
    //получаем из его Q строку
    QString DataAsString = QString::fromStdString(response.toStdString());
    state = new ServerState(DataAsString);
    //выводит информацию полученную с сервера
    infoUpdate();
    //если у нас последняя версия, сообщаем об этом
    if (state->version == version)
    {
        QMessageBox msg;
        msg.setWindowTitle("Info");
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
