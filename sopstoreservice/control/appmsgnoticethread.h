#ifndef APPMSGNOTICETHREAD_H
#define APPMSGNOTICETHREAD_H

#include <QObject>
#include <QMap>
#include <cngfmanager.h>

class CSystemPowerManager;
class AppMsgNoticeThread : public QObject
{
    Q_OBJECT
public:
    explicit AppMsgNoticeThread(QObject *parent = 0);
    virtual ~AppMsgNoticeThread();
signals:
public slots:
    void onRemoveNitification(QString targetId);
    void onBcNotify(const QString senderId,
                  const QString msgType,
                  const QString content,
                  const QString msgId,
                  const QString sendTime,
                  const QString displayName,
                  const QString senderIconPath="",
                  const QString sessionType="",
                  int unReadNumber=1);
private:
    CNgfManager *m_pNgfManager;
    QMap<QString,QString> mMapUppdateId;
};

#endif // APPMSGNOTICETHREAD_H
