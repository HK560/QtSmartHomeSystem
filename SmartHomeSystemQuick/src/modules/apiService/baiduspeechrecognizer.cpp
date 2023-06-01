#include "baiduspeechrecognizer.h"
#include "src/modules/global/init.h"

BaiduSpeechRecognizer::BaiduSpeechRecognizer(QObject *parent)
    : QObject(parent) {
  QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
  foreach (const QNetworkInterface &interface, interfaces) {
    if (!(interface.flags() & QNetworkInterface::IsLoopBack) &&
        interface.hardwareAddress().length() > 0) {
      m_macAddress = interface.hardwareAddress();
      break;
    }
  }
}

void BaiduSpeechRecognizer::setAccessKeys(const QString &apiKey,
                                          const QString &secretKey) {
  m_apiKey = apiKey;
  m_secretKey = secretKey;
}

QString BaiduSpeechRecognizer::recognize(const QString &audioFilepath) {

  if (!m_enable){
    outWarn<<"BaiduSpeechRecognizer disabled!";
    return QString();
  } 
  // 获取Access Token
  getAccessToken();

  // 上传音频文件并获取识别结果
  uploadAudioFile(audioFilepath);

  // 返回空字符串
  return QString();
}

void BaiduSpeechRecognizer::getAccessToken() {
  if (!m_accessToken.isEmpty())
    return;

  // 设置请求URL和请求参数
  QString url = "https://aip.baidubce.com/oauth/2.0/token";
  QByteArray postData;
  postData.append("grant_type=client_credentials");
  postData.append("&client_id=");
  postData.append(m_apiKey.toUtf8());
  postData.append("&client_secret=");
  postData.append(m_secretKey.toUtf8());

  // 发送API请求，并解析响应数据
  QByteArray replyData = sendApiRequest(url, postData);
  if (replyData.isEmpty())
    return;
  QJsonDocument jsonDoc = QJsonDocument::fromJson(replyData);
  QJsonObject jsonObj = jsonDoc.object();
  m_accessToken = jsonObj.value("access_token").toString();
  outInfo << "access_token=" << m_accessToken;
}

void BaiduSpeechRecognizer::uploadAudioFile(const QString &audioFilepath) {
  // 打开音频文件
  if(m_accessToken.isEmpty()){
    outWarn << "No access token";
    return ;
  }
  
  QFile audioFile(audioFilepath);
  if (!audioFile.open(QIODevice::ReadOnly))
    return;

  // 读取音频文件内容
  QByteArray audioData = audioFile.readAll();

  // 设置请求URL和请求参数
  QString url = "http://vop.baidu.com/server_api";
  QString contentType = "audio/wav;rate=16000";
  QString base64Data = QString(audioData.toBase64());

  // 设置请求参数
  QString bodyData =
      QString("{\"format\":\"wav\",\"rate\":16000,\"channel\":1,\"token\":\"%"
              "1\",\"cuid\":\"%2\",\"len\":%3,\"speech\":\"%4\"}")
          .arg(m_accessToken)
          .arg(m_macAddress)
          .arg(audioData.size())
          .arg(base64Data);
  QByteArray postData = bodyData.toUtf8();

  // 发送API请求，并解析响应数据
  // outInfo<<"postData="<<postData;

  QByteArray replyData = sendApiRequest(url, postData);
  if (replyData.isEmpty())
    return;
  QJsonDocument jsonDoc = QJsonDocument::fromJson(replyData);
  QJsonObject jsonObj = jsonDoc.object();

  int errorCode = jsonObj.value("err_no").toInt();
  if (errorCode == 0) {
    QJsonArray resultArray = jsonObj.value("result").toArray();
    QString recognitionResult;
    for (int i = 0; i < resultArray.size(); i++) {
      recognitionResult += resultArray.at(i).toString();
    }
    outInfo << "recognitionResult" << recognitionResult;
    emit recognitionFinished(recognitionResult);
  } else {
    QString errorMsg = jsonObj.value("err_msg").toString();
  }
}

QByteArray BaiduSpeechRecognizer::sendApiRequest(const QString &url,
                                                 const QByteArray &postData) {
  // 发送HTTP POST请求
  QNetworkAccessManager manager;
  QNetworkRequest request(url);
  request.setHeader(QNetworkRequest::ContentTypeHeader,
                    "application/x-www-form-urlencoded");
  QNetworkReply *reply = manager.post(request, postData);

  // 等待请求完成
  QEventLoop loop;
  QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
  loop.exec();

  // 检查请求是否出错
  if (reply->error() != QNetworkReply::NoError) {
    qDebug() << "API请求出错：" << reply->errorString();
    reply->deleteLater();
    return QByteArray();
  }

  // 读取响应数据
  QByteArray replyData = reply->readAll();
  outInfo << "收到数据" << replyData;
  reply->deleteLater();

  return replyData;
}
