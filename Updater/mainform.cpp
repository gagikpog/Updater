#include "mainform.h"
#include "ui_mainform.h"

mainForm::mainForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainForm)
{
    ui->setupUi(this);
}

mainForm::~mainForm()
{
    delete ui;
}
