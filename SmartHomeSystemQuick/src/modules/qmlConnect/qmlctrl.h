#ifndef QMLCTRL_H
#define QMLCTRL_H

#include "../deviceMgnt/deviceapi.h"
#include "../deviceMgnt/devicemgnt.h"
#include "../deviceMgnt/udphandle.h"
#include "../global/configmanager.h"
#include "../global/init.h"
#include "../global/mglobal.h"
#include "../weather/weatherinfo.h"

#include "../global/networkservice.h"
#include "../sqlite/sqlitemgnt.h"
#include "../usrMgnt/user.h"
#include "../usrMgnt/userlogin.h"
#include "../usrMgnt/usermgnt.h"
#include "../wifiMgnt/wifimgnt.h"
#include "qnumeric.h"
#include "qobject.h"
#include "qobjectdefs.h"
#include "src/modules/apiService/baiduspeech.h"
#include "src/modules/apiService/baiduspeechrecognizer.h"
#include "src/modules/apiService/chatgptapi.h"
#include "src/modules/audio/audiorecorder.h"

#include "src/modules/deviceMgnt/deviceapi.h"
#include "src/modules/global/configmanager.h"
#include "src/modules/global/init.h"
#include "src/modules/global/mglobal.h"
#include <QDir>
#include <QList>
#include <QObject>
#include <QTimer>

QStringList deleteStringListItems(const QStringList &a, const QStringList &b);

class QmlCtrl : public QObject {
  Q_OBJECT
public:
  QmlCtrl();
  ~QmlCtrl();
  void QmlCtrlInit();
  void QmlCtrlSecondInit();
  const QString programWorkingDirectory = qApp->applicationDirPath();

  QString test_name = "HK560";

  QStringList imageList;

  QString m_imageName = "null";

  int test_value = 560;

  bool m_wifiStatus = false;
  bool m_proxyVaild = false;

  int m_lockScreenTimeout = 10;
  int m_udpSendCycleTime = 10;

  bool m_loadingRequestStatue = false;

  int m_sttFlag = -1;

  QString m_audioInputDeviceName; // not as Q_PROPERTY

  QString m_proxyServerAddr = ConfigManager::getInstance()
                                  .getValue(ConfigManager::ProxyAddr)
                                  .toString();
  QString m_proxyServerPort = ConfigManager::getInstance()
                                  .getValue(ConfigManager::ProxyPort)
                                  .toString();
  bool m_enableProxy = ConfigManager::getInstance()
                           .getValue(ConfigManager::ProxyEnable)
                           .toBool();

  bool m_assistantEnable;

  bool m_baiduApiEnable;

  QString m_baiduApiKey = "";

  QString m_baiduApiSecret = "";

  bool m_chatGPTEnable = "";

  QString m_openAiApiKey = "";

  QString m_chatgptCommandSetting = "";

  // QString m_chatGPTCommand = "";

  Q_PROPERTY(bool wifiStatus MEMBER m_wifiStatus NOTIFY wifiStatusChanged)

  Q_PROPERTY(bool proxyVaild MEMBER m_proxyVaild NOTIFY proxyVaildChanged)

  Q_PROPERTY(int lockScreenTimeout MEMBER m_lockScreenTimeout NOTIFY
                 lockScreenTimeoutChanged)

  Q_PROPERTY(int udpSendCycleTime MEMBER m_udpSendCycleTime NOTIFY
                 udpSendCycleTimeChanged)

  Q_PROPERTY(QString proxyServerAddr MEMBER m_proxyServerAddr NOTIFY
                 proxyServerAddrChanged)

  Q_PROPERTY(QString proxyServerPort MEMBER m_proxyServerPort NOTIFY
                 proxyServerPortChanged)

  Q_PROPERTY(bool enableProxy MEMBER m_enableProxy NOTIFY enableProxyChanged)

  Q_PROPERTY(QString imageName MEMBER m_imageName NOTIFY imageNameChanged)

  Q_PROPERTY(bool loadingRequestStatue MEMBER m_loadingRequestStatue NOTIFY
                 loadingRequestStatueChanged)

  Q_PROPERTY(int sttFlag MEMBER m_sttFlag NOTIFY sttFlagChanged)

  Q_PROPERTY(bool assistantEnable MEMBER m_assistantEnable NOTIFY
                 assistantEnableChanged)

  Q_PROPERTY(
      bool baiduApiEnable MEMBER m_baiduApiEnable NOTIFY baiduApiEnableChanged)

  Q_PROPERTY(QString baiduApiKey MEMBER m_baiduApiKey NOTIFY baiduApiKeyChanged)

  Q_PROPERTY(QString baiduApiSecret MEMBER m_baiduApiSecret NOTIFY
                 baiduApiSecretChanged)

  Q_PROPERTY(
      bool chatGPTEnable MEMBER m_chatGPTEnable NOTIFY chatGPTEnableChanged)

  Q_PROPERTY(
      QString openAiApiKey MEMBER m_openAiApiKey NOTIFY openAiApiKeyChanged)

  Q_PROPERTY(QString chatgptCommandSetting MEMBER m_chatgptCommandSetting NOTIFY
                 chatgptCommandSettingChanged)

  /****************************************************************/

  Q_INVOKABLE bool runInLinux() {
#ifdef Q_OS_LINUX
    return true;
#else
    return false;
#endif
  }

  Q_INVOKABLE void setTestValue(int value) { pri_test_name = value; }
  Q_INVOKABLE int getTestValue() { return test_value; }

  Q_INVOKABLE bool loginUser(QString user, QString password);
  Q_INVOKABLE QString getLoginUserName() {
    return nowLoginUsr.usr->getUsrName();
  }
  Q_INVOKABLE int getLoginUserRole() {
    return int(nowLoginUsr.usr->getUsrRole());
  }

  Q_INVOKABLE int getWifiListSize() { return wifiMgnt->getWifiListSize(); };
  Q_INVOKABLE QString getWifiName(int index) {
    return wifiMgnt->getWifiName(index);
  };
  Q_INVOKABLE QString getWifiLevel(int index) {
    return wifiMgnt->getWifiLevel(index);
  };
  Q_INVOKABLE bool connectWifi(QString ssid, QString pwd) {
    return wifiMgnt->connectWIFI(ssid, pwd);
  };

  Q_INVOKABLE void sendUdpDcNow() {
    udpHandle->sendUdpBroadcastNow();
    Delay_MSec(1000);
  }

  //******************************************************
  // device ctrl

  Q_INVOKABLE int getDeviceListSize() {
    outDebug << "getDeviceListSize:" << deviceMgnt->getDeviceListSize();
    return deviceMgnt->getDeviceListSize();
  }
  Q_INVOKABLE QString getDeviceNameFromIndex(int i) {
    return deviceMgnt->getDeviceNameFromListIndex(i);
  }
  Q_INVOKABLE QString getDeviceIDFromIndex(int i) {
    return deviceMgnt->getDeviceIDFromListIndex(i);
  }
  Q_INVOKABLE int getDeviceFuncSize(int deviceIndex) {
    return deviceMgnt->getDeviceByListIndex(deviceIndex)
        ->getDevicesCtrlVector()
        ->size();
  }

  Q_INVOKABLE QString getDeviceFuncNameByIndex(int deviceIndex, int funcIndex) {
    return deviceMgnt->getDeviceByListIndex(deviceIndex)
        ->getDevicesCtrlVector()
        ->at(funcIndex)
        ->getCtrlModName();
  }

  Q_INVOKABLE QString getDeviceFuncDescByIndex(int deviceIndex, int funcIndex) {
    return deviceMgnt->getDeviceByListIndex(deviceIndex)
        ->getDevicesCtrlVector()
        ->at(funcIndex)
        ->getDesc();
  }

  Q_INVOKABLE int getDeviceFuncTypeByIndex(int deviceIndex, int funcIndex) {
    return deviceMgnt->getDeviceByListIndex(deviceIndex)
        ->getDevicesCtrlVector()
        ->at(funcIndex)
        ->getType();
  }

  Q_INVOKABLE int getDeviceFuncKeyWordByIndex(int deviceIndex, int funcIndex) {
    return (int)deviceMgnt->getDeviceByListIndex(deviceIndex)
        ->getDevicesCtrlVector()
        ->at(funcIndex)
        ->getKeyword();
  }
  Q_INVOKABLE QString getDeviceFuncValueByIndex(int deviceIndex,
                                                int funcIndex) {
    return deviceMgnt->getDeviceByListIndex(deviceIndex)
        ->getDevicesCtrlVector()
        ->at(funcIndex)
        ->getValue();
  }

  Q_INVOKABLE bool getDeviceFuncEnabledForAiByIndex(int deviceIndex,
                                                    int funcIndex) {
    return deviceMgnt->getDeviceByListIndex(deviceIndex)
        ->getDevicesCtrlVector()
        ->at(funcIndex)
        ->getEnabledForAI();
  }

  Q_INVOKABLE void setDeviceFuncEnabledForAiByIndex(int deviceIndex,
                                                    int funcIndex,
                                                    const bool &enabled) {
    outDebug << "setEnabledforAI :" << enabled;
    if(deviceMgnt->getDeviceByListIndex(deviceIndex)
            == nullptr){
        sendMessage("状态信息有误，请刷新");
        return;
    }
    if(funcIndex >= deviceMgnt->getDeviceByListIndex(deviceIndex)
            ->getDevicesCtrlVector()->size()){
        sendMessage("状态信息有误，请刷新");
        return;
    }
    return deviceMgnt->getDeviceByListIndex(deviceIndex)
        ->getDevicesCtrlVector()
        ->at(funcIndex)
        ->setEnabledForAI(enabled);
  }

  Q_INVOKABLE void setDeviceFuncValueByIndex(int deviceIndex, int funcIndex,
                                             QString funcName, QString value);

  Q_INVOKABLE void setDeviceName(int deviceIndex, QString name) {
    deviceMgnt->getDeviceByListIndex(deviceIndex)->setDeviceName(name);
  }

  Q_INVOKABLE void saveDeviceSetting(int deviceIndex) {
    sqlitemgnt->DeviceInfoInsertRecord(
        deviceMgnt->getDeviceByListIndex(deviceIndex));
  };

  Q_INVOKABLE void readDeviceSetting(int deviceIndex) {
    Device *dev = deviceMgnt->getDeviceByListIndex(deviceIndex);

    if (sqlitemgnt->DeviceGetRecord(dev)) {
      dev->readGenerateSettingStr();
      deviceMgnt->updateFuncToDevice(dev);
    };
  }

  Q_INVOKABLE void setDeviceEnable(int deviceIndex, bool enable) {
    Device *dev = deviceMgnt->getDeviceByListIndex(deviceIndex);
    dev->setDeviceEnabled(enable);
    sqlitemgnt->DeviceInfoInsertRecord(dev);
  }

  Q_INVOKABLE int getDeviceEnable(int deviceIndex) {
    Device *dev = deviceMgnt->getDeviceByListIndex(deviceIndex);
    return (int)dev->getDeviceEnabled();
  }

  Q_INVOKABLE void getDeviceRecordFromDB(int deviceIndex) {
    Device *dev = deviceMgnt->getDeviceByListIndex(deviceIndex);
    sqlitemgnt->DeviceGetRecord(dev);
  }

  Q_INVOKABLE void getWeatherReq(QString cityCode) {
    return weatherInfo->getWeatherInfo(cityCode);
  }

  Q_INVOKABLE QString getWeatherNowInfo(int type) {
    return weatherInfo->getNowInfoByIndex(type);
  }

  Q_INVOKABLE QString getWeatherInfo(int type, int index) {
    return weatherInfo->getInfobByIndex(type, index);
  }

  Q_INVOKABLE int searchCityCode(QString cityName) {
    return weatherInfo->searchCityCode(cityName).size();
  }

  Q_INVOKABLE QString getCityNameByIndex(int index) {
    return weatherInfo->cityVector.at(index).first;
  }

  Q_INVOKABLE QString getCityCodeByIndex(int index) {
    return weatherInfo->cityVector.at(index).second;
  }

  Q_INVOKABLE void setCityCodeToDB(QString cityCode) {
    outDebug << "goingt to set city code to DB";

    sqlitemgnt->settingInsertWeatherCode(
        QString::number(nowLoginUsr.usr->getUsrId()), cityCode);
  }

  // in setting

  Q_INVOKABLE void updateNowUserName(QString userName) {
    sqlitemgnt->updateUserName(QString::number(nowLoginUsr.usr->getUsrId()),
                               userName);
    nowLoginUsr.usr->setUsrName(userName);
  }

  Q_INVOKABLE void updateNowUserPwd(QString pwd) {
    sqlitemgnt->updateUserPwd(QString::number(nowLoginUsr.usr->getUsrId()),
                              pwd);
    nowLoginUsr.usr->setUsrPwd(pwd);
  }

  Q_INVOKABLE QString getNowUserName() { return nowLoginUsr.usr->getUsrName(); }

  Q_INVOKABLE QString getNowUserPwd() { return nowLoginUsr.usr->getUsrPwd(); }

  Q_INVOKABLE QVariant getSettingScnTimeOutValue() {
    return ConfigManager::getInstance().getValue(
        ConfigManager::ScreenLockTimeout);
  }

  Q_INVOKABLE void updateProxySetting() { updateEnableProxy(true); }

  Q_INVOKABLE QStringList getAudioDeviceList() {
    // outInfo<<"going to send";
    return audioRecorder->getAvailableDevices();
  }

  Q_INVOKABLE QString getAudioDeviceName() {
    return audioRecorder->getAudioDevice();
  }

  Q_INVOKABLE void setAudioDevice(int index) {
    audioRecorder->setAudioDevice(index);
    ConfigManager::getInstance().setValue(ConfigManager::AudioInputDevice,
                                          audioRecorder->getAudioDevice());
    return;
  }

  Q_INVOKABLE void setAudioDeviceByName(const QString &name) {
    // ConfigManager::getInstance().setValue(ConfigManager::AudioInputDevice,
    //                                       name);
    return audioRecorder->setAudioDeviceByName(name);
  }

  Q_INVOKABLE void startRecordAudio() {
    return audioRecorder->startRecording();
  }

  Q_INVOKABLE void stopRecordAudio() {
    audioRecorder->stopRecording();
    recognizer->recognize(QCoreApplication::applicationDirPath() +
                          "/tmp/sttTmp.wav");
    return;
  }

  Q_INVOKABLE QStringList getImagesList() { return this->imageList; }

  Q_INVOKABLE void setImage(int index) {
    if (index >= this->imageList.size() || index < 0) {
      this->m_imageName = this->imageList[0];
    } else {
      this->m_imageName = this->imageList[index];
    }
  }

  Q_INVOKABLE int getImageIndexfromName() {
    return this->imageList.indexOf(m_imageName);
  }

  Q_INVOKABLE void setImageNameFromIndex(int index) {
    if (index >= this->imageList.size() || index < 0)
      m_imageName = this->imageList[0];
    m_imageName = this->imageList[index];
    ConfigManager::getInstance().setValue(ConfigManager::LockScreenImage,
                                          m_imageName);
    outInfo << "updated lockscreen image " << m_imageName;
    emit imageNameChanged(m_imageName);
  }

  Q_INVOKABLE int getDeviceRvListSize() {
    return deviceMgnt->getRvDeviceList()->size();
  }

  Q_INVOKABLE int getDeviceRvSize(int index) {
    return deviceMgnt->getRvDeviceList()
        ->at(index)
        ->getDeviceRvVector()
        ->size();
  }

  Q_INVOKABLE QString getDeviceRvName(int index, int index2) {
    return deviceMgnt->getRvDeviceList()
        ->at(index)
        ->getDeviceRvVector()
        ->at(index2)
        .ctrlModName;
  }

  Q_INVOKABLE QString getDeviceRvDesc(int index, int index2) {
    return deviceMgnt->getRvDeviceList()
        ->at(index)
        ->getDeviceRvVector()
        ->at(index2)
        .desc;
  }

  Q_INVOKABLE QString getDeviceRvValue(int index, int index2) {
    return deviceMgnt->getRvDeviceList()
        ->at(index)
        ->getDeviceRvVector()
        ->at(index2)
        .value;
  }

  Q_INVOKABLE QString getRvDeviceName(int index) {
    return deviceMgnt->getRvDeviceList()->at(index)->getDeviceIdName();
  }

  Q_INVOKABLE QStringList getDeviceListFromDB() {
    return sqlitemgnt->getAllDeviceIdRecord();
  }

  Q_INVOKABLE bool getNowUserRoleIsAdmin() {
    outDebug << "nowLoginUsr.usr->getUsrRole()"
             << nowLoginUsr.usr->getUsrRole();
    return nowLoginUsr.usr->getUsrRole() == ADMIN ? true : false;
  }

  Q_INVOKABLE QStringList getUserNameList() {
    // return sqlitemgnt->userGetAllUsersName();
    return userMgnt->getUserNameList();
  }

  // Q_INVOKABLE QStringList getUserSettingBannedDevice(){
  //   return userMgnt->getUserNameList();
  // }

  Q_INVOKABLE QStringList getUserBannedDeviceList(int userId) {
    outInfo << "userIndex: " << userId;

    return userMgnt->getUserByIndex(userId)->bannedDeviceList;
  }

  Q_INVOKABLE QStringList getUserUnbannedDeviceList(int userId) {
    QStringList userBannedList = getUserBannedDeviceList(userId);
    QStringList allDeviceList = sqlitemgnt->getAllDeviceIdRecord();
    // deviceMgnt->getAllDeviceNameList(allDeviceList);
    return deleteStringListItems(allDeviceList, userBannedList);
  }

  Q_INVOKABLE void addBannedDevice(int userIndex, int unbanneddeviceIndex) {
    outInfo << "userIndex: " << userIndex;
    QStringList userBannedList = getUserBannedDeviceList(userIndex);
    QStringList allDeviceList = sqlitemgnt->getAllDeviceIdRecord();
    QStringList unBannedList =
        deleteStringListItems(allDeviceList, userBannedList);
    userMgnt->getUserByIndex(userIndex)->bannedDeviceList.append(
        unBannedList[unbanneddeviceIndex]);
    outInfo << userMgnt->getUserByIndex(userIndex)->bannedDeviceList;
  }

  Q_INVOKABLE void removeBannedDevice(int userIndex, int banneddeviceIndex) {
    outInfo << "userIndex: " << userIndex;
    QStringList userBannedList = getUserBannedDeviceList(userIndex);
    // QStringList allDeviceList = sqlitemgnt->getAllDeviceIdRecord();
    // QStringList unBannedList =
    // deleteStringListItems(allDeviceList,userBannedList);
    userMgnt->getUserByIndex(userIndex)->bannedDeviceList.removeAll(
        userBannedList[banneddeviceIndex]);
    outInfo << userMgnt->getUserByIndex(userIndex)->bannedDeviceList;
  }

  Q_INVOKABLE void updateBannedDeviceToDB() {
    outInfo << "going to updateBannedDeviceToDB";
    for (int i = 0; i < userMgnt->getUserListSize(); ++i) {
      sqlitemgnt->updateUserBannedDevice(*userMgnt->getUserByIndex(i));
    }
  }

  Q_INVOKABLE bool getDeviceIsBanned(QString deviceIdName) {
    if (nowLoginUsr.usr->bannedDeviceList.contains(deviceIdName)) {
      outDebug << "isBanned";
      return true;
    } else {
      outDebug << "unbanned";
      return false;
    }
  }

  Q_INVOKABLE void sendReloginSingle() {
    emit reLoginSingle();
    return;
  }

  Q_INVOKABLE void sendExitProgramSingle() {
    emit exitProgramSingle();
    return;
  }

  Q_INVOKABLE void updateDeviceCtrlDataList() { deviceApi->updateDeviceData(); }

  Q_INVOKABLE void updateChatGptDeviceCtrlCommand() {
    chatGptApi->updateApiList(deviceApi->generateCommand());
    emit refreshChatGptHistory();
  };

  // ***************** ChatGPT API ****************
  Q_INVOKABLE bool chatGptSendMessage(const QString &message) {
    if (true) {
      m_loadingRequestStatue = true;
      emit loadingRequestStatueChanged(true);
      chatGptApi->sendMessage(message);
      return true;
    }
    return false;
  }

  Q_INVOKABLE void chatGptClearHistory() { chatGptApi->clearChatHistory(); }

  Q_INVOKABLE void chatGptSetCommand(const QString &command) {
    chatGptApi->setCommand(command);
  }
  // ************************************************
  Q_INVOKABLE void updateApiSettings() {
    ConfigManager::getInstance().setValue(ConfigManager::AssistantEnable,
                                          m_assistantEnable);
    ConfigManager::getInstance().setValue(ConfigManager::BaiduApiKey,
                                          m_baiduApiKey);
    ConfigManager::getInstance().setValue(ConfigManager::BaiduApiSecret,
                                          m_baiduApiSecret);
    ConfigManager::getInstance().setValue(ConfigManager::ChatGPTEnable,
                                          m_chatGPTEnable);
    ConfigManager::getInstance().setValue(ConfigManager::OpenAiApiKey,
                                          m_openAiApiKey);
    ConfigManager::getInstance().setValue(ConfigManager::ChatGPTCommand,
                                          m_chatgptCommandSetting);
  }

  Q_INVOKABLE bool getCtrlEnabled() { return deviceMgnt->getCtrlEnabled(); }

  Q_INVOKABLE void setCtrlNow(const bool &stauts) {
    return deviceMgnt->setCtrlNow(stauts);
  }

  Q_INVOKABLE void sendMessage(const QString &message){
    emit sendMessageSingle(message);
  };

  QStringList getImagesInFolder(const QString &folderPath);

private:
  QString pri_test_name = "HK560pri";

  SqliteMgnt *sqlitemgnt = nullptr; // implemented in QmlCtrl

  UserLogin nowLoginUsr;

  UserMgnt *userMgnt = nullptr; // implemented in QmlCtrl

  WifiMgnt *wifiMgnt = nullptr; // implemented in QmlCtrl

  DeviceMgnt *deviceMgnt = nullptr; // implemented in QmlCtrl

  DeviceApi *deviceApi = nullptr; // implemented in QmlCtrl

  UdpHandle *udpHandle; // implemented in QmlCtrl

  WeatherInfo *weatherInfo;

  NetworkService *networkService; // implemented in QmlCtrl

  BaiduSpeechRecognizer *recognizer;

  BaiduSpeech *baiduSpeech;

  AudioRecorder *audioRecorder;

  ChatGptApi *chatGptApi;

  void initConfigSettings();
  void initChatGptApi();
  void initTtsAndSstApi();
public slots:

  // handle all after user login
  void afterUserLogin() {
    sqlitemgnt->initInsertUserSetting(
        QString::number(nowLoginUsr.usr->getUsrId()));
  }

  void setWifiStatus(bool status) {
    m_wifiStatus = status;
    outDebug << "network status changed:" << status;
    emit wifiStatusChanged(status);
  };

  void checkDeviceFunc(QString deivceId) {
    outDebug << "going to check device func";
    deviceMgnt->getDeviceFuncByName(deivceId);
  };

  void weatherInfoGot() {
    outDebug << "weatherInfoGot";
    emit weatherInfoChanged();
  }

  void getWeatherInfoSlot() {
    weatherInfo->getWeatherInfo(sqlitemgnt->settingGetWeatherCode(
        QString::number(nowLoginUsr.usr->getUsrId())));
  }

  void updateScreenLockTimeout(int time) {
    ConfigManager::getInstance().setValue(ConfigManager::ScreenLockTimeout,
                                          time);
    outWarn << "ScreenLockTimeout updated to " << time << " seconds";
  }

  void updateUdpSendCycleTime(int time) {
    ConfigManager::getInstance().setValue(ConfigManager::UdpSendCycleTimeout,
                                          time);
    outInfo << "UdpSendCycleTime updated to " << time << " seconds";
    if (udpHandle)
      udpHandle->updateCycleTimeUdpBroadcast(time);
  }

  void updateEnableProxy(bool enable) {
    ConfigManager::getInstance().setValue(ConfigManager::ProxyEnable, enable);
    outInfo << "EnableProxy updated to " << m_enableProxy;
    if (m_enableProxy) {
      outInfo << "proxySever " << m_proxyServerPort << ":" << m_proxyServerPort;
      m_proxyVaild = networkService->setProxy(m_proxyServerAddr,
                                              m_proxyServerPort.toUInt());
      emit proxyVaildChanged(m_proxyVaild);
      if (m_proxyVaild) {
        ConfigManager::getInstance().setValue(ConfigManager::ProxyAddr,
                                              m_proxyServerAddr);
        ConfigManager::getInstance().setValue(ConfigManager::ProxyPort,
                                              m_proxyServerPort);
      }
    } else {
      outInfo << "close proxy";
      networkService->clearProxy();
    }
    // todo network
  }

  void getAudioRecognizerResult(const QString &result) {
    outInfo << "识别结果" << result;
    emit audioRecognizerResultGet(result);
  }

  void getChatGptNewMessage(const QString &message) {
    outInfo << "Get chatGPT Message:" << message;
    QString newMessage;
    bool findJson = false;
    DeviceControlData tmp;
    tmp = DeviceApi::parseJsonString(message, newMessage, findJson);
    if (findJson) {
      deviceApi->findDeviceControl(tmp);
    }
    m_loadingRequestStatue = false;
    emit loadingRequestStatueChanged(false);
    baiduSpeech->textToSpeech(newMessage);
    emit chatGptNewResponse(newMessage);
  }

  void getChatGptError(const QString &error) {
    outWarn << "Error occurred:" << error;
    m_loadingRequestStatue = false;
    emit loadingRequestStatueChanged(false);
    emit chatGptError(error);
  }

  void handleDeviceCtrlApi(const DeviceControlInfo &info) {
    outInfo << "now handle device control api";
    if (deviceMgnt->getCtrlEnabled()) {
      setCtrlNow(true);
      setDeviceFuncValueByIndex(info.deviceIndex, info.funcIndex, info.funcName,
                                info.value);
      setCtrlNow(false);
    }
  }

  void doSecondInit() { QmlCtrlSecondInit(); }

  void sendFoundDeviceSingals(QString device) {
    outInfo << "told qml found device";
    emit foundDevice();
  }



signals:
  void wifiStatusChanged(const bool &newStatus);
  void proxyVaildChanged(const bool &newStatus);

  void lockScreenTimeoutChanged(int newTimeout);
  void udpSendCycleTimeChanged(int newCycleTime);
  void proxyServerAddrChanged(QString addr);
  void proxyServerPortChanged(QString port);
  void enableProxyChanged(bool enabled);
  void imageNameChanged(QString imageName);
  void weatherInfoChanged();
  void loadingRequestStatueChanged(const bool &status);
  void sttFlagChanged(const int &flag);
  void assistantEnableChanged(const bool &enable);
  void baiduApiEnableChanged(const bool &enable);
  void baiduApiKeyChanged(const QString &key);
  void baiduApiSecretChanged(const QString &key);
  void chatGPTEnableChanged(const bool &enable);
  void openAiApiKeyChanged(const QString &key);
  void chatgptCommandSettingChanged(const QString &settingCommand);

  void audioRecognizerResultGet(const QString &result);
  void userLoginSuccess();
  void reLoginSingle();
  void exitProgramSingle();
  void chatGptNewResponse(const QString &response);
  void chatGptError(const QString &errorMessage);
  void refreshChatGptHistory();
  void secondInitFinished();
  void foundDevice();

  void sendMessageSingle(const QString &errorMessage);
};
#endif // QMLCTRL_H
