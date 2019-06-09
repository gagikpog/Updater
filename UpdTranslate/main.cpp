#include "mainform.h"
#include <QApplication>

#include "connecttoserver.h"
#include "commandlinemode.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainForm* w;
//    std::cout << "hello world";
//    qDebug() << "goodbye world";
    if (argc >= 2)
    {
        bool download = false,
             hide = false;
        for (int i = 1; i < argc; i++)
        {
            QString key (argv[i]);
            hide |= key == "-h";
            download |= key == "-d";
        }

        if (hide)
        {
            ConnectToServer* server = new ConnectToServer();
            CommandLineMode* clm = new CommandLineMode();
            QObject::connect(server, SIGNAL(resultData(QString)), clm, SLOT(result(QString)));
            if (download)
            {
                clm->enableHideDownloadMode();
            }
        }
    } else {
        w = new mainForm();
        w->show();
    }
    return a.exec();
}
