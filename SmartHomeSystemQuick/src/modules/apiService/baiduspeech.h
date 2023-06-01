#ifndef BAIDUSPEECH_H
#define BAIDUSPEECH_H

#include "../global/init.h"
#include "src/modules/global/init.h"
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QEventLoop>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QList>
#include <QMediaPlayer>
#include <QNetworkInterface>
#include <QObject>
#include <QUrl>
#include <QUrlQuery>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

class BaiduSpeech : public QObject {
  Q_OBJECT
public:
  BaiduSpeech(QObject *parent = nullptr) {
    m_macAddress = "57891421";

    m_filename = QCoreApplication::applicationDirPath() + "/tmp";
    // QDir dir;
    // dir.setPath(m_filename);
    // dir.removeRecursively();
  }
  ~BaiduSpeech() {
    if (m_player != nullptr) {
      delete m_player;
      m_player = nullptr;
    }
  }

  void setEnabled(const bool &enabled) { m_enable = enabled; };
  bool getEnabled() { return m_enable; }

  bool textToSpeech(QString text) {
    if (m_accessToken.isEmpty()||!m_enable) {
      outWarn << "No access token or disabled";
      return false;
    }

    QString url = "http://tsn.baidu.com/text2audio";

    QUrl apiUrl(url);

    QUrlQuery query;
    query.addQueryItem("tex", text);
    query.addQueryItem("lan", "zh");
    query.addQueryItem("tok", m_accessToken);
    query.addQueryItem("ctp", "1");
    query.addQueryItem("cuid", m_macAddress);
    query.addQueryItem("spd", "5");
    query.addQueryItem("pit", "5");
    query.addQueryItem("vol", "5");
    query.addQueryItem("per", "0");

    apiUrl.setQuery(query);

    QNetworkAccessManager manager;
    QNetworkRequest request(apiUrl);

    QNetworkReply *reply = manager.get(request);

    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    QByteArray data = reply->readAll();
    // outDebug << "baiduspeech got data: " << data;

    int statusCode =
        reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    // QByteArray data = reply->readAll();

    if (statusCode != 200) {
      qDebug() << "Failed to get speech. Status code:" << statusCode
               << "Response body:" << data;
      return false;
    }

    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date =
        current_date_time.toString("yyyy_MM_dd_hh_mm_ss_zzz");
    QString filename = m_filename + "/" + current_date + "ttsAudio.mp3";
    QFile file(filename);
    if (file.open(QIODevice::ReadWrite)) {
      file.write(data);
      file.close();

      outDebug << "Speech saved to" << filename;
      play(filename);
      return true;
    } else {
      outDebug << "Failed to save speech to" << filename;
      return false;
    }
  }

  void setAccessKeys(QString apiKey, QString secretKey) {
    m_apiKey = apiKey;
    m_secretKey = secretKey;

    QUrl url("https://openapi.baidu.com/oauth/2.0/token");
    QUrlQuery query;
    query.addQueryItem("grant_type", "client_credentials");
    query.addQueryItem("client_id", m_apiKey);
    query.addQueryItem("client_secret", m_secretKey);
    url.setQuery(query);

    QNetworkAccessManager manager;
    QNetworkRequest request(url);

    QNetworkReply *reply = manager.get(request);

    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    QByteArray data = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject jsonObj = jsonDoc.object();

    if (jsonObj.contains("access_token")) {
      m_accessToken = jsonObj.value("access_token").toString();
      qDebug() << "Access Token:" << m_accessToken;
    } else {
      qDebug() << "Failed to get Access Token";
    }
  }

  //   void setSecretKey(QString secretKey) { m_secretKey = secretKey; }

  void play(QString filename) {
    if (m_player != nullptr) {
      delete m_player;
      m_player = nullptr;
    }
    m_player = new QMediaPlayer();
    m_player->setMedia(QUrl::fromLocalFile(filename));
    m_player->setVolume(50);
    m_player->play();
    // m_player.
  }

private:
  bool m_enable;
  QString m_apiKey;
  QString m_secretKey;
  QString m_accessToken;
  QString m_macAddress;
  QMediaPlayer *m_player = nullptr;
  QString m_filename;
};

#endif // BAIDUSPEECH_H