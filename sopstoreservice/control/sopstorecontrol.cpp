#include "sopstorecontrol.h"
#include <QDebug>
#include "packet.h"

SopStoreControl::SopStoreControl(QObject *parent) : QObject(parent)
{
    m_pSopService = SOPSERVICE;
    QObject::connect(this,SIGNAL(signalsQueryAppStoreSelft(model::respAppStore,int)),this,SLOT(onSignalsQueryAppStoreSelf(model::respAppStore,int)));
    QObject::connect(this,SIGNAL(singalgetUsersByParamSelft(QString)),this,SLOT(onGetUsersByParamSelf(QString)));
    QObject::connect(this,SIGNAL(singalqueryEnOSSelft(model::respEnOS,int)),this,SLOT(onSingalqueryEnOSSelft(model::respEnOS,int)));
}

void SopStoreControl::queryEnOS(model::reqEnOS req)
{
  //    qDebug()<<Q_FUNC_INFO<<"req.type:"<<req.type<<",req.value64:"<<req.value64<<",value64_2:"<<req.value64_2<<",<req.params:"<<req.params["orgId"].c_str();

    if(req.type == 8){
        req.type = 3;
        m_pSopService->queryEnOS(req,std::bind(&SopStoreControl::_queryEnOS,this,std::placeholders::_1, std::placeholders::_2,2));
    }else{
        qDebug()<<Q_FUNC_INFO<<"req.type:"<<req.type<<",req.value64:"<<req.value64<<",value64_2:"<<req.value64_2<<",<req.params[orgId]:"<<req.params["orgId"].c_str();
        m_pSopService->queryEnOS(req,std::bind(&SopStoreControl::_queryEnOS,this,std::placeholders::_1, std::placeholders::_2,req.type));
    }

}

void SopStoreControl::_queryEnOS(service::ErrorInfo code, model::respEnOS resp,int type)
{
    emit singalqueryEnOSSelft(resp,type);
}

void SopStoreControl::queryAppStore(int8 type, model::AppStoreQueryParam appStoreQueryParam, model::AppRelationBean appRelation, int64 value64,model::AppStatisticsBean stic)
{
   qDebug()<<Q_FUNC_INFO<<"appRelation.appID:"<<appRelation.appID;
    m_pSopService->queryAppStore(type,appStoreQueryParam,appRelation,value64,stic,std::bind(&SopStoreControl::_queryAppStore,this,std::placeholders::_1,std::placeholders::_2,type));
}

void SopStoreControl::_queryAppStore(service::ErrorInfo code, model::respAppStore response,int reqType)
{
    qDebug()<<Q_FUNC_INFO<<"code:"<<code<<","<<response.statResult.code.c_str()<<","<<response.statResult.msg.c_str();
    emit signalsQueryAppStore(response,reqType);
}

void SopStoreControl::getUsersByParam(QString key, QString value)
{
    qDebug()<<Q_FUNC_INFO;
    std::map<std::string,std::string> map;
    map["searchname"] = value.toStdString();
    qDebug()<<Q_FUNC_INFO<<"vaue:"<<value;
    m_pSopService->getUsersByParam(map,std::bind(&SopStoreControl::_getUsersByParam,this,std::placeholders::_1, std::placeholders::_2,std::placeholders::_3, std::placeholders::_4));
}

void SopStoreControl::_getUsersByParam(service::ErrorInfo err, int32 code, std::string &what, std::vector<model::UserBean> &bean)
{
    qDebug()<<Q_FUNC_INFO<<"sezie:"<<bean.size()<<",code:"<<err;
    QString json = "[";
    for(auto i : bean){
        json.append(QString ::fromStdString(i.entExtend));
        json.append(",");
    }
    if(json.length()>1){
        json.remove(json.length() -1,1);
    }
    json.append("]");
    qDebug()<<Q_FUNC_INFO<<"josn:"<<json;
    emit singalgetUsersByParamSelft(json);
}

void SopStoreControl::onGetUsersByParamSelf(QString josn)
{
    emit singalgetUsersByParamResult(josn);
}

void SopStoreControl::onSignalsQueryAppStoreSelf(model::respAppStore response, int reqType)
{
    emit signalsQueryAppStore(response,reqType);
}

void SopStoreControl::onSingalqueryEnOSSelft(model::respEnOS resp,int type)
{
    emit singalqueryEnOS(resp,type);
}
