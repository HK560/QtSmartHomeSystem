#include "device.h"

void Device::init() {

  if (devicesCtrlVector == nullptr) {
    devicesCtrlVector = QSharedPointer<QVector<QSharedPointer<DeviceCtrl>>>(
        new QVector<QSharedPointer<DeviceCtrl>>);
    if (!devicesCtrlVector) {
      outDebug << "deviceCtrlVector new failed";
    }
  }

  // get deviceinfo
}

void Device::deviceCopyFrom(const Device &device) {
  this->idname = device.idname;
  this->deviceName = device.deviceName;
  this->deviceType = device.deviceType;
  this->deviceStatus = device.deviceStatus;
  this->ipAddress = device.ipAddress;
  this->devicesCtrlVector = device.devicesCtrlVector;
  this->enabled = device.enabled;
}

QString Device::generateSettingStr() {
  QSharedPointer<QVector<QSharedPointer<DeviceCtrl>>> funcCtrlVector =
      this->getDevicesCtrlVector();

  QByteArray data;
  for (int i = 0; i < funcCtrlVector->size(); i++) {
    data += '#';
    data += g_keysList.at((int)funcCtrlVector->at(i)->getKeyword()).toUtf8();
    data += '*';
    data += funcCtrlVector->at(i)->getCtrlModName().toUtf8();
    data += '/';
    data += QString::number(funcCtrlVector->at(i)->getType()).toUtf8();
    data += '/';
    data += funcCtrlVector->at(i)->getValue().toUtf8();
    data += '/';
    data += QString::number(int(funcCtrlVector->at(i)->getEnabledForAI())).toUtf8();
  }
  outDebug << "Setting data:" <<data;   
  this->settingStr = data;
  return data;
}

void Device::readGenerateSettingStr() {
  outDebug<<settingStr;
  QString temp = settingStr;
  QRegExp regexKey(R"((.[^*]+)\*(.*))");
  QStringList keyGroup = temp.split('#');
  outDebug<<keyGroup.length();
  for (int i = 0; i < keyGroup.length(); i++) {
    if(keyGroup[i].isEmpty())
      continue;
    outDebug<<keyGroup[i];
    regexKey.indexIn(keyGroup[i]);
    QStringList keyValue = regexKey.capturedTexts();
    outDebug << "Key and value: " << keyValue;
    QStringList funcList = keyValue[2].split('/');
    setFuncValueByName(funcList[0], funcList[2],funcList[3]);
  }

  //

}

void Device::setFuncValueByName(QString &funcName, QString &funcValue,QString &enabledForAi) {
    for(int i = 0; i < devicesCtrlVector->size(); i++) {
        if (devicesCtrlVector->at(i)->getCtrlModName() == funcName) {
            devicesCtrlVector->at(i)->setValue(funcValue);
            devicesCtrlVector->at(i)->setEnabledForAI(enabledForAi.toInt());
            outDebug<< "set success";
            return;
        } 
    }
    outWarn<<"Cant find the function: "<<funcName;
    return;
}