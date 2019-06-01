#include "mainform.h"
#include "ui_mainform.h"

mainForm::mainForm(QWidget *parent) : QMainWindow(parent), ui(new Ui::mainForm)
{
    ui->setupUi(this);
}

mainForm::~mainForm()
{
    delete ui;
}

void mainForm::on_pushButton_clicked()
{
    //готовлюсь к отправке запроса
    QNetworkAccessManager *NAM = new QNetworkAccessManager(this);
    //назначаю процедуру для подучения ответа
    connect(NAM, SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));

    QString version = "0.0.0";
    QString host = "http://k992302t.beget.tech/translate/update.php";
    //отправляю get запрос
    NAM->get(QNetworkRequest(QUrl(host+"?version="+version)));
}

//процедура которая вызывается для приема ответа от сервера
void mainForm::replyFinished(QNetworkReply* reply)
{
    //преобразование полученных данных в массив байт
    QByteArray response = reply->readAll();
    //получаем из его Q строку
    QString DataAsString = QString::fromStdString(response.toStdString());

    qDebug() << "translate: " << DataAsString;
}
