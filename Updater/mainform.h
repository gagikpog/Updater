#ifndef MAINFORM_H
#define MAINFORM_H

#include <QMainWindow>

#include <QDialog>
#include <QtNetwork/QNetworkAccessManager>
#include <QMessageBox>
#include <QByteArray>
#include <QNetworkReply>
#include <QRegularExpression>
#include <QString>
#include <QKeyEvent>
#include <QDebug>

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
    void on_pushButton_clicked();
    void replyFinished(QNetworkReply* reply);

private:
    Ui::mainForm *ui;
};

#endif // MAINFORM_H
