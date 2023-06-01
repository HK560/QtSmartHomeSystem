
#include "src/modules/deviceMgnt/deviceapi.h"
#include "src/modules/global/init.h"

DeviceApi::DeviceApi(QObject *parent, DeviceMgnt *ddeviceMgnt)
    : QObject{parent}, deviceMgnt(ddeviceMgnt) {
  deviceCtrlDataList = new QVector<DeviceData>;
}

void DeviceApi::updateDeviceData() {
  outInfo << "started updateDeviceCtrlData";
  Device *dev = nullptr;
  if (deviceCtrlDataList) {
    deviceCtrlDataList->clear();
  }
  int deviceSize = deviceMgnt->getDeviceListSize();
  for (int deviceIndex = 0; deviceIndex < deviceSize; ++deviceIndex) {

    dev = deviceMgnt->getDeviceByListIndex(deviceIndex);

    DeviceData newData;
    newData.deviceIndex = deviceIndex;
    newData.deviceName = dev->getDeviceName();

    bool flag = false;

    int funcSize = dev->getDevicesCtrlVector()->size();

    for (int funcIndex = 0; funcIndex < funcSize; ++funcIndex) {
      if (dev->getDevicesCtrlVector()->at(funcIndex)->getEnabledForAI() ==
          true) {

        DeviceFuncData newFuncData;

        newFuncData.funcIndex = funcIndex;

        newFuncData.funcName =
            dev->getDevicesCtrlVector()->at(funcIndex)->getCtrlModName();

        newFuncData.type = DeviceControlType(
            dev->getDevicesCtrlVector()->at(funcIndex)->getType());

        newData.deviceFuncAndIndex.append(newFuncData);

        flag = true;
      }
    }

    if (flag) {

      deviceCtrlDataList->append(newData);

      outInfo << "added devicCtrlDevice:" << newData.deviceName
              << newData.deviceFuncAndIndex.size();
    }
  }
  outInfo << "updateDeviceCtrlData ended";
  generateCommand();
}

QString DeviceApi ::generateCommand() {

  QString result;

  for (const auto &device : *deviceCtrlDataList) {
    result += "!" + device.deviceName + "";

    for (const auto &func : device.deviceFuncAndIndex) {
      result += "#" + func.funcName + "/" + type2Str(func.type);
    }
  }
  outInfo << "generateCommand" << result;
  return result;
}

DeviceControlInfo
DeviceApi ::findDeviceControl(const DeviceControlData &controlData) {
  DeviceControlInfo info;
  for (int i = 0; i < deviceCtrlDataList->size(); i++) {
    DeviceData deviceData = deviceCtrlDataList->at(i);
    if (deviceData.deviceName == controlData.deviceName) {
      for (int j = 0; j < deviceData.deviceFuncAndIndex.size(); j++) {
        DeviceFuncData funcData = deviceData.deviceFuncAndIndex.at(j);
        if (funcData.funcName == controlData.deviceFunc) {
          if (funcData.type == DT_switch || funcData.type == DT_int ||
              funcData.type == DT_string) {
            info.deviceIndex = deviceData.deviceIndex;
            info.funcIndex = funcData.funcIndex;
            info.value = controlData.value;
            info.funcName = funcData.funcName;
            printDeviceControlInfo(info);
            emit sendDeviceCtrlSingle(info);
            return info;
          }
        }
      }
    }
  }
  outWarn<<"notfound device control info";
  return info;
}
