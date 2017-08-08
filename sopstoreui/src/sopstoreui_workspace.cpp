#include "sopstoreui_workspace.h"
#include "sopstoreclinet.h"
#include <QJsonObject>
#include <QJsonDocument>

int sopstoreui_Workspace::pageType(QString url)
{
    qDebug()<<Q_FUNC_INFO<<"page:"<<url;
    if((url.contains("/TimeOut"))||(url.contains("/App"))||url.endsWith("/Me")||url.contains("/Main")||url.contains("/Contacts")){
        return 0;
    }else if(url.contains("#/Quit")){//
        return -1;
    }else{
        return 1;
    }
}

void sopstoreui_Workspace::voiceCall(QString phone)
{
    QString call = "contact://showdialpage?"+phone;
    qDebug()<<Q_FUNC_INFO<<"call:"<<call;
    qApp->openUrl(call);
}

void sopstoreui_Workspace::install(QString params)
{
    qDebug()<<Q_FUNC_INFO<<"params:"<<params;
    mSysPkgMgr->install(params,false);
}

void sopstoreui_Workspace::uninstall(QString params)
{
    mSysPkgMgr->uninstall(params);
}

void sopstoreui_Workspace::openApp(QString url)
{
    if(url.contains("http")||url.contains("https")){
        mNeedNoticeRefreshData = true;
        url = "browser:"+url;
    }
    qApp->openUrl(url);
}

QString sopstoreui_Workspace::getSystemAppList()
{
    QList<QSharedPointer<CPackageInfo> > list = mSysPkgMgr->packageInfoList();
    QJsonDocument doc;
    QJsonObject root;
    for(auto i :list){
        QJsonObject child;
        child.insert("ver",i->versionName());
        child.insert("name",i->name());
        root.insert(i->sopid(),child);
    }
    doc.setObject(root);
    QString json = doc.toJson();

    emit systemApps(json);
    return json;
}

void sopstoreui_Workspace::setUsrName(QString nm)
{
    QSettings config(APP_DATA_CONFIG,QSettings::IniFormat);
    config.setValue("usrNm",nm);
    emit usrNameChanged();
}

void sopstoreui_Workspace::setUsrPasswd(QString pwd)
{
    QSettings config(APP_DATA_CONFIG,QSettings::IniFormat);
    config.setValue("usrPwd",pwd);
    emit usrPasswdChanged();
}

QString sopstoreui_Workspace::usrName()
{
    QSettings config(APP_DATA_CONFIG,QSettings::IniFormat);
    return config.value("usrNm","").toString();
}

QString sopstoreui_Workspace::usrPasswd()
{
    QSettings config(APP_DATA_CONFIG,QSettings::IniFormat);
    return config.value("usrPwd","").toString();
}

void sopstoreui_Workspace::closeBrowser()
{
    qDebug()<<Q_FUNC_INFO<<"==================closeBrowser===========================";
    //    if(mNeedNoticeRefreshData){
    //        mNeedNoticeRefreshData = false;
    //        return;
    //    }
    //     CProcessManager proMgr;
    //     QList<int> pids = proMgr.processList();

    //     for(auto i : pids){
    //         qDebug()<<Q_FUNC_INFO<<"kill id:"<<i<<",sodId:"<<proMgr.sopidByPid(i);
    //         if(proMgr.sopidByPid(i) == "com.syberos.browser"){
    //             proMgr.killProcessByPid(i);
    //         }
    //     }
}

QUrl sopstoreui_Workspace::appUrl()
{
    QUrl url;
    url.setUrl("file:///data/apps/com.vrv.sopstore/bin/h5/index.html");
    return url;
}

QString sopstoreui_Workspace::sid()
{
    return mSid;
}

void sopstoreui_Workspace::setSid(QString data)
{
    mSid = QUuid::createUuid().toString().replace("{","").replace("}","").replace("-","");
    emit sidChanged();
}

sopstoreui_Workspace::sopstoreui_Workspace()
    : CWorkspace()
{
    //serviceIP();
    mNeedNoticeRefreshData = true;
    qmlRegisterType<SopStoreClinet>("com.app.sopApp",1,0,"SopAppClient");

    mSysPkgMgr = QSharedPointer<CSystemPackageManager>(new CSystemPackageManager(this));
    connect(mSysPkgMgr.data(),SIGNAL(installStatusChanged(const QString &, const QString &, CPackageInfo::PackageStatus , CPackageInfo::PackageError , int )),this,SLOT(onInstallStatusChanged(const QString &, const QString &, CPackageInfo::PackageStatus , CPackageInfo::PackageError , int )));

    m_view = SYBEROS::SyberosGuiCache::qQuickView();
    QObject::connect(m_view->engine(), SIGNAL(quit()), qApp, SLOT(quit()));

    mpClient = QSharedPointer<SopStoreClinet>(new SopStoreClinet(this));

    m_view->rootContext()->setContextProperty("appClient", mpClient.data());
    m_view->rootContext()->setContextProperty("mainApp", this);
    m_view->rootContext()->setContextProperty("globalApp", qApp);

    qApp->setAttribute(Qt::AA_SynthesizeTouchForUnhandledMouseEvents, true);

    m_view->setSource(QUrl("qrc:/qml/mainUI.qml"));
    m_view->showFullScreen();
}

sopstoreui_Workspace::~sopstoreui_Workspace()
{
    qDebug()<<Q_FUNC_INFO;
    QSettings config(APP_DATA_CONFIG,QSettings::IniFormat);
    config.setValue("clientStatus",0);
    //    closeBrowser();
}

void sopstoreui_Workspace::onActive()
{
    QSettings config(APP_DATA_CONFIG,QSettings::IniFormat);
    config.setValue("clientStatus",1);
    emit refreshData();
}

void sopstoreui_Workspace::onDeactive()
{
    QSettings config(APP_DATA_CONFIG,QSettings::IniFormat);
    config.setValue("clientStatus",0);
}

void sopstoreui_Workspace::onLaunchComplete(Option option, const QStringList& params)
{
    Q_UNUSED(params)

    qApp->runService("sopstoreservice");
    switch (option) {
    case CWorkspace::HOME:
        qDebug()<< "Start by Home";
        break;
    case CWorkspace::URL:
        break;
    case CWorkspace::EVENT:
        break;
    case CWorkspace::DOCUMENT:
        break;
    default:
        break;
    }

    QSettings config(APP_DATA_CONFIG,QSettings::IniFormat);
    config.setValue("clientStatus",1);
}

void sopstoreui_Workspace::onInstallStatusChanged(const QString &sopid, const QString &pkgPath, CPackageInfo::PackageStatus status, CPackageInfo::PackageError error, int percent)
{
    qDebug()<<Q_FUNC_INFO;
    //    getSystemAppList();
}

