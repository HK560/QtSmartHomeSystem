#include "qmlctrl.h"
#include "qglobal.h"
#include "src/modules/apiService/baiduspeech.h"
#include "src/modules/apiService/baiduspeechrecognizer.h"
#include "src/modules/apiService/chatgptapi.h"
#include "src/modules/audio/audiorecorder.h"
#include "src/modules/deviceMgnt/devicemgnt.h"
#include "src/modules/global/mglobal.h"
#include "src/modules/qmlConnect/qmlctrl.h"
#include "src/modules/weather/weatherinfo.h"

QmlCtrl::QmlCtrl() {}

void QmlCtrl::QmlCtrlInit() {
  qDebug() << "QmlCtrl start init";
  sqlitemgnt = new SqliteMgnt;

  userMgnt = new UserMgnt(sqlitemgnt);

  wifiMgnt = new WifiMgnt();

  deviceMgnt = new DeviceMgnt(sqlitemgnt);

  deviceApi = new DeviceApi(this, deviceMgnt);

  udpHandle = new UdpHandle(deviceMgnt);

  // QTimer::singleShot(20000, udpHandle, SLOT(stopUdpBroadcast()));
  // test
  weatherInfo = new WeatherInfo();

  networkService = new NetworkService(this);

  audioRecorder = new AudioRecorder(this);

  recognizer = new BaiduSpeechRecognizer(this);

  baiduSpeech = new BaiduSpeech(this);

  chatGptApi = new ChatGptApi(this, networkService->getNetworkAccessManager());

  connect(&wifiMgnt->networkConfigurationManager,
          SIGNAL(onlineStateChanged(bool)), this, SLOT(setWifiStatus(bool)));

  connect(weatherInfo, &WeatherInfo::gotWeatherInfoSignal, this,
          &QmlCtrl::weatherInfoGot);
  // weatherInfo->getWeatherInfo(sqlitemgnt.c);
  connect(this, &QmlCtrl::userLoginSuccess, this, &QmlCtrl::afterUserLogin);

  connect(this, &QmlCtrl::userLoginSuccess, this, &QmlCtrl::doSecondInit);

  connect(this, &QmlCtrl::lockScreenTimeoutChanged, this,
          &QmlCtrl::updateScreenLockTimeout);
  connect(this, &QmlCtrl::udpSendCycleTimeChanged, this,
          &QmlCtrl::updateUdpSendCycleTime);

  connect(this, &QmlCtrl::enableProxyChanged, this,
          &QmlCtrl::updateEnableProxy);

  connect(recognizer, &BaiduSpeechRecognizer::recognitionFinished, this,
          &QmlCtrl::getAudioRecognizerResult);

  // connect(chatGptApi, &ChatGptApi::responseReceived,
  //         [](const QString &text) { qDebug() << "Generated text:" << text;
  //         });

  connect (udpHandle,&UdpHandle::foundDevice,this,&QmlCtrl::sendFoundDeviceSingals);
  
  connect(chatGptApi, &ChatGptApi::responseReceived, this,
          &QmlCtrl::getChatGptNewMessage);

  connect(chatGptApi, &ChatGptApi::errorOccurred, this,
          &QmlCtrl::getChatGptError);

  connect(this, &QmlCtrl::chatGPTEnableChanged, this, &QmlCtrl::initChatGptApi);

  connect(this, &QmlCtrl::baiduApiEnableChanged, this,
          &QmlCtrl::initTtsAndSstApi);

  connect(deviceApi, &DeviceApi::sendDeviceCtrlSingle, this,
          &QmlCtrl::handleDeviceCtrlApi);

  createOrClearFolder(QCoreApplication::applicationDirPath() + "/tmp");

  sqlitemgnt->initDb();

  userMgnt->init();

  wifiMgnt->getAllWifiConnectionsList();

  deviceMgnt->init();
  initConfigSettings();
}

void QmlCtrl::QmlCtrlSecondInit() {

  outInfo << "Stated second qmlCtrl init";

  getWeatherInfoSlot();

  audioRecorder->setAudioDeviceByName(m_audioInputDeviceName);

  updateEnableProxy(m_enableProxy);

  m_wifiStatus = wifiMgnt->networkConfigurationManager.isOnline();

  m_lockScreenTimeout = ConfigManager::getInstance()
                            .getValue(ConfigManager::ScreenLockTimeout)
                            .toInt();

  sqlitemgnt->createUserSettingTable();

  udpHandle->init();

  udpHandle->updateCycleTimeUdpBroadcast(m_udpSendCycleTime);

  udpHandle->startUdpBroadcast();

  // outInfo << networkService->setProxy("127.0.0.1", 7890);
  // networkService->testNetworkConnectivity();
  initChatGptApi();

  // 设置API Key和Secret Key
  initTtsAndSstApi();
  // baiduSpeech->play(QCoreApplication::applicationDirPath()+"/speech.mp3");
  // 识别音频文件
  // QString audioFilepath = "I:\\Desktop\\16k.wav";
  // recognizer->recognize(audioFilepath);

  // 连接recognitionFinished()信号

  // AudioRecorder recorder ;
  // recorder.printAvailableDevices();
  // testAudioRecorder("Mic in at rear panel (Pink) (Realtek(R)
  // Audio)","I:\\Desktop\\test.wav");
  emit secondInitFinished();
}

QmlCtrl::~QmlCtrl() {
  delete sqlitemgnt;
  delete userMgnt;
}

bool QmlCtrl::loginUser(QString userName, QString password) {
  qDebug() << "get from qml:" << userName << " " << password;
  User user(userName, password);

  if (userMgnt->userLoginCheack(user)) {
    nowLoginUsr.setUser(userMgnt->getUserById((userName)));
    nowLoginUsr.outputUsrInfo();
    emit userLoginSuccess();
    return true;
  }
  qDebug() << "usrloginFailed";
  return false;
}

void QmlCtrl::setDeviceFuncValueByIndex(int deviceIndex, int funcIndex,
                                        QString funcName, QString value) {
  Device *device = deviceMgnt->getDeviceByListIndex(deviceIndex);
  if (device == nullptr) {
      sendMessage("状态信息有误，请刷新");
    return;
  }
  if (funcName ==
      device->getDevicesCtrlVector()->at(funcIndex)->getCtrlModName()) {
    device->getDevicesCtrlVector()->at(funcIndex)->setValue(value);
    outDebug << "QmlCtrl: set device func value" << funcName << "," << value
             << ",";

    deviceMgnt->updateFuncToDevice(device);
    return;
  }
  outWarn << "funcIndex and funcName not match";
  return;
}

void QmlCtrl::initConfigSettings() {

  this->imageList =
      getImagesInFolder(programWorkingDirectory + QString("/images"));
  Q_ASSERT(this->imageList.size() != 0);

  m_lockScreenTimeout = ConfigManager::getInstance()
                            .getValue(ConfigManager::ScreenLockTimeout)
                            .toInt();
  m_udpSendCycleTime = ConfigManager::getInstance()
                           .getValue(ConfigManager::UdpSendCycleTimeout)
                           .toInt();
  m_audioInputDeviceName = ConfigManager::getInstance()
                               .getValue(ConfigManager::AudioInputDevice)
                               .toString();
  m_proxyServerAddr = ConfigManager::getInstance()
                          .getValue(ConfigManager::ProxyAddr)
                          .toString();
  m_proxyServerPort = ConfigManager::getInstance()
                          .getValue(ConfigManager::ProxyPort)
                          .toString();
  m_enableProxy = ConfigManager::getInstance()
                      .getValue(ConfigManager::ProxyEnable)
                      .toBool();
  m_imageName = ConfigManager::getInstance()
                    .getValue(ConfigManager::LockScreenImage)
                    .toString();
  if ((m_imageName.isEmpty()) ||
      (!QFile::exists(programWorkingDirectory + QString("/images/") +
                      QString(m_imageName)))) {
    outWarn << "Couldn't find the image " << m_imageName;
    m_imageName = this->imageList[0];
  }

  m_assistantEnable = ConfigManager::getInstance()
                          .getValue(ConfigManager::AssistantEnable)
                          .toBool();

  m_baiduApiEnable = ConfigManager::getInstance()
                         .getValue(ConfigManager::BaiduApiEnable)
                         .toBool();

  m_baiduApiKey = ConfigManager::getInstance()
                      .getValue(ConfigManager::BaiduApiKey)
                      .toString();

  m_baiduApiSecret = ConfigManager::getInstance()
                         .getValue(ConfigManager::BaiduApiSecret)
                         .toString();

  m_chatGPTEnable = ConfigManager::getInstance()
                        .getValue(ConfigManager::ChatGPTEnable)
                        .toBool();

  m_openAiApiKey = ConfigManager::getInstance()
                       .getValue(ConfigManager::OpenAiApiKey)
                       .toString();

  m_chatgptCommandSetting = ConfigManager::getInstance()
                                .getValue(ConfigManager::ChatGPTCommand)
                                .toString();
}

QStringList QmlCtrl::getImagesInFolder(const QString &folderPath) {
  QStringList imageFilters;
  imageFilters << "*.bmp"
               << "*.gif"
               << "*.jpg"
               << "*.jpeg"
               << "*.png"
               << "*.pbm"
               << "*.pgm"
               << "*.ppm"
               << "*.xbm"
               << "*.xpm";

  QDir directory(folderPath);
  QStringList images = directory.entryList(imageFilters, QDir::Files);
  outInfo << "got images list:" << images;
  return images;
}

QStringList deleteStringListItems(const QStringList &a, const QStringList &b) {
  QStringList result = a;

  for (const QString &str : b) {
    if (result.contains(str)) {
      result.removeAll(str);
    }
  }
  return result;
}

void QmlCtrl::initChatGptApi() {
  outInfo << "NOW initChatGptApi";
  chatGptApi->setEnable(m_chatGPTEnable);

  if (m_chatGPTEnable) {

    chatGptApi->setApiToken(m_openAiApiKey);

    chatGptApi->setCommand(m_chatgptCommandSetting);

    updateChatGptDeviceCtrlCommand();

    chatGptApi->clearChatHistory();

    chatGptApi->sendMessage("介绍一下你自己");
    outInfo << "chatGPT enabled";
    return;
  }
  outInfo << "chatGPT disabled";
}

void QmlCtrl::initTtsAndSstApi() {
  outInfo << "NOW initTtsAndSstApi";
  recognizer->setEnabled(m_baiduApiEnable);
  baiduSpeech->setEnabled(m_baiduApiEnable);
  if (m_baiduApiEnable) {
    recognizer->setAccessKeys(m_baiduApiKey, m_baiduApiSecret);

    baiduSpeech->setAccessKeys(m_baiduApiKey, m_baiduApiSecret);

    baiduSpeech->textToSpeech("欢迎使用智慧家庭系统");
    outInfo << "baiduApi enabled";
    return;
  }
  outInfo << "baiduApi disabled";
}
