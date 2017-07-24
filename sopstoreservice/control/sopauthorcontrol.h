#ifndef SOPAUTHORCONTROL_H
#define SOPAUTHORCONTROL_H
#include <QThread>
#include <QObject>
#include "servicecontroller.h"
#include "appmsgnoticethread.h"

class SopAuthorControl : public QObject
{
    Q_OBJECT
public:
    explicit SopAuthorControl(QObject *parent = 0);
    int64 login(std::string user,  std::string pwd,  std::string server);
    void  logout();
    void  changePassword(QString oldPwd,QString newPwd);
    void _changePassword(service::ErrorInfo code);
    void _login(service::ErrorInfo code, int64 userId,int64 time, const std::string veryImg);
    void _logout(service::ErrorInfo code,bool noticeClient);

    void _msgNoticeCb(std::shared_ptr<Msg>msg);
    void _recontactCb(int, std::vector<std::shared_ptr<Chat> >&msgList);
    void _regOfflineMsgCb(std::vector<OfflineMsg>&msgs);
    void setMsgRead(qint64 targetId,qint64 msgId);

    void updateAccountInfo(Account user);
    void _updateAccountInfo(service::ErrorInfo code);

    void getAccountInfo(Account& info );
    int64 userId();

    void getLoginAuthCode(oauthReq req);
    void _getLoginAuthCode(service::ErrorInfo code, const std::string& authCode);
signals:
    void loginAuthCodeResult(QString authCode);
    void loginResult(int code);
    void loginoutResult(int code);
    void changePasswordResult(int code);
    void noticeLastMsg(QString msgContent);
    void updateAccountResult(int code);

    void removeNitifications(QString noticeId);
    void bcNotify(const QString senderId,
                    const QString msgType,
                    const QString content,
                    const QString msgId,
                    const QString sendTime,
                    const QString displayName,
                    const QString senderIconPath,
                    const QString sessionType,
                    int unReadNumber);
public slots:
private:
    void msgNotice(qint64 targetId,qint64 msgId,QString msg,bool showUnread=true,bool offline=true);

    QThread mWorkThread;
    AppMsgNoticeThread* m_pWorkControl;

    std::shared_ptr<service::IAuthService> m_pAuthorService;
    std::shared_ptr<service::IChatService> m_pChatService;
    std::shared_ptr<service::IUserService> m_pUserService;
    int64   mUserId;
    std::string mUser, mPwd, mServer;
};

#endif // SOPAUTHORCONTROL_H
