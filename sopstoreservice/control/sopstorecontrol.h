#ifndef SOPSTORECONTROL_H
#define SOPSTORECONTROL_H
#include <QObject>

#include "servicecontroller.h"

class SopStoreControl : public QObject
{
    Q_OBJECT
public:
    explicit SopStoreControl(QObject *parent = 0);

    void queryEnOS(model::reqEnOS req);
    void _queryEnOS(service::ErrorInfo code, model::respEnOS resp,int type);

    void queryAppStore(int8 type, model::AppStoreQueryParam appStoreQueryParam, model::AppRelationBean appRelation, int64 value64,model::AppStatisticsBean stic);
    void _queryAppStore(service::ErrorInfo code , model::respAppStore response,int type);

    void getUsersByParam(QString key,QString value);
    void _getUsersByParam(service::ErrorInfo err , int32 code, std::string &what, std::vector<model::UserBean> &bean);

signals:
    void singalgetUsersByParamSelft(QString);
    void signalsQueryAppStoreSelft(model::respAppStore response,int reqType);
    void singalqueryEnOSSelft(model::respEnOS,int type);

    void singalgetUsersByParamResult(QString json);
    void signalsQueryAppStore(model::respAppStore response,int reqType);
    void singalqueryEnOS(model::respEnOS,int type);

protected slots:
    void onGetUsersByParamSelf(QString josn );
    void onSignalsQueryAppStoreSelf(model::respAppStore response,int reqType);
    void onSingalqueryEnOSSelft(model::respEnOS resp,int type);
private:
    std::shared_ptr<service::ISopStoreService> m_pSopService;
};

#endif // SOPSTORECONTROL_H
