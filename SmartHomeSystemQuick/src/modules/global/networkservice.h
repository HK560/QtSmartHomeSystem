#ifndef NETWORKSERVICE_H
#define NETWORKSERVICE_H

#include <QNetworkAccessManager>
#include <QNetworkProxy>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include "init.h"

class NetworkService : public QObject {
  Q_OBJECT
public:
  explicit NetworkService(QObject *parent = nullptr);
  ~NetworkService();
  void get(const QString &url);
  bool setProxy(const QString &proxyHost, quint16 proxyPort);
  void setUseSystemProxy(bool useSystemProxy);
  void clearProxy();

  void setApiToken(const QString &apiToken);
  void postToChatGPT(const QUrl &url, const QByteArray &data);
  void testNetworkConnectivity();

  QNetworkAccessManager * getNetworkAccessManager(){
    return m_networkAccessManager;
  }

signals:
  void requestFinished(QNetworkReply *reply);
  void finished(const QByteArray &data);
private slots:
  void onFinished(QNetworkReply *reply);
  void onRequestFinished(QNetworkReply *reply);

private:
  QNetworkAccessManager *m_networkAccessManager;
  QString m_apiToken;

};

#endif // NETWORKSERVICE_H
