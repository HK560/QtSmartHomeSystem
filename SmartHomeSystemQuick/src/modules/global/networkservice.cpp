#include "networkservice.h"
#include <QEventLoop>
NetworkService::NetworkService(QObject *parent) : QObject(parent) {
  m_networkAccessManager = new QNetworkAccessManager(this);

  // connect(m_networkAccessManager, &QNetworkAccessManager::finished, this,
  //         &NetworkService::onRequestFinished);

//  connect(_reply,&QNetworkReply::finished,this,
}

NetworkService::~NetworkService() { delete m_networkAccessManager; }

void NetworkService::get(const QString &url) {
  QNetworkRequest request;
  request.setUrl(QUrl(url));
  m_networkAccessManager->get(request);
}

// void NetworkService::setProxy(const QString &proxyHost, quint16 proxyPort) {
//   QNetworkProxy proxy;
//   proxy.setType(QNetworkProxy::HttpProxy);
//   proxy.setHostName(proxyHost);
//   proxy.setPort(proxyPort);
//   m_networkAccessManager->setProxy(proxy);
// }

bool NetworkService::setProxy(const QString &proxyHost, quint16 proxyPort)
{
    QNetworkProxy proxy;
    proxy.setType(QNetworkProxy::HttpProxy);
    proxy.setHostName(proxyHost);
    proxy.setPort(proxyPort);



    m_networkAccessManager->setProxy(proxy);

    QNetworkRequest request;
    request.setUrl(QUrl("http://www.google.com"));
    request.setHeader(QNetworkRequest::ServerHeader, "Qt Network");


    QNetworkReply *reply = m_networkAccessManager->head(request);
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    bool isValid = false;
    if (reply->error() == QNetworkReply::NoError && reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() >= 200 && reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() < 300) {
        isValid = true;
    }else{
      isValid = false;
      clearProxy();
    }
    reply->deleteLater();
    outInfo << "Proxy: "<<(isValid ? "Valid" : "invalid");
    return isValid;
}


void NetworkService::onFinished(QNetworkReply *reply) {
  emit requestFinished(reply);
}

void NetworkService::setUseSystemProxy(bool useSystemProxy) {
  QNetworkProxyFactory::setUseSystemConfiguration(useSystemProxy);
}
void NetworkService::clearProxy() {
  m_networkAccessManager->setProxy(QNetworkProxy::NoProxy);
}

void NetworkService::setApiToken(const QString &apiToken) {
  m_apiToken = apiToken;
}

void NetworkService::postToChatGPT(const QUrl &url, const QByteArray &data) {
  QNetworkRequest request(url);
  request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
  if (!m_apiToken.isEmpty()) {
    request.setRawHeader("Authorization",
                         QString("Bearer %1").arg(m_apiToken).toUtf8());
  }
  outInfo<<"going to post"<<request.url()<<data;
  QNetworkReply         *_reply;
  _reply = m_networkAccessManager->post(request, data);
}

void NetworkService::onRequestFinished(QNetworkReply *reply) {
  if (reply->error() != QNetworkReply::NoError) {
    emit finished(QByteArray());
    outDebug<<"NetworkService::onRequestFinished"<<reply->error();
    return;
  }

  QByteArray data = reply->readAll();
  emit finished(data);
}




void NetworkService::testNetworkConnectivity() {
  QUrl url("https://www.baidu.com/");
  QNetworkRequest request(url);
  QNetworkReply *reply = m_networkAccessManager->get(request);

  connect(reply, &QNetworkReply::finished, [this, reply]() {
    if (reply->error() == QNetworkReply::NoError) {
      qDebug() << "Network is connected to the internet";
    } else {
      qDebug() << "Network is not connected to the internet";
      qDebug()  << reply->errorString()<<QSslSocket::supportsSsl()<<QSslSocket::sslLibraryBuildVersionString();
    }
    reply->deleteLater();
  });
}
