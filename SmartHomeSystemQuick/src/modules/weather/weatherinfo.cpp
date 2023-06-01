#include "weatherinfo.h"
#include "../global/init.h"
#include "qjsondocument.h"
#include "qpair.h"
#include "src/modules/weather/weatherinfo.h"
#include <QFile>

WeatherInfo::WeatherInfo()

{
  // sqlmgnt->settingGetWeatherCode(const QString userId)
  bool ok = connect(this->manager, &QNetworkAccessManager::finished, this,
                    &WeatherInfo::readData);
  qDebug() << ok;
  // getWeatherInfo();
}

void WeatherInfo::getWeatherInfo(QString cityCode) {
  outDebug << "doing getWeatherInfo";
  QString uurl = "http://t.weather.sojson.com/api/weather/city/";

  if(cityCode.isEmpty()){
    uurl.append(this->cityCode);
  }else{
    this->cityCode = cityCode;
    uurl.append(cityCode);

  }
  outDebug <<"going to send req:"<<uurl;
  QUrl url(uurl.simplified());
  QNetworkRequest request;
  request.setUrl(url);
  request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
  manager->get(request);
}

void WeatherInfo::readData(QNetworkReply *reply) {
  QByteArray array = reply->readAll();
  outDebug << "doing readData";
  outDebug << array;
  
  QJsonParseError error;
  QJsonDocument doc = QJsonDocument::fromJson(array, &error);

  if (error.error != QJsonParseError::NoError) {
    qDebug("josn error");
    return;
  }
  QJsonObject obj = doc.object();
  // 时间
  QString time = obj.value("time").toString();
  time = nowTime = time.mid(5, 5);
  qDebug() << time;

  // 地区
  QJsonObject cityobj = obj.value("cityInfo").toObject();
  QString city = nowCity = cityobj.value("city").toString();
  qDebug() << city;
  QJsonObject dataobj = obj.value("data").toObject();
  // 实时温度
  QString wendu = nowTemp = dataobj.value("wendu").toString();
  qDebug() << wendu;
  temperature = wendu;
  // 近一周的天气
  QJsonArray forecast_array = dataobj.value("forecast").toArray();
  for (int i = 0; i < 5; i++) {
    QJsonObject weatherobj = forecast_array.at(i).toObject();
    // 最高温度
    QString high = weatherobj.value("high").toString();
    high = high.mid(3);
    qDebug() << high;
    // 最低温度
    QString low = weatherobj.value("low").toString();
    low = low.mid(3, 2);
    qDebug() << low;
    // 温度范围
    QString range_wendu = low + "~" + high;
    qDebug() << range_wendu;
    rangewendu[i] = range_wendu;

    // 日期
    QString ymd = weatherobj.value("ymd").toString();
    ymd = ymd.mid(5);
    qDebug() << ymd;
    // 星期几
    week[i] = weatherobj.value("week").toString();
    qDebug() << week[i];
    if (1) {
      // weeklb[i]->setText(week[i]);
      datalb[i] = ymd;
    }
    // 天气
    QString type = weatherobj.value("type").toString();
    qDebug() << type;
    // if(i == 0) weatherpic = type;
    wtpye[i] = type;
    // type_result(type,i);

    // 风
    QString fx = weatherobj.value("fx").toString();
    QString fl = weatherobj.value("fl").toString();
    QString wind = fx + fl;
    qDebug() << wind;
    windlb[i] = wind;

    // 空气质量
    int aqi = weatherobj.value("aqi").toInt();
    qDebug() << aqi;
    aqilb[i] = aqi;
    // aqi_result(aqi,i);
  }
  // 地区+日期+星期
  //  ui->datalb->setText(city+"  "+time+" "+week[0]);
  // 设置QMainWindow的背景
  //  background_main(weatherpic);
  // 实时天气
  //  ui->currweatherlb->setText(weatherpic+"实时");
  emit gotWeatherInfoSignal();
}

QString WeatherInfo::getInfobByIndex(int type, int index) {
  switch (type) {
  case 0:
    return week[index];
  case 1:
    return datalb[index];
  case 2:
    return rangewendu[index];
  case 3:
    return wtpye[index];
  case 4:
    return windlb[index];
  case 5:
    return aqilb[index];
  default:
    return "";
  }
}

QString WeatherInfo::getNowInfoByIndex(int type) {
  switch (type) {
  case 0:
    return nowTime;
  case 1:
    return nowCity;
  case 2:
    return nowTemp;
  default:
    return "";
  }
}

QString WeatherInfo::getCityCode() {
  return cityCode;
}

QString WeatherInfo::setCityCode(QString cityCode) {
  this->cityCode = cityCode;
  return cityCode;
}

QVector<QPair<QString, QString>> WeatherInfo::searchCityCode(QString cityname) {
  cityVector.clear();

  if(cityname.isEmpty()) return cityVector;
  QFile file("weatherCity.txt");

  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    outWarn << "Cant open weatherCity.txt";
    return cityVector;
  }

  while (!file.atEnd()) {
    QString line = file.readLine();
    if (line.contains(cityname)) {
      QStringList lineList = line.split("=>");
      cityVector.append(
          QPair<QString, QString>(lineList.at(0), lineList.at(1)));
    }
  }
  outDebug<<"susccess get citycode, size:"<<cityVector.size();
  return cityVector;
}
