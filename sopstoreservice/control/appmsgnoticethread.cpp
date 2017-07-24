#include "appmsgnoticethread.h"
#include <QTimer>
#include <QDebug>
#include <csystemnotification.h>
#include <csystemnotificationmanager.h>
#include <csystembadge.h>
#include <csystempowermanager.h>
#include <QDateTime>
#include <QUuid>

AppMsgNoticeThread::AppMsgNoticeThread(QObject *parent) : QObject(parent)
{
//    m_pPowerManager = new CSystemPowerManager(this);
    m_pNgfManager   =  new CNgfManager(this);
}

AppMsgNoticeThread::~AppMsgNoticeThread()
{
//    if (m_pPowerManager) {
//        delete m_pPowerManager;
//        m_pPowerManager = NULL;
//    }
}

void AppMsgNoticeThread::onRemoveNitification(QString targetId)
{
    CSystemNotificationManager notificationService;
    QString updateId = mMapUppdateId.value(targetId,"");
    if(updateId != ""){
        notificationService.removeNotification(updateId);
    }
    mMapUppdateId.remove(targetId);
}

void AppMsgNoticeThread::onBcNotify(const QString senderId,
                                     const QString msgType,
                                     const QString content,
                                     const QString msgId,
                                     const QString sendTime,
                                     const QString displayName,
                                     const QString senderIconPath,
                                     const QString sessionType,
                                     int unReadNumber)
{
    Q_UNUSED(sendTime);
    Q_UNUSED(msgId);
    Q_UNUSED(sessionType);
    Q_UNUSED(senderId);
    Q_UNUSED(content);
    Q_UNUSED(displayName);
    Q_UNUSED(senderIconPath);


    CSystemNotificationManager notificationService;
    CSystemNotification notification;
    notification.setAppName("智慧企业");
    notification.setTitle(displayName);

    QString updateId = mMapUppdateId.value(senderId,"");
    if(updateId == ""){
        QUuid id = QUuid::createUuid();
        updateId = id.toString();
        mMapUppdateId[senderId] = updateId;
    }
    notification.setUpdateId(updateId);
    notification.setAction(senderId);
    notification.setMarqueeText(QString(tr("你收到了%1条即时消息")).arg(unReadNumber));
    notification.setSubtitle(content);
    QDateTime dateTime = QDateTime::fromMSecsSinceEpoch(sendTime.toLongLong());
    notification.setDisplayTime(dateTime);
    if(senderIconPath != ""){
        notification.setIcon("file:://"+senderIconPath);
    }
    notification.setVibrationMode(CNotification::NormalMode);
    notification.setSound("/usr/share/rings/门铃.wav");
    notification.setSopid("com.vrv.sopstore");
    notification.setUiAppId("sopstoreui");
    notificationService.sendNotification(notification);

    // 桌面角标数处理：
//    QString fileName =QString::fromStdString(APP_DATA_PATH)+".config.ini";
//    QSettings settings(fileName, QSettings::IniFormat);
//    int count = settings.value("badage",0).toInt()+1;
//    settings.setValue("badage",count);
//    CSystemBadge badage;
//    badage.setValue(LINKDOOD_SOPID,LINKDOOD_UISOPID,count);
}
