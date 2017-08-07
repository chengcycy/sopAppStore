#include "sopstoreclinet.h"
#include <QFileInfo>
#include <QtMath>
SopStoreClinet::SopStoreClinet(QObject *parent) :
    QObject(parent)
{

    m_strApps = "";
    m_strDownloadingApps = "";
    initDBusConnect();
    connect(&mNetworkMgr,SIGNAL(networkStatusChanged(bool,CNetworkManager::NetworkType)),this,SLOT(onNetworkStatusChanged(bool,CNetworkManager::NetworkType)));
}

SopStoreClinet::~SopStoreClinet()
{
    qDebug()<<Q_FUNC_INFO;
    m_strApps = "";
}

QString SopStoreClinet::curUserInfo() const
{
    return m_strCurUserInfo;
}

void SopStoreClinet::setCurUserInfo(const QString curUserInfo)
{
    if (m_strCurUserInfo != curUserInfo) {
        m_strCurUserInfo = curUserInfo;
        emit curUserInfoChanged();
    }
}

QString SopStoreClinet::myApps() const
{
    return m_strApps;
}

void SopStoreClinet::setMyApps(const QString json)
{
    m_strApps = json;
    emit myAppsChanged();
}

QString SopStoreClinet::downloadingApps() const
{
    return m_strDownloadingApps;
}

void SopStoreClinet::setDownloadingApps(const QString json)
{
    m_strDownloadingApps = json;
    emit downloadingAppsChanged();
}

void SopStoreClinet::writeData(QString content)
{
    QFile file(APP_DATA_CACHE);
    if(file.open(QIODevice::WriteOnly)){
        file.write(content.toUtf8().data());
        file.close();
    }
    jsonParce("{\"result\":true}","writeData");
}

QString SopStoreClinet::readData()
{
    QFile file(APP_DATA_CACHE);
    if(file.open(QIODevice::ReadOnly)){
        QString content = file.readAll();
        file.close();
        return content;
    }
    return "";
}
void SopStoreClinet::login(QString json)
{
    qDebug()<<Q_FUNC_INFO;
    GET_DATA_PARAMS(login,json);
}

void SopStoreClinet::preLogin(QString json)
{
    qDebug()<<Q_FUNC_INFO;
    GET_DATA_PARAMS(reqUserNameList,json);
}

void SopStoreClinet::loginout()
{
    GET_DATA(loginout);
}

void SopStoreClinet::setMessageRead(QString json)
{
    GET_DATA_PARAMS(setMessageRead,json);
}

void SopStoreClinet::slidesshow(QString json)
{
    GET_DATA_PARAMS(queryAppStore,json);
}

void SopStoreClinet::queryAppStore(QString json)
{
    GET_DATA_PARAMS(queryAppStore,json);
}

void SopStoreClinet::queryEnOS(QString json)
{
    qDebug()<<Q_FUNC_INFO;
    GET_DATA_PARAMS(queryEnOS,json);
}

void SopStoreClinet::installSopApp(QString path)
{
    qDebug()<<Q_FUNC_INFO<<path;
    emit installApp(APP_DIR + path);
}

void SopStoreClinet::uninstallSopApp(QString sopId)
{
    emit uninstallApp(sopId);
}

void SopStoreClinet::changedPwd(QString json)
{
    GET_DATA_PARAMS(changedPwd,json);
}

void SopStoreClinet::getSonOrgs(QString orgId)
{
    qDebug()<<Q_FUNC_INFO<<"orgId:"<<orgId;
    GET_DATA_PARAMS(getSonOrgs,orgId);
}

void SopStoreClinet::updateAccount(QString json)
{
    GET_DATA_PARAMS(updateAccount,json);
}

void SopStoreClinet::log(QString data)
{
    qDebug()<<Q_FUNC_INFO<<"log:"<<data;
}

void SopStoreClinet::getAccountInfo()
{
    GET_DATA(getAccountInfo);
}

void SopStoreClinet::getAppLoginStatus()
{
    GET_DATA(getAppLoginStatus);
}

void SopStoreClinet::getSystemAppList()
{
    emit getSystemApps();
}

void SopStoreClinet::getLoginAuthCode(QString json)
{
    GET_DATA_PARAMS(getLoginAuthCode,json);
}

QString SopStoreClinet::getOfflineMsg()
{
    QJsonDocument doc;
    doc.setArray(mJsonMsgs);
    //    jsonParce(doc.toJson(),"getOfflineMsg");

    while(mJsonMsgs.size()>0){
        mJsonMsgs.removeAt(mJsonMsgs.size()-1);
    }
    return doc.toJson();
}

bool SopStoreClinet::isNetworkAvailable()
{
    bool status = mNetworkMgr.isNetworkAvailable();
    qDebug()<<Q_FUNC_INFO<<"networkStatus:"<<status;
    QJsonDocument doc;
    QJsonObject obj;
    obj.insert("status",status);
    doc.setObject(obj);
    emit jsonParce(doc.toJson(),"isNetworkAvailable");
}

void SopStoreClinet::onLoginAuthCodeResult(QString authCode)
{
    qDebug()<<Q_FUNC_INFO<<"authCode:"<<authCode;
    QJsonDocument doc;
    QJsonObject obj;
    obj.insert("authCode",authCode);
    doc.setObject(obj);
    emit jsonParce(doc.toJson(),"getLoginAuthCode");
}

void SopStoreClinet::onGetSystemApps(QString json)
{
    emit jsonParce(json,"getSystemAppList");
}
void SopStoreClinet::onRefreshData(QString json)
{
    //    qDebug()<<Q_FUNC_INFO<<"onRefreshData:"<<json;
    //    emit jsonParce(json,"refreshData");
}

void SopStoreClinet::onLoginResult(QString json)
{
    jsonParce(json,"login");
}

void SopStoreClinet::onGetAppLoginStatusResult(QString json)
{
    jsonParce(json,"getAppLoginStatus");
}
void SopStoreClinet::onLoginoutResult(QString json)
{
    jsonParce(json,"loginout");
}

void SopStoreClinet::onPreLoginResult(QString json)
{
    jsonParce(json,"preLogin");
    m_strApps = "";
}

void SopStoreClinet::onGetAccountInfoResult(QString json)
{
    jsonParce(json,"getAccountInfo");
}

void SopStoreClinet::onSlidesshowResult(QString json)
{
    jsonParce(json,"slidesshow");
}

void SopStoreClinet::onQueryAppStoreResult(QString json,int type)
{
    qDebug()<<Q_FUNC_INFO<<"json:"<<json;
    QString fName;
    if(type == 1){
        fName = "appInfos";
        setMyApps(json);
    }else if(type == 2){
        fName = "appStores";
    }else if(type == 3){
        fName = "appBeans";
    }else if(type == 4){
        fName = "classifyBeans";
    }else if(type == 6){
        fName = "addApp";
    }else if(type == 7){
        fName = "delApp";
    }
    else if(type == 8){
        fName = "appStatistics";
    }
    jsonParce(json,fName);
}

void SopStoreClinet::onQueryEnOSResult(QString json,int type)
{
    if(type == 2){//search
        jsonParce(json,"searchEnOS");
    }else{
        jsonParce(json,"queryEnOS");
    }

}

void SopStoreClinet::onGetSonOrgsResult(QString json)
{
    jsonParce(json,"getSonOrgs");
}

void SopStoreClinet::onChangedPwdResult(QString json)
{
    jsonParce(json,"changedPwd");
}

void SopStoreClinet::onNoticeLastMsg(QString msgContent)
{
    qDebug()<<Q_FUNC_INFO<<"msg:"<<msgContent;
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(msgContent.toUtf8().data(),&err);
    if(err.error == QJsonParseError::NoError){
        QJsonObject obj = doc.object();
        if(obj.value("offline").toBool() == true){
            mJsonMsgs.append(obj);
        }else{
            jsonParce(msgContent,"noticeLastMsg");
        }
    }
}

void SopStoreClinet::onUpdateAccountResult(QString json)
{
    jsonParce(json,"updateAccount");
}

void SopStoreClinet::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    int unit = bytesReceived*100/bytesTotal;
    qDebug()<<Q_FUNC_INFO<<"unit:"<<unit;
    QString strJSON = "{\"progress\":"+ QString::number(unit)+"}";
    jsonParce(strJSON,"progress");
}

void SopStoreClinet::downloadApp(QString pkgName, QString url)
{
    if(!url.startsWith("http")){
        QString BASE = "http://"+serviceIP()+"/";
        url = BASE + url;
    }
    QString fileName = APP_DIR+pkgName;
    mOutputFile.setFileName(fileName);
    if (!mOutputFile.open(QIODevice::WriteOnly)) {
        qDebug()<<Q_FUNC_INFO<<"open File fail.";

        QJsonObject obj;
        QJsonDocument doc;
        obj.insert("code",false);
        doc.setObject(obj);
        emit jsonParce(doc.toJson(),"downloadApp");
        return;
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

void SopStoreClinet::downloadFinished()
{
    QJsonObject obj;
    QJsonDocument doc;

    mOutputFile.close();
    if (mCurDownLoadReply->error()) {
        qDebug()<<Q_FUNC_INFO<<mCurDownLoadReply->errorString();
        obj.insert("code",false);
    }else{
        obj.insert("code",true);
    }
    mCurDownLoadReply->deleteLater();
    doc.setObject(obj);
    qDebug()<<Q_FUNC_INFO;
    emit jsonParce(doc.toJson(),"downloadApp");
}

void SopStoreClinet::downloadReadyRead()
{
    mOutputFile.write(mCurDownLoadReply->readAll());
}

void SopStoreClinet::onNetworkStatusChanged(bool connected, CNetworkManager::NetworkType type)
{
    qDebug()<<Q_FUNC_INFO<<"networkStatus:"<<connected;
    QJsonDocument doc;
    QJsonObject obj;
    obj.insert("status",connected);
    doc.setObject(obj);
    emit jsonParce(doc.toJson(),"isNetworkAvailable");
}

void SopStoreClinet::callPhone(QString json)
{
    qDebug()<<Q_FUNC_INFO;
    emit voiceCall(json);
}

void SopStoreClinet::opensopApp(QString json)
{
    if(json.contains("http")||json.contains("https")){
    }
    emit openApp(json);
}
void SopStoreClinet::initDBusConnect()
{
    CONNECT_DEBUS(slidesshowResult,SlidesshowResult(QString));
    CONNECT_DEBUS(queryAppStoreResult,QueryAppStoreResult(QString,int));
    CONNECT_DEBUS(queryEnOSResult,QueryEnOSResult(QString,int));
    CONNECT_DEBUS(loginResult,LoginResult(QString));
    CONNECT_DEBUS(preLoginResult,PreLoginResult(QString));
    CONNECT_DEBUS(loginoutResult,LoginoutResult(QString));
    CONNECT_DEBUS(getSonOrgsResult,GetSonOrgsResult(QString));
    CONNECT_DEBUS(changedPwdResult,ChangedPwdResult(QString));
    CONNECT_DEBUS(noticeLastMsg,NoticeLastMsg(QString));
    CONNECT_DEBUS(updateAccountResult,UpdateAccountResult(QString));
    CONNECT_DEBUS(getAccountInfoResult,GetAccountInfoResult(QString));
    CONNECT_DEBUS(getAppLoginStatusResult,GetAppLoginStatusResult(QString));
    CONNECT_DEBUS(loginAuthCodeResult,LoginAuthCodeResult(QString));
}

void SopStoreClinet::jsonParce(QString json,QString fName)
{
    QJsonObject obj;
    QJsonParseError err;

    QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8().data(),&err);
    if(err.error == QJsonParseError::NoError){
        QJsonDocument docTmp;
        obj.insert("fName",fName);
        if(doc.isObject()){
            obj.insert("data",doc.object());
        }else if(doc.isArray()){
            obj.insert("data",doc.array());
        }
        docTmp.setObject(obj);
        qDebug()<<Q_FUNC_INFO<<"callback:"<<docTmp.toJson();
        emit callback(docTmp.toJson());
    }
}
QString SopStoreClinet::dealTime(qint64 msgtime)
{
    QString strDateTime("");
    QDateTime msgDateTime;
    int distance = 0;
    if (!msgtime)
    {
        return strDateTime;
    }
    msgDateTime.setMSecsSinceEpoch(msgtime);
    distance = msgDateTime.daysTo(QDateTime::currentDateTime());
    //今天
    if (qFabs(distance) <= 0)
    {
        strDateTime = msgDateTime.toString("HH:mm");
    }
    //昨天
    else if (qFabs(distance) <= 1)
    {
        strDateTime = "昨天" + QString::fromLocal8Bit(" ") + msgDateTime.toString("HH:mm");
    }
    //前天
    else if (qFabs(distance) <= 2)
    {
        strDateTime = "前天" + QString::fromLocal8Bit(" ") + msgDateTime.toString("HH:mm");
    }
    else
    {
        strDateTime = msgDateTime.toString("MM月dd日") +QString::fromLocal8Bit(" ")+msgDateTime.toString("HH:mm");
    }
    return strDateTime;
}
