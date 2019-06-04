#include "mainform.h"
#include <QApplication>

#include "connecttoserver.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainForm w;
    if (argc >= 2)
    {
        if (strlen(argv[1]) >= 2)
        {
            if (argv[1][0] == '-' && argv[1][1] == 'h')
            {
                ConnectToServer* server = new ConnectToServer();
                CommandLineMode* clm = new CommandLineMode();
                QObject::connect(server, SIGNAL(resultData(QString)), clm, SLOT(result(QString)));
            }
        }
    } else {
        w.show();
    }
    return a.exec();
}
