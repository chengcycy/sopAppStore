#include "sopauthorcontrol.h"
#include <QDebug>
#include <QSettings>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>

#include "../../sopstoreclinet/consttype.h"

SopAuthorControl::SopAuthorControl(QObject *parent) : QObject(parent)
{
    m_pAuthorService = AUTHSERVICE;
    m_pChatService = CHATSERVICE;
    m_pUserService = USERSERVICE;
    mUserId = 0;
    mUser = mPwd = mServer="";

    m_pWorkControl = new AppMsgNoticeThread(this);
    m_pWorkControl->moveToThread(&mWorkThread);
    connect(this,SIGNAL(removeNitifications(QString)),m_pWorkControl,SLOT(onRemoveNitification(QString)));
    connect(this,SIGNAL(bcNotify(QString,QString,QString,QString,QString,QString,QString,QString,int)),m_pWorkControl,SLOT(onBcNotify(QString,QString,QString,QString,QString,QString,QString,QString,int)));
    mWorkThread.start();
    m_pChatService->regOfflineMsgCb(std::bind(&SopAuthorControl::_regOfflineMsgCb,this,std::placeholders::_1));
    m_pChatService->regMsgNoticeCb(std::bind(&SopAuthorControl::_msgNoticeCb,this,std::placeholders::_1));
    m_pChatService->regRecontactCb(std::bind(&SopAuthorControl::_recontactCb,this,std::placeholders::_1,std::placeholders::_2));
}

int64 SopAuthorControl::login(std::string user, std::string pwd, std::string server)
{
    mUser = user;
    mPwd = pwd;
    mServer = server;

    m_pAuthorService->login(user,pwd,server,std::bind(&SopAuthorControl::_login,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4));
}

void SopAuthorControl::logout()
{
    m_pAuthorService->logout(std::bind(&SopAuthorControl::_logout,this,std::placeholders::_1,true));
}

void SopAuthorControl::changePassword(QString oldPwd, QString newPwd)
{
    qDebug()<<Q_FUNC_INFO;
    m_pAuthorService->changePassword(oldPwd.toStdString(),newPwd.toStdString(),std::bind(&SopAuthorControl::_changePassword,this,std::placeholders::_1));
}

void SopAuthorControl::_changePassword(service::ErrorInfo code)
{
    qDebug()<<Q_FUNC_INFO;
    emit changePasswordResult(code);
}

void SopAuthorControl::_login(service::ErrorInfo code,int64 userId,int64 time, const std::string veryImg)
{
    qDebug()<<Q_FUNC_INFO<<"code:"<<code<<"userId:"<<userId;
    if(code == 0){
        mUserId = userId;
    }else if(code == 113){
        m_pAuthorService->logout(std::bind(&SopAuthorControl::_logout,this,std::placeholders::_1,false));
        return;
    }
    emit loginResult(code);
}
void SopAuthorControl::_logout(service::ErrorInfo code,bool noticeClient)
{
    if(noticeClient){
        emit loginoutResult(code);
    }else{
        login(mUser,mPwd,mServer);
    }
}

void SopAuthorControl::_msgNoticeCb(std::shared_ptr<Msg> msg)
{

    msgNotice(msg->targetId,msg->msgId,msg->body.c_str(),true,false);

    QSettings config(APP_DATA_CONFIG,QSettings::IniFormat);
    int clientStatus = config.value("clientStatus",0).toInt();
    if(clientStatus == 0){
        QJsonParseError err;
        QJsonDocument doc = QJsonDocument::fromJson(msg->body.c_str(),&err);
        QString message = doc.object().value("body").toString();

        if(err.error == QJsonParseError::NoError){
            doc = QJsonDocument::fromJson(message.toUtf8().data(),&err);
            QJsonObject obj = doc.object();
            emit bcNotify(QString::number(msg->targetId),"2",obj.value("msg").toString(),QString::number(msg->msgId),QString::number(msg->time),obj.value("appName").toString(),"","",1);
        }

    }
}

void SopAuthorControl::_recontactCb(int, std::vector<std::shared_ptr<Chat> > &msgList)
{
    for(auto i : msgList){
        qDebug()<<Q_FUNC_INFO<<"msgList:"<<i->lastMsg.c_str();
        msgNotice(i->sendUserId,i->lastMsgId,i->lastMsg.c_str(),i->unreadCount>0,true);
    }
}

void SopAuthorControl::_regOfflineMsgCb(std::vector<OfflineMsg> &msgs)
{
    qDebug()<<Q_FUNC_INFO<<"offline msg==========================";
    for(auto item:msgs){
       if(item.msg != NULL){
           msgNotice(item.msg->targetId,item.msg->msgId,item.msg->body.c_str(),true,true);
       }
    }
}

void SopAuthorControl::setMsgRead(qint64 targetId, qint64 msgId)
{
    m_pChatService->setMessageRead(targetId,msgId);
}

void SopAuthorControl::updateAccountInfo(Account user)
{
    user.id = mUserId;
    qDebug()<<Q_FUNC_INFO<<"phone:"<<user.phone.value().c_str();
    qDebug()<<Q_FUNC_INFO<<"sex:"<<user.gender.value();
    m_pUserService->updateAccountInfo(user,std::bind(&SopAuthorControl::_updateAccountInfo,this,std::placeholders::_1));
}

void SopAuthorControl::_updateAccountInfo(service::ErrorInfo code)
{
    emit updateAccountResult(code);
}

void SopAuthorControl::getAccountInfo(Account &info)
{
    m_pUserService->getAccountInfo(info);
    //    qDebug()<<Q_FUNC_INFO<<"phone:"<<info.phone.value().c_str()<<",ex:"<<info.extends.value().c_str();
}

int64 SopAuthorControl::userId()
{
    return mUserId;
}

void SopAuthorControl::getLoginAuthCode(oauthReq req)
{
    qDebug()<<Q_FUNC_INFO<<"code111111:"<<req.appID.c_str()<<",userId:"<<req.userID.c_str();
    m_pAuthorService->getLoginAuthCode(req,std::bind(&SopAuthorControl::_getLoginAuthCode,this,std::placeholders::_1,std::placeholders::_2));
}

void SopAuthorControl::_getLoginAuthCode(service::ErrorInfo code, const std::string &authCode)
{
    qDebug()<<Q_FUNC_INFO<<"code:"<<code<<",authCode:"<<authCode.c_str();
    emit loginAuthCodeResult(QString::fromStdString(authCode));
}

void SopAuthorControl::msgNotice(qint64 targetId, qint64 msgId, QString msg,bool showUnread,bool offline)
{
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(msg.toUtf8().data(),&err);
    QString message = doc.object().value("body").toString();

    if(err.error == QJsonParseError::NoError && !message.isEmpty()){
        QJsonDocument doc1;
        QJsonObject obj;
        obj.insert("targetId",targetId);
        obj.insert("msgId",msgId);
        obj.insert("message",message);
        obj.insert("showUnread",showUnread);
        obj.insert("offline",offline);
        doc1.setObject(obj);
        emit noticeLastMsg(doc1.toJson());
    }
}
