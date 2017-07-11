#include "cdownloadmanger.h"

CDownLoadManger::CDownLoadManger(QObject *parent) : QObject(parent)
{

}

CDownLoadItem::CDownLoadItem(QObject *parent): QObject(parent)
{

}

void CDownLoadItem::downloadFile(QString url)
{
    QString pkgName;
    QString fileName = APP_DIR+pkgName;
    mOutputFile.setFileName(fileName);
    if (!mOutputFile.open(QIODevice::WriteOnly)) {

    }
    QUrl romoteUrl(url);
    QNetworkRequest request;
    request.setUrl(romoteUrl);

    mCurDownLoadReply = mNetMgr.get(request);
    connect(mCurDownLoadReply, SIGNAL(downloadProgress(qint64,qint64)),
            SLOT(downloadProgress(qint64,qint64)));
    connect(mCurDownLoadReply, SIGNAL(finished()),
            SLOT(downloadFinished()));
    connect(mCurDownLoadReply, SIGNAL(readyRead()),
            SLOT(downloadReadyRead()));
}
void CDownLoadItem::downloadFinished()
{
    mOutputFile.close();
    if (mCurDownLoadReply->error()) {

    }else{
    }
    mCurDownLoadReply->deleteLater();

}

void CDownLoadItem::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
  int unit = bytesReceived*100/bytesTotal;
}

void CDownLoadItem::downloadReadyRead()
{
    mOutputFile.write(mCurDownLoadReply->readAll());
}
