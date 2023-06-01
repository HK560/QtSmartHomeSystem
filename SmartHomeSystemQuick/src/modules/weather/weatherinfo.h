#ifndef WEATHERINFO_H
#define WEATHERINFO_H

//#include "qobjectdefs.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QTimer>
#include <QTime>
#include <QObject>
 #include "../global/init.h"
 #include "../sqlite/sqlitemgnt.h"
class WeatherInfo:public QObject

{
    Q_OBJECT

    // SqliteMgnt *sqlmgnt;

    QString api = "http://t.weather.sojson.com/api/weather/city/";
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    
    QString cityCode = "101280101";

    QString nowTime;
    QString nowCity;
    QString nowTemp;

    QString temperature;

    QString week[5];
    QString datalb[5];
    QString rangewendu[5];
    QString wtpye[5];
    QString windlb[5];
    QString aqilb[5];


public:

    QVector<QPair<QString, QString>> cityVector;

    WeatherInfo();
    void getWeatherInfo(QString cityCode);


    QString getInfobByIndex(int type, int index);
    QString getNowInfoByIndex(int type);

    QString getCityCode();
    QString setCityCode(QString city);
     QVector<QPair<QString, QString>> searchCityCode(QString cityname);
signals:
    void gotWeatherInfoSignal();

public slots:
    void readData(QNetworkReply *reply);

    

};

#endif // WEATHERINFO_H
