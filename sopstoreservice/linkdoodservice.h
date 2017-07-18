#ifndef LINKDOODSERVICE_H
#define LINKDOODSERVICE_H

#include <QObject>
#include <QDebug>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusArgument>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonParseError>

#include "consttype.h"
#include "servicecontroller.h"
#include "sopauthorcontrol.h"
#include "sopstorecontrol.h"

#include <cconfig.h>

class CSystemPackageManager;
class LinkDoodService : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.vrv.sopstore")
public:
    static void  createService();
    static LinkDoodService* instance();
    static LinkDoodService* m_pInstance;
    static QJsonObject jsonParce(QString json);

    //sopstore
    Q_INVOKABLE void queryEnOS(QString json);
    Q_INVOKABLE void reqUserNameList(QString json);
    Q_INVOKABLE void queryAppStore(QString json);
    Q_INVOKABLE void login(QString json);
    Q_INVOKABLE void loginout();
    Q_INVOKABLE void changedPwd(QString json);
    Q_INVOKABLE void updateAccount(QString json);
    Q_INVOKABLE void getAppLoginStatus();
    Q_INVOKABLE void getAccountInfo();

    Q_INVOKABLE void downloadFile(QString url);
    Q_INVOKABLE void getLoginAuthCode(QString json);
    Q_INVOKABLE void setMessageRead(QString json);
signals:
    void preLoginResult(QString json);
    void loginResult(QString json);
    void loginoutResult(QString json);
    void changedPwdResult(QString json);

    void queryAppStoreResult(QString json,int type);
    void queryEnOSResult(QString json,int type);
    void slidesshowResult(QString json);
    void getSonOrgsResult(QString json);
    void noticeLastMsg(QString msgContent);
    void updateAccountInfoResult(QString json);
    void getAppLoginStatusResult(QString json);
    void getAccountInfoResult(QString json);
    void loginAuthCodeResult(QString authCode);
private slots:
    void onLoginAuthCodeResult(QString authCode);
    void onNoticeLastMsg(QString msgContent);
    void onSingalgetUsersByParamResult(QString josn);
    void onSignalsQueryAppStore(model::respAppStore response,int reqType);
    void onSingalqueryEnOS(model::respEnOS,int type);
    void onLoginoutResult(int flag);
    void onLoginResult(int code);
    void onUpdateAccountInfoResult(int code);
    void onChangedPwdResult(int flag);
    void onGetSonOrgsResult(int code,int allowChat,int contactVisible,std::vector<model::OrganizationInfo> orgs, std::vector<model::EntpriseUserInfo> orgusers);
private:

    void regMetaType();
    QString getHostMacAddress();
    void initSdk();
    void unInitSdk();
    void connectS();
    void initControl();
    void initDBusConnection();

    void handleSlidesshow(model::respAppStore response);
    void handleRespEnOS(model::respEnOS resp,int type);
    void handleRespAppStore(model::respAppStore resp,int type);
    void enterpriseUserBeanToJsonObj(model::EnterpriseUserBean user,QJsonObject& userObj);
    void entpriseUserInfoToJsonObj(model::EntpriseUserInfo user,QJsonObject& userObj);

    void organizationBeanToJsonObj(model::OrganizationBean obean ,QJsonObject& obeanObj);
    void organizationInfoToJsonObj(model::OrganizationInfo org,QJsonObject& obeanObj);

    void appInfoBeanToJsonObj(model::AppInfoBean appinfo,QJsonObject& obj);
    void myAppInfoBeanToJsonObj(model::MyAppInfo appinfo,QJsonObject& obj);
    void appClassifyBeanToJsonObj(model::AppClassifyBean appinfo,QJsonObject& obj);

    LinkDoodService(QObject *parent = 0);
    CSystemPackageManager *m_pPackageManager;
    std::shared_ptr<SopStoreControl> mpSopService;
    std::shared_ptr<SopAuthorControl> mpAuthService;
    CConfig config;
    QString mCurLoginInforJson;

};

#endif // LINKDOODSERVICE_H
