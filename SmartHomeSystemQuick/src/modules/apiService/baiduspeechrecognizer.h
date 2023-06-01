#ifndef BAIDUSPEECHRECOGNIZER_H
#define BAIDUSPEECHRECOGNIZER_H

#include "qjsonarray.h"
#include <QByteArray>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QUrl>

#include "../global/init.h"
#include <QByteArray>
#include <QCoreApplication>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkInterface>
#include <QNetworkReply>
#include <QObject>
#include <QUrl>

class BaiduSpeechRecognizer : public QObject {
  Q_OBJECT
public:
  explicit BaiduSpeechRecognizer(QObject *parent = nullptr);

  // 设置API Key和Secret Key
  void setAccessKeys(const QString &apiKey, const QString &secretKey);

  // 识别音频文件
  QString recognize(const QString &audioFilepath);

  void setEnabled(const bool &enabled){m_enable = enabled;};
  bool getEnabled(){return m_enable;}
signals:
  // 识别完成信号，参数为识别结果
  void recognitionFinished(const QString &recognitionResult);

private:
  // 获取Access Token
  void getAccessToken();

  // 上传音频文件并获取识别结果
  void uploadAudioFile(const QString &audioFilepath);
  QByteArray sendApiRequest(const QString &url, const QByteArray &postData);

private:
  bool m_enable;
  QString m_apiKey;      // API Key
  QString m_secretKey;   // Secret Key
  QString m_accessToken; // Access Token
  QString m_macAddress;
};

#endif // BAIDUSPEECHRECOGNIZER_H

