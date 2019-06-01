#ifndef MAINFORM_H
#define MAINFORM_H

#include <QMainWindow>

namespace Ui {
class mainForm;
}

class mainForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainForm(QWidget *parent = 0);
    ~mainForm();

private:
    Ui::mainForm *ui;
};

#endif // MAINFORM_H
