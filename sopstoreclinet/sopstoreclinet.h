#ifndef SOPSTORECLINET_H
#define SOPSTORECLINET_H
#include "sopstoreclinet_global.h"
#include <QDebug>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusPendingReply>
#include <QDBusInterface>
#include <QFile>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <cnetworkmanager.h>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonParseError>

#include <QObject>
#include <cconfig.h>
#include "consttype.h"

class  SopStoreClinet : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString curUserInfo READ curUserInfo WRITE setCurUserInfo NOTIFY curUserInfoChanged)
    Q_PROPERTY(QString myApps READ myApps WRITE setMyApps NOTIFY myAppsChanged)
    Q_PROPERTY(QString downloadingApps READ downloadingApps WRITE setDownloadingApps NOTIFY downloadingAppsChanged)
public:
    explicit SopStoreClinet(QObject *parent = 0);
    ~SopStoreClinet();

    QString curUserInfo() const;
    void setCurUserInfo(const QString curUserInfo);

    QString myApps() const;
    void setMyApps(const QString json);

    QString downloadingApps() const;
    void setDownloadingApps(const QString json);

    //Q_INVOKABLE bool isInstallApp(QString userId,QString appId);

    Q_INVOKABLE void writeData(QString content);
    Q_INVOKABLE QString readData();

    Q_INVOKABLE void downloadApp(QString pkgName,QString url);
    Q_INVOKABLE void login(QString json);
    Q_INVOKABLE void preLogin(QString json);
    Q_INVOKABLE void loginout();

    /**
      setMessageRead:设置消息已读写
      targetId:long
      msgId:long
      */
    Q_INVOKABLE void setMessageRead(QString json);

    Q_INVOKABLE void slidesshow(QString json);
    Q_INVOKABLE void queryAppStore(QString json);
    Q_INVOKABLE void queryEnOS(QString json);

    Q_INVOKABLE void installSopApp(QString path);
    Q_INVOKABLE void uninstallSopApp(QString sopId);
    Q_INVOKABLE void callPhone(QString json);
    Q_INVOKABLE void opensopApp(QString json);
    Q_INVOKABLE void changedPwd(QString json);
    Q_INVOKABLE void getSonOrgs(QString orgId);
    Q_INVOKABLE void updateAccount(QString json);
    Q_INVOKABLE void log(QString data);
    Q_INVOKABLE void getAccountInfo();
    Q_INVOKABLE void getAppLoginStatus();
    Q_INVOKABLE void getSystemAppList();
    Q_INVOKABLE void getLoginAuthCode(QString json);
    Q_INVOKABLE void getOfflineMsg();

    Q_INVOKABLE bool isNetworkAvailable();
    Q_INVOKABLE QString dealTime(qint64 msgtime);
signals:
    void voiceCall(QString param);
    void openApp(QString param);
    void callback(QString json);
    void noticeLastMsg(QString msgContent);
    void installApp(QString appPath);
    void uninstallApp(QString sopId);
    void getSystemApps();
    void loginoutUI();
    void curUserInfoChanged();
    void myAppsChanged();
    void downloadingAppsChanged();
public slots:
    void onLoginAuthCodeResult(QString authCode);
    void onGetSystemApps(QString json);
    void onRefreshData(QString json);
    void onGetAppLoginStatusResult(QString json);
    void onLoginResult(QString json);
    void onLoginoutResult(QString json);
    void onPreLoginResult(QString json);
    void onGetAccountInfoResult(QString json);
    void onSlidesshowResult(QString json);
    void onQueryAppStoreResult(QString json,int type);
    void onQueryEnOSResult(QString json,int type);
    void onGetSonOrgsResult(QString json);
    void onChangedPwdResult(QString json);
    void onNoticeLastMsg(QString msgContent);
    void onUpdateAccountResult(QString json);

private slots:

    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void downloadFinished();
    void downloadReadyRead();
    void onNetworkStatusChanged(bool connected, CNetworkManager::NetworkType type);

private:
    QNetworkAccessManager mNetMgr;
    QNetworkReply *mCurDownLoadReply;
    QFile mOutputFile;
    QJsonArray mJsonMsgs;
    CNetworkManager mNetworkMgr;
    void initDBusConnect();
    void jsonParce(QString json,QString fName);
    QString m_strCurUserInfo;
    QString m_strApps;//缓存我的apps
    QString m_strDownloadingApps;//记录正在下载app
};

#endif // SOPSTORECLINET_H
