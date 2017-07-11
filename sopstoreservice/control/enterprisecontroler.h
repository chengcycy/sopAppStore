#ifndef ENTERPRISECONTROLER_H
#define ENTERPRISECONTROLER_H

#endif // ENTERPRISECONTROLER_H
#include<QObject>
#include<IExtService.h>
#include<servicecontroller.h>
#include <QDebug>
#include "packet.h"

class EnterpriseControler:public QObject
{
    Q_OBJECT
public:
    void init();
    EnterpriseControler(QObject *parent = 0);
    ~EnterpriseControler();
    void onUpdateRootFinished(int code);
    //调用底层接口并通过回调获取结果
    void onEnterpriseAvatarChanged(int64 userid,std::string avatar);
    void getOrgRemark(QString orgId);
    void _getOrgRemark(service::ErrorInfo info, OrganizationInfo&orginfo);
    void getSonOrgs(QString orgid);
    void _getSonOrgs(service::ErrorInfo info, int8 allowChat, int8 contactVisible,std::vector<model::OrganizationInfo>& orgs, std::vector<model::EntpriseUserInfo>& orgusers);

    void getOnlineStates(QStringList& userid);
    void _getOnlineStates(std::vector<OnlineState>& states);

    void getOrgUserInfo(QString userid);
    void _getOrgUserInfo(service::ErrorInfo info, std::vector<EntpriseUserInfo>& orguser);

signals:
    //将结果抛给linkdoodservice层
    void enterpriseAvatarChanged(QString userid,QString avatar);
    void getSonOrgsResult(int code,int allowChat,int contactVisible,std::vector<model::OrganizationInfo> orgs, std::vector<model::EntpriseUserInfo> orgusers);
    //void getOnlineStatesResult(QOnlineStateList onlinestatelist);
    //void getOrgUserInfoResult(int code,OrgUser orguser);
    void getOrgRemarkResult(QString orgId,QString remark);
private:
    std::shared_ptr<service::IExtService> m_pEnterpriseService;
};
