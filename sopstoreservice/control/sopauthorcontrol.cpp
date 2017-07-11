#include "sopauthorcontrol.h"
#include <QDebug>

SopAuthorControl::SopAuthorControl(QObject *parent) : QObject(parent)
{
    m_pAuthorService = AUTHSERVICE;
    m_pChatService = CHATSERVICE;
    m_pUserService = USERSERVICE;
    mUserId = 0;

    m_pWorkControl = new AppMsgNoticeThread(this);
    m_pWorkControl->moveToThread(&mWorkThread);
    connect(this,SIGNAL(removeNitifications(QString)),m_pWorkControl,SLOT(onRemoveNitification(QString)));
    connect(this,SIGNAL(bcNotify(QString,QString,QString,QString,QString,QString,QString,QString,int)),m_pWorkControl,SLOT(onBcNotify(QString,QString,QString,QString,QString,QString,QString,QString,int)));
    mWorkThread.start();

    m_pChatService->regMsgNoticeCb(std::bind(&SopAuthorControl::_msgNoticeCb,this,std::placeholders::_1));
    m_pChatService->regRecontactCb(std::bind(&SopAuthorControl::_recontactCb,this,std::placeholders::_1,std::placeholders::_2));
}

int64 SopAuthorControl::login(std::string user, std::string pwd, std::string server)
{
    m_pAuthorService->login(user,pwd,server,std::bind(&SopAuthorControl::_login,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4));
}

void SopAuthorControl::logout()
{
    m_pAuthorService->logout(std::bind(&SopAuthorControl::_logout,this,std::placeholders::_1));
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
    }
    emit loginResult(code);
}
void SopAuthorControl::_logout(service::ErrorInfo code)
{
    emit loginoutResult(code);
}

void SopAuthorControl::_msgNoticeCb(std::shared_ptr<Msg> msg)
{
    qDebug()<<Q_FUNC_INFO<<"msg:"<<msg->body.c_str();
    emit noticeLastMsg(msg->body.c_str());

//    QString msgContent;
//    if(msg != nullptr){
//        if(msg->msgType == MSG_TYPE_TEXT){
//            msgContent = msg->body.c_str();
//        }else if(msg->msgType == MSG_TYPE_IMG){
//            msgContent = "您收到一条图片消息";
//        }else if(msg->msgType == MSG_TYPE_FILE){
//            msgContent = "您收到一条图文消息";
//        }else if(msg->msgType == MSG_TYPE_PICTEXT){
//            msgContent = "您收到一条图文消息";
//        }else if(msg->msgType == MSG_TYPE_DYNEXPRESSION){
//            msgContent = "您收到一条新消息";
//        }else if(msg->msgType == MSG_TYPE_TIP){
//            msgContent = msg->body.c_str();
//        }else{
//            msgContent = "您收到一条新消息";
//        }
//        emit noticeLastMsg(msgContent);
//    }
}

void SopAuthorControl::_recontactCb(int, std::vector<std::shared_ptr<Chat> > &msgList)
{
//    if(msgList.size()>0){
//        std::shared_ptr<Chat> chat = msgList.at(msgList.size() -1);
//        if(chat != nullptr){
//            emit noticeLastMsg(chat->lastMsg.c_str());
//        }
//    }
    for(auto i : msgList){
         emit noticeLastMsg(i->lastMsg.c_str());
    }
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
