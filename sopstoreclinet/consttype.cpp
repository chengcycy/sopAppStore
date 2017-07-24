#include "consttype.h"

#include <QObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonParseError>
#include <QFile>
#include <QDebug>
QString serviceIP(){

    QFile file(APP_SVR_IP);
    if(file.open(QIODevice::ReadOnly)){
        QJsonParseError err;
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll(),&err);
        file.close();

        if(err.error == QJsonParseError::NoError){
            QJsonObject obj = doc.object();
            QJsonArray arr =  obj.value("sopstoreServers").toArray();
            QString ip = arr.at(0).toObject().value("ip").toString();
            qDebug()<<Q_FUNC_INFO<<"ip:"<<ip;

            return ip;
        }else{
            return "10.152.142.20";
        }
    }else{
        return "10.152.142.20";
    }
}
