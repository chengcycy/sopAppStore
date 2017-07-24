#include "linkdoodservice.h"
#include "csystempackagemanager.h"
#include "packet.h"
#include <QNetworkInterface>
#include <QDir>
#include "consttype.h"

std::shared_ptr<service::IMClient> g_client;
LinkDoodService* LinkDoodService::m_pInstance ;

void LinkDoodService::createService()
{
    if (!m_pInstance) {
        qDebug() << " create LinkDoodService parent !!!  ";
        m_pInstance = new LinkDoodService();
    }
}

LinkDoodService *LinkDoodService::instance()
{
    return m_pInstance;
}

QJsonObject LinkDoodService::jsonParce(QString json)
{
    QJsonObject obj;
    QJsonParseError err;

    QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8().data(),&err);
    if(err.error == QJsonParseError::NoError){
        if(doc.isObject()){
            return doc.object();
        }
    }
    return obj;
}

void LinkDoodService::regMetaType()
{
    qRegisterMetaType<imsdksopstore::AppStoreQueryParam>("imsdksopstore::AppStoreQueryParam>");
    qRegisterMetaType<imsdksopstore::AppRelationBean>("imsdksopstore::AppRelationBean");
    qRegisterMetaType<model::respAppStore>("model::respAppStore");
    qRegisterMetaType<service::ErrorInfo>("service::ErrorInfo");
    qRegisterMetaType<int32>("int32");
    qRegisterMetaType<std::string>("std::string");
    qRegisterMetaType<std::vector<std::string>>("std::vector<std::string>");
    qRegisterMetaType<std::map<std::string, std::string>>("std::map<std::string, std::string>");
    qRegisterMetaType<int64>("int64");
    qRegisterMetaType<model::reqEnOS>("model::reqEnOS");
    qRegisterMetaType<model::respEnOS>("model::respEnOS");

    qRegisterMetaType<std::vector<model::OrganizationInfo> >("std::vector<model::OrganizationInfo>");
    qRegisterMetaType<std::vector<model::EntpriseUserInfo> >("std::vector<model::EntpriseUserInfo>");
}

QString LinkDoodService::getHostMacAddress()
{
    QList<QNetworkInterface> nets = QNetworkInterface::allInterfaces();// 获取所有网络接口列表
    int nCnt = nets.count();
    QString strMacAddr = "";
    for(int i = 0; i < nCnt; i ++)
    {
        // 如果此网络接口被激活并且正在运行并且不是回环地址，则就是我们需要找的Mac地址
        if(nets[i].flags().testFlag(QNetworkInterface::IsUp) && nets[i].flags().testFlag(QNetworkInterface::IsRunning) && !nets[i].flags().testFlag(QNetworkInterface::IsLoopBack))
        {
            strMacAddr = nets[i].hardwareAddress();
            break;
        }
    }
    return strMacAddr;
}

void LinkDoodService::initSdk()
{
    if(m_pPackageManager == NULL){
        m_pPackageManager = new CSystemPackageManager(this);
        qDebug() << Q_FUNC_INFO<<"m_pPackageManager";
    }
    QString m_sInstallPath = m_pPackageManager->packageInfo(LINKDOOD_SOPID)->installPath();
    QString crtPath = m_sInstallPath;
    crtPath += "/crt/linkdood.crt";
    std::string appDataPath = "/data/data/com.vrv.sopstore/";
    std::string appCrtPath =crtPath.toStdString();

    g_client = service::getClient();

    QDir appDir(APP_DIR);
    if(!appDir.exists()){
        appDir.mkdir(APP_DIR);
    }
    std::shared_ptr<service::IConfigService> pSrvConfig = CONFIGSERVICE;
    pSrvConfig->setAppName("sopstore");


    qDebug()<<Q_FUNC_INFO<<"1";
    model::AppInfo appInfo;
    appInfo.appName = "sopstore";
    appInfo.deviceInfo = "pc-yuanxin";
    appInfo.deviceType = 2;
    QString macAddr = getHostMacAddress();
    qDebug()<<Q_FUNC_INFO<<"macAddr:"<<macAddr;
    if(macAddr.isEmpty()){
        macAddr = "E0:DB:55:C7:95:8D";
    }
    appInfo.mac = macAddr.toStdString();
    QString ver = m_pPackageManager->packageInfo(LINKDOOD_SOPID)->versionName();
    appInfo.appVersion = ver.toStdString();

    bool ret = g_client->init(appDataPath,appCrtPath,appInfo);
    qDebug()<<Q_FUNC_INFO<<"ret:"<<ret;
    if(!ret){
        qDebug()<<Q_FUNC_INFO<<"zhuceshibai";
    }
    if(ret)
    {
        initControl();
        if(pSrvConfig){
            pSrvConfig->setMsgParserMode(false);

        }
    }

}

void LinkDoodService::unInitSdk()
{

}

void LinkDoodService::connectS()
{
    qDebug()<<Q_FUNC_INFO;

    QObject::connect(mpSopService.get(),SIGNAL(singalgetUsersByParamResult(QString)),this,SLOT(onSingalgetUsersByParamResult(QString)));
    QObject::connect(mpSopService.get(),SIGNAL(signalsQueryAppStore(model::respAppStore,int)),this,SLOT(onSignalsQueryAppStore(model::respAppStore,int)));
    QObject::connect(mpSopService.get(),SIGNAL(singalqueryEnOS(model::respEnOS,int)),this,SLOT(onSingalqueryEnOS(model::respEnOS,int)));

    QObject::connect(mpAuthService.get(),SIGNAL(noticeLastMsg(QString)),this,SLOT(onNoticeLastMsg(QString)));
    QObject::connect(mpAuthService.get(),SIGNAL(changePasswordResult(int)),this,SLOT(onChangedPwdResult(int)));
    QObject::connect(mpAuthService.get(),SIGNAL(updateAccountResult(int)),this,SLOT(onUpdateAccountInfoResult(int)));
    QObject::connect(mpAuthService.get(),SIGNAL(loginoutResult(int)),this,SLOT(onLoginoutResult(int)));
    QObject::connect(mpAuthService.get(),SIGNAL(loginResult(int)),this,SLOT(onLoginResult(int)));
    QObject::connect(mpAuthService.get(),SIGNAL(loginAuthCodeResult(QString)),this,SLOT(onLoginAuthCodeResult(QString)));
}


void LinkDoodService::initDBusConnection()
{
    QDBusConnection bus = QDBusConnection::sessionBus();
    bool bSuccess = false;
    bSuccess = QDBusConnection::sessionBus().registerService(DBUS_DOOD_SERVICE);
    bSuccess = bus.registerObject(DBUS_DOOD_PATH, this,QDBusConnection::ExportAllInvokables|QDBusConnection::ExportAllSignals);
}

void LinkDoodService::initControl()
{
    qDebug()<<Q_FUNC_INFO;
    mpAuthService.reset(new SopAuthorControl());
    mpSopService.reset(new SopStoreControl());
    connectS();
}

void LinkDoodService::queryEnOS(QString json)
{
    qDebug()<<Q_FUNC_INFO<<"req Data:"<<json;
    model::reqEnOS req;
    QJsonObject obj = jsonParce(json);
    int64 enterId = obj.value("enterId").toDouble();
    int64 orId = obj.value("orgId").toString().toLongLong();

    req.type = obj.value("type").toInt();
    //    req.value64 = enterId;
    if(req.type == 3){
        req.value64 = enterId;
        req.params["orgId"] = (obj.value("orgId").toString()).toStdString();
        req.params["pageSize"] = "1000";
    }else if(req.type == 4){
        req.value64 = enterId;
        req.value64_2 = (orId==1?2920082167275313:orId);//2920082167275313
        qDebug()<<Q_FUNC_INFO<<"enter:"<<enterId<<",orId:"<<orId;
    }else if(req.type == 2){
        //        req.value64 = orId;
        //        req.valuestr = obj.value("name").toString().toStdString();

        //        req.value64 = enterId;

        req.type = 8;
        req.params["pageSize"] = "1000";
        req.params["unitID"] = (obj.value("orgId").toString()).toStdString();
        req.params["name"] = (obj.value("name").toString()).toStdString();
        qDebug()<<Q_FUNC_INFO<<"unitID:"<< req.params["unitID"].c_str()<<",name:"<< req.params["name"].c_str();
    }
    mpSopService->queryEnOS(req);
}

void LinkDoodService::reqUserNameList(QString json)
{
    qDebug()<<Q_FUNC_INFO<<json;

    QJsonObject obj = jsonParce(json);

    QString userName = obj.value("userName").toString();
    mpSopService->getUsersByParam("",userName);
}


//struct AppStatisticsBean{
//	/* 应用类型：
//	* 1：门户应用类型 2.普通应用类型
//	*/
//	std::string appType;
//	/* 应用ID */
//	std::string appID;
//	/* 用户ID */
//	std::string userID;
//	/* 组织机构ID*/
//	std::string orgID;
//	/* 组织机构CODE */
//	std::string orgCode;
//	/* 组织机构CODE */
//	std::string unitID;
//}

void LinkDoodService::queryAppStore(QString json)
{
    model::AppStoreQueryParam appStoreQueryParam;
    model::AppRelationBean appRelation;
    model::AppStatisticsBean stic;
    int64 value;
    int type;

    qDebug()<<Q_FUNC_INFO<<"req:"<<json;
    QJsonObject obj = jsonParce(json);
    type = obj.value("type").toString().toInt();
    if(type == 2){
        appStoreQueryParam.userId = mpAuthService->userId();
        appStoreQueryParam.pageSize = 50;
        appStoreQueryParam.appClassifyId = 0;
        appStoreQueryParam.searchType = 2;
        appStoreQueryParam.pageNum = 1;
    }else if(type == 3){
        appStoreQueryParam.userId = mpAuthService->userId();
        appStoreQueryParam.appName = (obj.value("appName").toString()).toStdString();
    }else if(type == 6){
        appRelation.userID = mpAuthService->userId();
        appRelation.appID = obj.value("id").toDouble();
        appRelation.classifyID = obj.value("classify").toDouble();
        appRelation.relationStatus = 1;
    }else if(type == 7){
        value =obj.value("id").toDouble();
        appRelation.userID = mpAuthService->userId();
        //        appRelation.appID = obj.value("id").toDouble();
        qDebug()<<Q_FUNC_INFO<<"appRelation.appID:"<<appRelation.appID;
    }else if(type == 1){
        appStoreQueryParam.userId = mpAuthService->userId();
    }else if(type == 8){
        stic.userID = (QString::number(mpAuthService->userId())).toStdString();
        stic.appType =(obj.value("appType").toString()).toStdString();
        stic.appID = (obj.value("appID").toString()).toStdString();
        stic.orgID = (obj.value("orgID").toString()).toStdString();
        stic.orgCode =(obj.value("orgCode").toString()).toStdString();
        stic.unitID = (obj.value("unitID").toString()).toStdString();
        qDebug()<<Q_FUNC_INFO<<"dd:"<<stic.userID.c_str()<<","<<stic.appType.c_str()<<","<<stic.appID.c_str()<<","<<stic.orgID.c_str()<<","<<stic.orgCode.c_str()<<","<<stic.unitID.c_str();
    }
    mpSopService->queryAppStore(type,appStoreQueryParam,appRelation,value,stic);
}

void LinkDoodService::login(QString json)
{
    qDebug()<<Q_FUNC_INFO<<json;

    QJsonObject obj = jsonParce(json);
    QString uID = obj.value("usbkeyidentification").toString()+":7";
    QString pwd = obj.value("password").toString();

    mCurLoginInforJson = json;
    mpAuthService->login(uID.toStdString(),pwd.toStdString(),serviceIP().toStdString());
}

void LinkDoodService::loginout()
{
    mpAuthService->logout();
}
void LinkDoodService::changedPwd(QString json)
{
    QString oldPwd,newPwd;
    QJsonObject obj = jsonParce(json);

    qDebug()<<Q_FUNC_INFO<<"json:"<<json;

    oldPwd = obj.value("oldPwd").toString();
    newPwd = obj.value("newPwd").toString();
    mpAuthService->changePassword(oldPwd,newPwd);
}

void LinkDoodService::updateAccount(QString json)
{
    model::Account account;
    QJsonObject obj = jsonParce(json);
    int type = obj.value("type").toInt();
    if(type == 1){
        account.name = obj.value("name").toString().toStdString();
    }else if(type == 2){
        account.phone = obj.value("phone").toString().toStdString();
        QJsonDocument doc;
        QJsonObject objTmp;
        objTmp.insert("enMobile",account.phone.value().c_str());
        objTmp.insert("telPhone",obj.value("telPhone").toString());
        doc.setObject(objTmp);
        QString enPhone = doc.toJson();
        qDebug()<<Q_FUNC_INFO<<"enPhone:"<<enPhone;
        account.extends = enPhone.toStdString();
    }
    else if(type == 3){
        account.gender = obj.value("gander").toInt();
    }
    qDebug()<<Q_FUNC_INFO<<"json:"<<json;
    mpAuthService->updateAccountInfo(account);
}

void LinkDoodService::getAppLoginStatus()
{
    emit getAppLoginStatusResult(config.value("acountStrJson").toString());
}

void LinkDoodService::getAccountInfo()
{
    model::Account info;
    mpAuthService->getAccountInfo(info);

    QJsonDocument doc;
    QJsonObject obj;
    obj.insert("gender",info.gender.value());
    obj.insert("phone",info.phone.value().c_str());
    obj.insert("name",info.name.value().c_str());

    QJsonObject telphone = jsonParce(QString::fromStdString(info.extends.value()));
    obj.insert("telPhone",telphone.value("telPhone").toString());
    QString phone = QString::fromStdString(info.phone.value());
    if(phone.isEmpty()){
        obj.insert("phone",telphone.value("enMobile").toString());
    }
    doc.setObject(obj);
    QString strJson = doc.toJson();

    qDebug()<<Q_FUNC_INFO<<"strJson:"<<strJson;
    emit getAccountInfoResult(strJson);
}

void LinkDoodService::downloadFile(QString url)
{

}

void LinkDoodService::getLoginAuthCode(QString json)
{
    QJsonObject obj = jsonParce(json);
    model::oauthReq req;
    req.userID = QString::number(mpAuthService->userId()).toStdString();
    req.appID = obj.value("appID").toString().toStdString();
    req.accountType = "4";
    mpAuthService->getLoginAuthCode(req);
}

void LinkDoodService::setMessageRead(QString json)
{
    QJsonObject obj = jsonParce(json);
    mpAuthService->setMsgRead(obj.value("targetId").toDouble(),obj.value("msgId").toDouble());
}

void LinkDoodService::onLoginAuthCodeResult(QString authCode)
{
    emit loginAuthCodeResult(authCode);
}

void LinkDoodService::onNoticeLastMsg(QString msgContent)
{
    emit noticeLastMsg(msgContent);
}
void LinkDoodService::handleSlidesshow(model::respAppStore response)
{
    QJsonDocument doc;
    QJsonArray arr;
    QString BASE = "http://"+serviceIP()+"/";

    for(auto i: response.hotNewsBeans){

        QJsonObject obj;
        QString img = BASE+ i.newsCover.c_str();
        QString title = i.newsTitle.c_str();

        QString newsContent = i.newsContent.c_str();
        int32 id = i.id;
        int64 createUserID = i.createUserID;
        QString createTime = i.createTime.c_str();
        QString updateTime = i.updateTime.c_str();

        obj.insert("newsContent",newsContent);
        obj.insert("id",id);
        obj.insert("createUserID",createUserID);
        obj.insert("createTime",createTime);
        obj.insert("updateTime",updateTime);

        obj.insert("img",img);
        obj.insert("title",title);
        QString url = BASE+"app-market/HotNews/findHotNewsMoble.vrv?id="+QString::number(i.id);
        obj.insert("url",url);
        arr.append(obj);


    }
    doc.setArray(arr);
    qDebug()<<Q_FUNC_INFO<<"handleSlidesshow:"<<doc.toJson();
    emit slidesshowResult(doc.toJson());
}

void LinkDoodService::handleRespEnOS(respEnOS resp,int type)
{

    QString strJson;
    QJsonDocument doc;
    QJsonObject obj;

    obj.insert("code",resp.code);

    QJsonObject nodeObj;
    nodeObj.insert("code",resp.nodes.code);
    nodeObj.insert("what",resp.nodes.what.c_str());
    nodeObj.insert("oPower",resp.nodes.oPower.c_str());
    QJsonArray users;
    for(auto user:resp.nodes.users){
        QJsonObject userObj;
        enterpriseUserBeanToJsonObj(user,userObj);
        users.append(userObj);
    }
    nodeObj.insert("users",users);
    QJsonArray obeans;
    for(auto obean:resp.nodes.obeans){
        QJsonObject obeanObj;
        organizationBeanToJsonObj(obean,obeanObj);
        users.append(obeanObj);
    }
    nodeObj.insert("obeans",obeans);
    obj.insert("nodes",nodeObj);

    QJsonArray orgSearchUsers;
    for(auto orgSearchUser:resp.orgSearchUsers){
        QJsonObject searOrg;
        searOrg.insert("power",orgSearchUser.power.c_str());
        QJsonObject ub;
        enterpriseUserBeanToJsonObj(orgSearchUser.ub,ub);
        searOrg.insert("ub",ub);
        orgSearchUsers.append(searOrg);
    }
    obj.insert("orgSearchUsers",orgSearchUsers);

    QJsonObject searchRet;
    QJsonArray uBeans;
    for(auto uBean:resp.searchRet.uBeans){
        QJsonObject ub;
        enterpriseUserBeanToJsonObj(uBean,ub);
        uBeans.append(ub);
    }
    searchRet.insert("uBeans",uBeans);
    searchRet.insert("resultFlag",resp.searchRet.resultFlag.c_str());
    obj.insert("searchRet",searchRet);

    qDebug()<<Q_FUNC_INFO<<"type:"<<type;
    QJsonArray entUsers;
    for(auto user:resp.entUsers){
        QJsonObject ub;
        enterpriseUserBeanToJsonObj(user,ub);
        entUsers.append(ub);
    }

    obj.insert("entUsers",entUsers);
    QJsonArray depts;
    for(auto dept : resp.depts){//"orgCode": "100110231018",
        if(dept.orgCode == "100110231018"){
            continue;
        }
        QJsonObject jsdept;
        organizationBeanToJsonObj(dept,jsdept);
        depts.append(jsdept);
    }
    obj.insert("depts",depts);

    doc.setObject(obj);
    strJson = doc.toJson();
    qDebug()<<Q_FUNC_INFO<<"org111111111:"<<strJson;
    emit queryEnOSResult(strJson,type);
}

void LinkDoodService::handleRespAppStore(respAppStore resp,int type)
{
    QJsonDocument doc;
    QJsonObject   obj;

    obj.insert("code",resp.code);
    obj.insert("what",resp.what.c_str());

    QJsonObject appStore;
    appStore.insert("msg",resp.appStore.msg.c_str());
    appStore.insert("pageSize",resp.appStore.pageSize);
    appStore.insert("pageNum",resp.appStore.pageNum);
    appStore.insert("totalCount",resp.appStore.totalCount);
    appStore.insert("totalPage",resp.appStore.totalPage);
    appStore.insert("code",resp.appStore.code);
    QJsonArray appInfoList;
    for(auto appinfo :resp.appStore.appInfoList){
        QJsonObject appinfoJson;
        appInfoBeanToJsonObj(appinfo,appinfoJson);
        appInfoList.append(appinfoJson);
    }
    appStore.insert("appInfoList",appInfoList);
    obj.insert("appStore",appStore);

    QJsonArray appInfos;
    for(auto myAppInfo : resp.appInfos){
        QJsonObject myappinfoJson;
        myAppInfoBeanToJsonObj(myAppInfo,myappinfoJson);
        appInfos.append(myappinfoJson);
    }
    obj.insert("appInfos",appInfos);

    QJsonArray classifyBeans;
    for(auto classifyBean : resp.classifyBeans){
        QJsonObject classifyBeanJson;
        appClassifyBeanToJsonObj(classifyBean,classifyBeanJson);
        classifyBeans.append(classifyBeanJson);
    }
    obj.insert("classifyBeans",classifyBeans);

    QJsonArray appBeans;
    for(auto appBean : resp.appBeans){
        QJsonObject appBeanJson;
        appInfoBeanToJsonObj(appBean,appBeanJson);
        appBeans.append(appBeanJson);
    }
    obj.insert("appBeans",appBeans);

    QJsonObject ret;
    ret.insert("message",resp.ret.message.c_str());
    ret.insert("code",resp.ret.code);
    ret.insert("result",resp.ret.result);
    obj.insert("ret",ret);

    QJsonObject statResult;
    statResult.insert("msg",resp.statResult.msg.data());
    statResult.insert("code",resp.statResult.code.data());
    obj.insert("statResult",statResult);

    doc.setObject(obj);
    QString strJson = doc.toJson();
    qDebug()<<Q_FUNC_INFO<<"strJson:"<<strJson;
    emit queryAppStoreResult(strJson,type);
}

void LinkDoodService::enterpriseUserBeanToJsonObj(EnterpriseUserBean user, QJsonObject &userObj)
{
    userObj.insert("userID",user.userID);
    userObj.insert("enterpriseID",user.enterpriseID);
    userObj.insert("orgID",user.orgID);
    userObj.insert("roleID",user.roleID);
    userObj.insert("enName",user.Enname.c_str());
    userObj.insert("duty",user.duty.c_str());
    userObj.insert("enMail",user.Enmail.c_str());
    userObj.insert("enMobile",user.Enmobile.c_str());
    userObj.insert("status",user.status);
    userObj.insert("orderNum",user.orderNum);
    userObj.insert("newOrgID",user.newOrgID);
    userObj.insert("orgName",user.orgName.c_str());
    userObj.insert("extend",user.extend.c_str());
    userObj.insert("accountName",user.accountName.c_str());
    userObj.insert("bizStatus",user.bizStatus);
    userObj.insert("userHead",user.userHead.c_str());
    userObj.insert("telPhone","");
    qDebug()<<Q_FUNC_INFO<<"userExtend:"<<user.userExtend.c_str();
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(user.userExtend.c_str(),&err);
    if(err.error == QJsonParseError::NoError){
        QJsonObject objTmp = doc.object();
        if(objTmp.contains("enMobile")){
            userObj.insert("enMobile",objTmp.value("enMobile").toString());
        }
        if(objTmp.contains("telPhone")){
            userObj.insert("telPhone",objTmp.value("telPhone").toString());
        }
    }
}

void LinkDoodService::entpriseUserInfoToJsonObj(EntpriseUserInfo user, QJsonObject &userObj)
{
    userObj.insert("userID",user.userID);
    userObj.insert("enterpriseID",user.enterpriseID);
    userObj.insert("orgID",user.orgID);
    userObj.insert("roleID",user.roleID);

    userObj.insert("enMail",user.enMail.c_str());
    userObj.insert("enMobile",user.enMobile.c_str());
    userObj.insert("enName",user.enName.c_str());

    userObj.insert("duty",user.duty.c_str());
    userObj.insert("status",user.status);
    userObj.insert("orderNum",user.orderNum);
    userObj.insert("newOrgID",user.newOrgID);
    userObj.insert("orgName",user.orgName.c_str());
    userObj.insert("extend",user.extend.c_str());
    userObj.insert("accountName",user.accountName.c_str());
    userObj.insert("bizStatus",user.bizStatus);
    userObj.insert("userHead",user.userHead.c_str());
}

void LinkDoodService::organizationBeanToJsonObj(OrganizationBean obean, QJsonObject &obeanObj)
{
    obeanObj.insert("orgID",obean.orgID);
    obeanObj.insert("enterpriseID",obean.enterpriseID);
    obeanObj.insert("orgName",obean.orgName.c_str());
    obeanObj.insert("orgCode",obean.orgCode.c_str());
    obeanObj.insert("leaf",obean.leaf);
    obeanObj.insert("parentOrgID",obean.parentOrgID);
    obeanObj.insert("remark",obean.remark.c_str());
    obeanObj.insert("orderNum",obean.orderNum);
    obeanObj.insert("extend",obean.extend.c_str());
    obeanObj.insert("resCode",obean.resCode);
    obeanObj.insert("exlRow",obean.exlRow);

    obeanObj.insert("subOrgNum",obean.subOrgNum);
    obeanObj.insert("subUserNum",obean.subUserNum);
}

void LinkDoodService::organizationInfoToJsonObj(OrganizationInfo obean, QJsonObject &obeanObj)
{
    obeanObj.insert("orgID",obean.orgID);
    obeanObj.insert("enterpriseID",obean.enterpriseID);
    obeanObj.insert("orgName",obean.orgName.c_str());
    obeanObj.insert("orgCode",obean.orgCode.c_str());
    obeanObj.insert("leaf",obean.leaf);
    obeanObj.insert("parentOrgID",obean.parentOrgID);
    obeanObj.insert("remark",obean.remark.c_str());
    obeanObj.insert("orderNum",obean.orderNum);
    obeanObj.insert("subOrgNum",obean.subOrgNum);
    obeanObj.insert("subUserNum",obean.subUserNum);
}

void LinkDoodService::appInfoBeanToJsonObj(AppInfoBean appinfo, QJsonObject &obj)
{
    obj.insert("id",appinfo.id);
    obj.insert("classify",appinfo.classify);
    obj.insert("type",appinfo.type);
    obj.insert("status",appinfo.status);
    obj.insert("createUserID",appinfo.createUserID);
    obj.insert("sort",appinfo.sort);

    obj.insert("column1",appinfo.column1.c_str());
    obj.insert("column2",appinfo.column2.c_str());
    obj.insert("column3",appinfo.column3.c_str());
    obj.insert("updateTime",appinfo.updateTime.c_str());
    obj.insert("createTime",appinfo.createTime.c_str());
    obj.insert("secret",appinfo.secret.c_str());
    obj.insert("key",appinfo.key.c_str());
    obj.insert("orgIds",appinfo.orgIds.c_str());
    obj.insert("activityName",appinfo.activityName.c_str());

    obj.insert("packageName",appinfo.packageName.c_str());
    obj.insert("version",appinfo.version.c_str());
    obj.insert("homeUrl",appinfo.homeUrl.c_str());
    QString BASE = "http://"+serviceIP()+"/";
    obj.insert("icon",BASE+appinfo.icon.c_str());
    obj.insert("downloadUrl",/*BASE+*/appinfo.downloadUrl.c_str());
    obj.insert("name",appinfo.name.c_str());
}

//struct AppClassifyBean {
//    int32       classifyID;     ///< 分类主键
//    std::string classifyName;   ///< 分类名称
//    int64       createUserID;   ///< 创建者userID
//    int32       classifyStatus; ///< 分类状态 1：正常 2：已删除
//    std::string createTime;     ///< 创建时间
//    std::string updateTime;     ///< 更新时间-新建分类时初始值与创建时间一致
//    int32       classifySort;   ///< 排序字段-未设置排序值时默认为1
//    std::string classifyColumn1;///< 预留字段1
//    std::string classifyColumn2;///< 预留字段2
//    std::string classifyColumn3;///< 预留字段3
//};

void LinkDoodService::appClassifyBeanToJsonObj(AppClassifyBean appinfo, QJsonObject &obj)
{

    obj.insert("classifyID",appinfo.classifyID);
    obj.insert("createUserID",appinfo.createUserID);
    obj.insert("classifyStatus",appinfo.classifyStatus);
    obj.insert("classifySort",appinfo.classifySort);
    obj.insert("createUserID",appinfo.createUserID);
    obj.insert("classifySort",appinfo.classifySort);

    obj.insert("classifyName",appinfo.classifyName.c_str());
    obj.insert("createTime",appinfo.createTime.c_str());
    obj.insert("updateTime",appinfo.updateTime.c_str());
    obj.insert("updateTime",appinfo.updateTime.c_str());
    obj.insert("classifyColumn1",appinfo.classifyColumn1.c_str());
    obj.insert("classifyColumn2",appinfo.classifyColumn2.c_str());
    obj.insert("classifyColumn3",appinfo.classifyColumn3.c_str());

}

void LinkDoodService::myAppInfoBeanToJsonObj(MyAppInfo appinfo, QJsonObject &obj)
{
    QJsonObject appClassify;
    appClassifyBeanToJsonObj(appinfo.appClassify,appClassify);
    obj.insert("appClassify",appClassify);
    obj.insert("code",appinfo.code);
    obj.insert("msg",appinfo.msg.c_str());

    QJsonArray appInfoList;
    for(auto app:appinfo.appInfoList){
        QJsonObject jsonObj;
        appInfoBeanToJsonObj(app,jsonObj);
        appInfoList.append(jsonObj);
    }
    obj.insert("appInfoList",appInfoList);
}

void LinkDoodService::onSignalsQueryAppStore(model::respAppStore response,int reqType)
{
    if(reqType == 5){
        handleSlidesshow(response);
    }else{
        handleRespAppStore(response,reqType);
    }
}

void LinkDoodService::onSingalgetUsersByParamResult(QString json)
{
    emit preLoginResult(json);
}


void LinkDoodService::onSingalqueryEnOS(model::respEnOS resp,int type)
{
    qDebug()<<Q_FUNC_INFO;
    handleRespEnOS(resp,type);
}

void LinkDoodService::onLoginoutResult(int code)
{
    qDebug()<<Q_FUNC_INFO<<"code:"<<code;
    if(code ==0){
        mCurLoginInforJson = "";
        config.setValue("acountStrJson",mCurLoginInforJson);
    }
    QString json="{\"code\":"+QString::number(code)+"}";
    emit loginoutResult(json);
}

void LinkDoodService::onLoginResult(int code)
{
    if(code == 0 || code == 113){
        config.setValue("acountStrJson",mCurLoginInforJson);
    }else{
        mCurLoginInforJson = "";
        config.setValue("acountStrJson",mCurLoginInforJson);
    }
    qDebug()<<Q_FUNC_INFO<<"code:"<<code;
    QString json="{\"code\":"+QString::number(code)+"}";
    emit loginResult(json);

    //   QString app = APP_DIR+QString::fromStdString("com.vrv.linkDood");
    //   QString url = "http://baqi.linkdood.cn/at010/0/file/20170504/1905/a_Mzm8_133d000000362a01.sop";
    //   mpAuthService->downloadExternalFile(app,url);
}

void LinkDoodService::onUpdateAccountInfoResult(int code)
{
    qDebug()<<Q_FUNC_INFO<<"code:"<<code;
    QString json="{\"code\":"+QString::number(code)+"}";
    emit updateAccountInfoResult(json);
}

void LinkDoodService::onChangedPwdResult(int code)
{
    qDebug()<<Q_FUNC_INFO<<"code:"<<code;
    QString json="{\"code\":"+QString::number(code)+"}";
    emit changedPwdResult(json);
}

void LinkDoodService::onGetSonOrgsResult(int code, int allowChat, int contactVisible, std::vector<model::OrganizationInfo> orgs, std::vector<model::EntpriseUserInfo> orgusers)
{
    QJsonDocument doc;
    QJsonObject obj;
    obj.insert("code",code);
    obj.insert("allowChat",allowChat);
    obj.insert("contactVisible",contactVisible);

    QJsonArray orgsJson;
    //    qDebug()<<Q_FUNC_INFO<<"orgs:"<<orgs.size()<<",orgusers:"<<orgusers.size();
    for(auto org:orgs){
        QJsonObject orgObj;
        organizationInfoToJsonObj(org,orgObj);
        orgsJson.append(orgObj);
    }

    QJsonArray orgusersJson;
    for(auto user:orgusers){
        QJsonObject userObj;
        entpriseUserInfoToJsonObj(user,userObj);
        //        qDebug()<<Q_FUNC_INFO<<"user:"<<user.orgName.c_str();
        orgusersJson.append(userObj);
    }
    obj.insert("orgs",orgsJson);
    obj.insert("orgusers",orgusersJson);

    doc.setObject(obj);
    QString strJson = doc.toJson();

    //    qDebug()<<Q_FUNC_INFO<<"strJson:"<<strJson;

    emit getSonOrgsResult(strJson);
}
LinkDoodService::LinkDoodService(QObject *parent) : QObject(parent)
{
    regMetaType();
    m_pPackageManager = NULL;
    //registerDoodDataTypes();

    mCurLoginInforJson = "";
    initSdk();
    initDBusConnection();
}
