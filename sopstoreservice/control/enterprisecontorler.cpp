#include "IMClient.h"
#include <enterprisecontroler.h>
#include<iostream>
#include<sstream>
#include<string>



void EnterpriseControler::init()
{
    m_pEnterpriseService= IEXTSERVICE;
    m_pEnterpriseService->regOrgMemHeadImgUpdateCb(std::bind(&EnterpriseControler::onEnterpriseAvatarChanged,this,std::placeholders::_1,std::placeholders::_2));
    m_pEnterpriseService->regEntUpdateFinishCb(std::bind(&EnterpriseControler::onUpdateRootFinished,this,std::placeholders::_1));
}

EnterpriseControler::EnterpriseControler(QObject *parent):QObject(parent)
{
    init();
}

EnterpriseControler::~EnterpriseControler()
{
}

void EnterpriseControler::onUpdateRootFinished(int code)
{
    //qDebug() << Q_FUNC_INFO<<"updateorgdata";
    //getSonOrgs("0");
}

void EnterpriseControler::onEnterpriseAvatarChanged(int64 userid, std::string avatar)
{
    qDebug()<<Q_FUNC_INFO<<userid<<avatar.c_str();
    emit enterpriseAvatarChanged(QString::number(userid),QString::fromStdString(avatar));
}

void EnterpriseControler::getOrgRemark(QString orgId)
{
    m_pEnterpriseService->getOrgInfo(orgId.toLongLong(),std::bind(&EnterpriseControler::_getOrgRemark,this,std::placeholders::_1,std::placeholders::_2));
}

void EnterpriseControler::_getOrgRemark(service::ErrorInfo info, OrganizationInfo &orginfo)
{
    qDebug()<<Q_FUNC_INFO<<"code:"<<info<<QString::fromStdString(orginfo.remark);
    emit getOrgRemarkResult(QString::number(orginfo.orgID),QString::fromStdString(orginfo.remark));
}
void EnterpriseControler::getSonOrgs(QString orgid)
{
    qDebug() << Q_FUNC_INFO<<"userxxorg:"<<orgid;
    int64 org_id;
    org_id=orgid.toLongLong();
    int type;
    if(orgid=="0"){
        type=0;
    }
    else{
        type=1;
    }
    m_pEnterpriseService->getVisibleOrgUsers(0,org_id,std::bind(&EnterpriseControler::_getSonOrgs,this,std::placeholders::_1,
                                                                  std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5));
}
void EnterpriseControler::_getSonOrgs(service::ErrorInfo info, int8 allowChat, int8 contactVisible,std::vector<model::OrganizationInfo>& orgs, std::vector<model::EntpriseUserInfo>& orgusers)
{

   emit getSonOrgsResult(info,allowChat,contactVisible,orgs,orgusers);
}



void EnterpriseControler::getOnlineStates(QStringList &userid)
{
    std::vector<int64> Ids;
    for(auto i :userid)
    {
        int64  id;
        std::stringstream str(i.toStdString());
        str>>id;
        Ids.push_back(id);
    }
//    service::IMClient::getClient()->getEnterprise()->getOnlineStates(Ids,
//                                                                     std::bind(&EnterpriseControler::_getOnlineStates,this,
//                                                                               std::placeholders::_1));
}
void EnterpriseControler::_getOnlineStates(std::vector<OnlineState> &states)
{
    //qDebug() << Q_FUNC_INFO;
//    QOnlineStateList onlinestatelist;
//    for(auto i:states){
//        QOnlineState  onlinestate;
//        onlinestate.userid=QString::number(i.userID);
//        onlinestate.connectId=QString::number(i.connectID);
//        onlinestate.deviceType=QString::number(i.deviceType);
//        onlinestate.flag=QString::number(i.flag);
//        onlinestatelist.insert(onlinestatelist.size(),onlinestate);
//    }
//    emit getOnlineStatesResult(onlinestatelist);
}




void EnterpriseControler::getOrgUserInfo(QString userid)
{

    m_pEnterpriseService->queryEntUserOneById(userid.toLongLong(),std::bind(&EnterpriseControler::_getOrgUserInfo,this,
                                              std::placeholders::_1,std::placeholders::_2));
}
void EnterpriseControler::_getOrgUserInfo(service::ErrorInfo info,std::vector<model::EntpriseUserInfo>& orguser)
{
//    qDebug() << Q_FUNC_INFO<<orguser.size();
//    OrgUser Qorguser;
//    if(orguser.size() > 0){
//        Qorguser= orguserToQorguser(orguser.at(0));
//        emit getOrgUserInfoResult(info,Qorguser);
//    }
}

