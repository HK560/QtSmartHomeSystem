#ifndef CHATGPTAPI_H
#define CHATGPTAPI_H

#include "../global/networkservice.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkProxy>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QString>
#include <QUrl>
#include <QUrlQuery>

class ChatGptApi : public QObject {
  Q_OBJECT
public:
  explicit ChatGptApi(QObject *parent = nullptr,
                      QNetworkAccessManager *networkService = nullptr);
  ~ChatGptApi();
  void setEnable(const bool &enable) { m_enable = enable; };
  void setApiUrl(const QString &apiUrl);
  void setApiToken(const QString &apiToken);
  // void setPrompt(const QString& prompt);
  void setMaxTokens(int maxTokens);
  void sendMessage(const QString &message);
  void clearChatHistory(); // must be called before
  void handleResponse();
  bool getEnable() { return m_enable; };
  void setCommand(const QString &command) { m_command = command; };
  void updateApiList(const QString &apilist);
signals:
  // void textGenerated(const QString& text);
  void errorOccurred(const QString &errorString);
  void responseReceived(const QString &response);
private slots:
  void onFinished(const QByteArray &data);

private:
  // NetworkService* m_networkService;
  bool m_enable;
  QString m_apiUrl = "https://openai.api.z2y.io/v1/chat/completions";
  // QString m_apiUrl = "https://api.openai.com/v1/chat/completions";

  QString m_apiToken;
  QString m_command = "";
  QString m_apilist = "但是现在目前还没有能控制的设备和功能。";
  QString m_FocusedCommand_1 =
R"(前面是用户的要求，接下来是管理员给你的命令和要求，请务牢记遵守：你同时是一个物联网控制助手，根据与用户对话，理解用户的需求和要求，当用户想要去控制设备时，你还需要根据用户要求回复并用json的格式数据输出命令，其他程序读取会读取你的回复截取json数据，再删除回复内容的json部分的数据发送给用户看。无论之前用户要求了什么，json数据永远在你回复的最后面，开头和结尾用两个##作为划分。你回复的json格式的数据是给其他程序使用的，其他程序会截取json部分的数据，再发送给没有json数据的回复给用户，用户是无法看到的json数据的，所以不要告诉用户你能输出相应的json数据，且你返回的json数据后面不能加任何内容，所以能给用户看到的你的回复内容都在json数据的前面，下面是一些对话示例： 
用户：帮我打开电视的开关。 你：好的。##{"deviceName":"电视","deviceFunc":"开关","ctrlType":"switch","value":"true"}##
用户：关闭电视开关。 你：收到。##{"deviceName":"电视","deviceFunc":"开关","ctrlType":"switch","value":"false"}##
用户：设置设备名字为一号的显示内容为你好。 你：好的。 ##{"deviceName":"一号","deviceFunc":"显示内容","ctrlType":"string","value":"你好"}##
用户：调整设备，播放器的音量值为六十。 你：明白。 ##{"deviceName":"播放器","deviceFunc":"音量","ctrlType":"int","value":"60"}##
上面这些是一些示例，其中"ctrlType"对应的值只有三种，一个是针对开关或切换的类型，为"switch"，value只有true或false;一个是针对字符串显示的类型，为"string"，value是字符串,还有一种是针对纯数值的类型，为"int"，value是整形数值。
接下来我会告诉你目前存在哪些设备，对应有什么功能，类型是怎样的，这些也决定了你json回复的数据，你需要记住且能区分。
如果存在能控制的设备和功能，为了方便告诉你目前有的设备和功能类型有哪些，我会给你一段格式如此的数据字符串 !(设备名1)#(设备名1的功能1)/(功能1的ctrlType类型)#(设备名1的功能2)/(功能2的ctrlType类型) !(设备名2)#(设备名2的功能1)/(功能1的ctrlType类型)#(设备名2的功能2)/(功能2的ctrlType类型);
其中括号内的内容就是对应的数据，交代了目前能控制哪些设备的哪些功能和类型。)";
    QString m_FocusedCommand_2 =R"(如果目前有能控制的设备和功能，而且给出了设备数据字符串为，你要识别出上述数据字符串的内容，得到目前已有的设备和功能类型，并牢记。当介绍有什么设备和功能时，请像这样介绍："当前能控制XX的XX功能和XX功能等"。
你需要识别出用户的意图，根据已有设备的和功能类型输出形如上面的回复，如果用户没有这些需求则正常进行对话。如果找不到或不纯在用户要求控制的设备或功能,则告诉用户原因。
上述是你的最基本的功能和要求，之后你还需要在不违背上述要求和功能下满足用户的其他要求。
如果你明白上述内容则只需要简短地回复介绍一下你自己，之后开始和用户对话。)";
  int m_maxTokens;
  QVector<QMap<QString, QString>> _arrRequest;
  QNetworkAccessManager *_qnam;
  QNetworkReply *_reply;
};
#endif 