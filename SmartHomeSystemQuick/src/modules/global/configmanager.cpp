#include "configmanager.h"
#include <QTextCodec>
ConfigManager::ConfigManager() {
  // m_settings = new QSettings("MyApp", "MyApp");
  QMutexLocker locker(&m_mutex);
  QFile configFile("config.ini");
  if (!configFile.exists()) {
    // 创建配置文件
    QSettings settings("config.ini", QSettings::IniFormat);
    for (int i = 0; i < ConfigKey::COUNT; i++) {
      settings.setValue(configKeyToString(static_cast<ConfigKey>(i)),
                        defaultValues[i].second);
    }
  }

  // 加载配置文件
  m_settings = new QSettings("config.ini", QSettings::IniFormat);
  m_settings->setIniCodec(QTextCodec::codecForName("UTF-8"));
}

ConfigManager::~ConfigManager() { delete m_settings; }

ConfigManager &ConfigManager::getInstance() {
  static ConfigManager instance;
  return instance;
}

void ConfigManager::setValue(ConfigKey key, const QVariant &value) {
  QMutexLocker locker(&m_mutex);
  m_settings->setValue(configKeyToString(key), value);
  m_settings->sync();
}

QVariant ConfigManager::getValue(ConfigKey key) {
  // QMutexLocker locker(&m_mutex);
  // QVariant value = m_settings->value(configKeyToString(key),
  //                                    QVariant(defaultValues[key].second));
  // m_settings->sync();
  // return value;

  QMutexLocker locker(&m_mutex);
  QString strKey = configKeyToString(key);
  QVariant value =
      m_settings->value(strKey);
  if (!value.isValid()) {
    // 如果获取不到值，则设定默认值并保存到配置文件
    value = defaultValues[key].second;
    m_settings->setValue(strKey, value);
    m_settings->sync();
  }
  return value;
}
  const char *ConfigManager::configKeyToString(ConfigKey key) {
    switch (key) {
    case WindowSize:
      return "windowSize";
    case LastOpenedFile:
      return "lastOpenedFile";
    case ScreenLockTimeout:
      return "screenLockTimeout";
    // 添加其他预定义的配置项
    case UdpSendCycleTimeout:
      return "udpSendCycleTimeout";
    case ProxyEnable:
      return "proxyEnable";
    case ProxyAddr:
      return "proxyAddr";
    case ProxyPort:
      return "proxyPort";
    case LockScreenImage:
      return "lockScreenImage";
    case AudioInputDevice:
      return "audioInputDevice";
    case AssistantEnable:
      return "assistantEnable";
    case BaiduApiEnable:
      return "baiduApiEnable";
    case BaiduApiKey:
      return "baiduApiKey";
    case BaiduApiSecret:
      return "baiduApiSecret";
    case ChatGPTEnable:
      return "chatGPTEnable";
    case OpenAiApiKey:
      return "openAiApiKey";
    case ChatGPTCommand:
      return "chatGPTCommand";
    default:
      return "";
    }
  }

  void ConfigManager::restoreDefaults() {
    // 获取互斥锁
    QMutexLocker locker(&m_mutex);

    // 恢复所有配置项的默认值
    for (int i = 0; i < static_cast<int>(ConfigKey::COUNT); i++) {
      m_settings->setValue(configKeyToString(static_cast<ConfigKey>(i)),
                           defaultValues[i].second);
    }
    m_settings->sync();
  }