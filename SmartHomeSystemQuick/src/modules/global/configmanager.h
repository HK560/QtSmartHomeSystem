#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <QFile>
#include <QMutex>
#include <QPair>
#include <QSettings>
#include <QVariant>

class ConfigManager

{
public:
  enum ConfigKey {
    WindowSize,
    LastOpenedFile,
    ScreenLockTimeout,
    UdpSendCycleTimeout,
    ProxyEnable,
    ProxyAddr,
    ProxyPort,
    LockScreenImage,
    AudioInputDevice,
    AssistantEnable,
    BaiduApiEnable,
    BaiduApiKey,
    BaiduApiSecret,
    ChatGPTEnable,
    OpenAiApiKey,
    ChatGPTCommand,
    COUNT
    // 添加其他预定义的配置项
  };

  static const char *configKeyToString(ConfigKey key);

  const QPair<ConfigManager::ConfigKey, const char *> defaultValues[COUNT] = {
      {WindowSize, "1024x600"},
      {LastOpenedFile, ""},
      {ScreenLockTimeout, "20"},
      {UdpSendCycleTimeout, "10"},
      {ProxyEnable, "false"},
      {ProxyAddr, "127.0.0.1"},
      {ProxyPort, "7890"},
      {LockScreenImage, ""},
      {AudioInputDevice, "default"},
      {AssistantEnable, "true"},
      {BaiduApiEnable,"true"},
      {BaiduApiKey, ""},
      {BaiduApiSecret, ""},
      {ChatGPTEnable,"true"},
      {OpenAiApiKey, ""},
      {ChatGPTCommand, ""}
      // 添加其他默认配置项
  };

  static ConfigManager &getInstance();

  void setValue(ConfigKey key, const QVariant &value);

  QVariant getValue(ConfigKey key);
  void restoreDefaults();

private:
  ConfigManager();

  ~ConfigManager();
  QMutex m_mutex;
  QSettings *m_settings;
};

#endif // CONFIG_MANAGER_H
