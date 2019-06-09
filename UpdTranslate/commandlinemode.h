#ifndef COMMANDLINEMODE_H
#define COMMANDLINEMODE_H
#include "header.h"

class CommandLineMode: public QObject
{
    Q_OBJECT
public:
    explicit CommandLineMode(QObject* parent = 0) : QObject(parent){}
    virtual ~CommandLineMode(){}
    void enableHideDownloadMode();
public slots:
    void result(QString res);
    void fileDownloaded(QString filename);
private:
    bool download = false;
    int downloadedFileCount = 0;
    ServerState* state;
};

#endif // COMMANDLINEMODE_H
