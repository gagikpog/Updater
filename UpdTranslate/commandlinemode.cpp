#include "commandlinemode.h"
#include "downloader.h"

void CommandLineMode::enableHideDownloadMode()
{
    download = true;
}

void CommandLineMode::result(QString res)
{
    state = new ServerState(res);
    if (download || state->force)
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
    } else {
        qDebug() << "version:" << state->version << ",build:" << state->build;
        exit(0);
    }
}

void CommandLineMode::fileDownloaded(QString)
{
    downloadedFileCount++;
    if (downloadedFileCount >= state->changes.length())
    {
        qDebug() << "version:" << state->version << ",build:" << state->build;
        exit(0);
    }
}
