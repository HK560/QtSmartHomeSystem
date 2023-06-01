#include "chatgptapi.h"
#include "src/modules/global/init.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

ChatGptApi::ChatGptApi(QObject *parent, QNetworkAccessManager *networkService)
    : QObject(parent), _qnam(networkService) {
  // m_networkService = new NetworkService(this);
}

ChatGptApi::~ChatGptApi() {}

void ChatGptApi::setApiToken(const QString &apiToken) { m_apiToken = apiToken; }

void ChatGptApi::setApiUrl(const QString &apiUrl) { m_apiUrl = apiUrl; }

void ChatGptApi::setMaxTokens(int maxTokens) { m_maxTokens = maxTokens; }

void ChatGptApi::sendMessage(const QString &message) {
  //   QUrl url(QString("https://openai.api.z2y.io/v1/chat/completions"));
  QNetworkRequest request;
  request.setUrl(QUrl(m_apiUrl));
  request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
  request.setRawHeader("Authorization",
                       QString("Bearer %1").arg(m_apiToken).toUtf8());
  // QUrlQuery query;
  // query.addQueryItem("model", "text-davinci-003");
  // query.addQueryItem("prompt", m_prompt);
  // query.addQueryItem("stream", "false");
  // query.addQueryItem("temperature", QString::number(m_temperature));
  // query.addQueryItem("max_tokens", QString::number(m_maxTokens));

#if (0)
  QJsonObject jsonObject;
  jsonObject["model"] = "text-davinci-003";
  jsonObject["stream"] = "false";

  jsonObject["prompt"] = m_chatHistory;
  jsonObject["max_tokens"] = QString::number(m_maxTokens);
  jsonObject["temperature"] = QString::number(m_temperature);
  jsonObject["stop"] = "\n";
  QJsonDocument jsonDoc(jsonObject);
  QByteArray postData = jsonDoc.toJson(QJsonDocument::Compact);

  // if (!m_stop.isEmpty()) {
  //     query.addQueryItem("stop", m_stop);
  // }
  // url.setQuery(query);
#endif
  outInfo << "User message sent:" << message;
  QMap<QString, QString> map;
  map.insert("role", "user");
  map.insert("content", message);
  _arrRequest.append(map);

  QJsonArray array;
  for (auto el : _arrRequest) {
    QJsonObject prompt;
    prompt.insert("role", el.value("role"));
    prompt.insert("content", el.value("content"));
    array.append(prompt);
  }
  QJsonObject parameters;
  parameters.insert("model", "gpt-3.5-turbo");
  parameters.insert("messages", array);

  QJsonDocument requestBody(parameters);
  qDebug() << requestBody.toJson();
  //   _reply = _qnam.post(request, requestBody.toJson());

  _reply = _qnam->post(request, requestBody.toJson());
  QObject::connect(_reply, &QNetworkReply::finished, this,
                   &ChatGptApi::handleResponse);
}

void ChatGptApi::handleResponse() {
  if (_reply->error() == QNetworkReply::NoError) {
    QByteArray responseData = _reply->readAll();
    outInfo << responseData;
    QJsonDocument responseDoc = QJsonDocument::fromJson(responseData);
    QJsonObject responseObject = responseDoc.object();
    QJsonValue choicesValue = responseObject.value("choices");
    if (choicesValue.isArray() && choicesValue.toArray().size() > 0) {
      QJsonValue textValue = choicesValue.toArray()
                                 .at(0)
                                 .toObject()
                                 .value("message")
                                 .toObject()
                                 .value("content");
      qDebug() << textValue.toString();
      if (textValue.isString()) {

        //                            _items.append(new QListWidgetItem());
        //                            _items.at(_items.length()-1)->setIcon(QIcon(":/res/openai_logo.svg"));
        //                            _ctxList->addItem(_items.at(_items.length()-1));

        QMap<QString, QString> mres;
        mres.insert("role", "assistant");
        mres.insert("content", textValue.toString());
        _arrRequest.append(mres);

        emit responseReceived(textValue.toString());
      }
    }
  } else {
    qDebug() << "Error:" << _reply->errorString();
    QByteArray responseData = _reply->readAll();
    emit errorOccurred(responseData);
  }
  _reply->deleteLater();
  //                _btnQuery->setEnabled(true);
}
void ChatGptApi::onFinished(const QByteArray &data) {
  outInfo << data;
  QJsonDocument json = QJsonDocument::fromJson(data);

  if (json.isNull() || !json.isObject()) {
    emit errorOccurred("Invalid JSON data received");
    return;
  }

  QJsonObject obj = json.object();
  if (!obj.contains("choices") || !obj["choices"].isArray()) {
    emit errorOccurred("Invalid JSON data received");
    return;
  }

  QJsonArray choices = obj["choices"].toArray();
  if (choices.isEmpty()) {
    emit errorOccurred("No text generated");
    return;
  }

  QString text = choices[0].toObject()["text"].toString();
}

void ChatGptApi::clearChatHistory() {
  _arrRequest.clear();

  QMap<QString, QString> map2;
  map2.insert("role", "system");
  if (!m_command.isEmpty()) {
    map2.insert("content", m_command + m_FocusedCommand_1+m_apilist+m_FocusedCommand_2);
  } else {
    map2.insert("content", m_FocusedCommand_1+m_apilist+m_FocusedCommand_2);
  }
  _arrRequest.append(map2);

  // QMap<QString, QString> map;
  // map.insert("role", "user");
  // map.insert("content", m_FocusedCommand);
  // _arrRequest.append(map);
}

void ChatGptApi::updateApiList(const QString &apilist) {
  if (apilist.isEmpty()) {
    m_apilist = "但是现在目前还没有能控制的设备和功能。";
  } else {
    m_apilist = "那么根据目前能控制的设备和功能，得到的设备数据字符串为: " + apilist;
  }
}