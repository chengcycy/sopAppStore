#ifndef __SOPSTOREUI_WORKSPACE__
#define __SOPSTOREUI_WORKSPACE__

#include <QQuickView>
#include <QQuickWindow>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <QDebug>

#include <cworkspace.h>
#include <SyberosServiceCache>
#include <SyberosGuiCache>
#include <cgui_application.h>
#include <QUuid>
#include "cprocessmanager.h"

#include "cpackageinfo.h"
#include "csystempackagemanager.h"
#include "sopstoreclinet.h"

using namespace SYBEROS;

class sopstoreui_Workspace : public CWorkspace
{
    Q_OBJECT
    Q_PROPERTY(QUrl appUrl READ appUrl NOTIFY appUrlChanged)
    Q_PROPERTY(QString sid READ sid WRITE setSid NOTIFY sidChanged)

    Q_PROPERTY(QString usrName READ usrName WRITE setUsrName NOTIFY usrNameChanged)
    Q_PROPERTY(QString usrPasswd READ usrPasswd WRITE setUsrPasswd NOTIFY usrPasswdChanged)
public:
    Q_INVOKABLE int  pageType(QString url);
    Q_INVOKABLE void voiceCall(QString phone);
    Q_INVOKABLE void install(QString params);
    Q_INVOKABLE void uninstall(QString params);
    Q_INVOKABLE void openApp(QString url);
    Q_INVOKABLE QString getSystemAppList();

    void setUsrName(QString nm);
    void setUsrPasswd(QString pwd);
    QString usrName();
    QString usrPasswd();

    QUrl    appUrl();
    QString sid();
    void setSid(QString data);

    sopstoreui_Workspace();
    virtual ~sopstoreui_Workspace();
    void onActive();
    void onDeactive();
    void onLaunchComplete(Option option, const QStringList& params);

signals:
    void appUrlChanged();
    void refreshData();
    void systemApps(QString json);
    void sidChanged();
    void usrNameChanged();
    void usrPasswdChanged();

public slots:
    void closeBrowser();
    void onInstallStatusChanged(const QString& sopid,
                                const QString& pkgPath,
                                CPackageInfo::PackageStatus status,
                                CPackageInfo::PackageError error = CPackageInfo::NoError,
                                int percent = -1);
private:
    QSharedPointer<SopStoreClinet> mpClient;
    QQuickView *m_view;
    QSharedPointer<CSystemPackageManager> mSysPkgMgr;
    QString    mSid;
    bool       mNeedNoticeRefreshData;
};
#endif //__SOPSTOREUI_WORKSPACE__
