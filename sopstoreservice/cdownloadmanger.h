#ifndef CDOWNLOADMANGER_H
#define CDOWNLOADMANGER_H

#include <QObject>
#include <QFile>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>

#include "consttype.h"

class CDownLoadItem : public QObject{
    Q_OBJECT
public:
    explicit CDownLoadItem(QObject *parent = 0);
    void downloadFile(QString url);
signals:

public slots:
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void downloadFinished();
    void downloadReadyRead();

private:
    QNetworkAccessManager mNetMgr;
    QNetworkReply *mCurDownLoadReply;
    QFile mOutputFile;
};

class CDownLoadManger : public QObject
{
    Q_OBJECT
public:
    explicit CDownLoadManger(QObject *parent = 0);

signals:

public slots:
};

#endif // CDOWNLOADMANGER_H
