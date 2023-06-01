#include "devicemgnt.h"
#include "../global/mglobal.h"
#include "qhostaddress.h"
#include "qpair.h"
#include "src/modules/deviceMgnt/device.h"
#include "src/modules/deviceMgnt/devicectrl.h"
#include "src/modules/deviceMgnt/devicemgnt.h"
#include "src/modules/deviceMgnt/tcphandle.h"
#include "src/modules/deviceMgnt/udpbroadcast.h"
#include "src/modules/global/protocolhandler.h"

bool checkDeviceInfo(Device &device) {

  if (device.getDeviceIdName().isEmpty() || device.getDeviceAddress().isNull())
    return false;
  else
    return true;
}

bool DeviceMgnt::checkDeviceExists(Device &device) {
  QMutexLocker locker(&mutexCtrl);

  Device *dev;

  for (int i = 0; i < devicesList->size(); ++i) {
    dev = devicesList->at(i);
    if (dev->getDeviceIdName() == device.getDeviceIdName()) {
      return true;
    }
  }
  return false;
}
void DeviceMgnt::addDevice(Device device) {

  if (checkDeviceInfo(device)) {
    if (checkDeviceExists(device)) {
      outDebug << "device already exists";
      Device *orgDev = getDeviceByID(device.getDeviceIdName());
      orgDev->setDeviceRvVector(*device.getDeviceRvVector());

      if (!device.getDeviceAddress().isEqual(orgDev->getDeviceAddress())) {

        orgDev->setDeviceAddress(device.getDeviceAddress());
        outInfo << orgDev->getDeviceIdName() << "IP changed from"
                << orgDev->getDeviceAddress() << "to"
                << device.getDeviceAddress();
        if (device.getDeviceRvVector()->size() != 0) {
          if (!rvDeviceList.contains(orgDev))
            rvDeviceList.append(orgDev);
        } else {
          rvDeviceList.removeOne(orgDev);
        }
      }
    } else {
      Device *newDevice =
          new Device(device.getDeviceIdName(), device.getDeviceAddress());
      newDevice->setDeviceRvVector(*device.getDeviceRvVector());
      {
        QMutexLocker locker(&mutexCtrl);
        devicesList->append(newDevice);
      }
      if (device.getDeviceRvVector()->size() != 0) {
        rvDeviceList.append(newDevice);
      }
      outInfo << "Added device " << device.getDeviceIdName(),
          device.getDeviceAddress();
      getDeviceFuncByName(device.getDeviceIdName());
    }

  } else
    outWarn << "DeviceInfo check failed:" << device.getDeviceIdName()
            << "Wont add ot the devicelist";
}

Device *DeviceMgnt::getDeviceByID(const QString &deviceId) {
  QMutexLocker locker(&mutexCtrl);

  Device *dev;

  for (int i = 0; i < devicesList->size(); ++i) {
    dev = devicesList->at(i);
    if (!dev->getDeviceIdName().compare(deviceId))
      return dev;
  }
  outInfo << "cant find device: " << deviceId;
  return NULL;
}

Device *DeviceMgnt::getDeviceByListIndex(int index) {
  QMutexLocker locker(&mutexCtrl);
  Device *dev =nullptr;
  if(index >= devicesList->size()){
      outWarn<<"out of index";
      return dev;
  }
  dev = devicesList->at(index);
  return dev;
}

void DeviceMgnt::setDevice(const Device &ddevice) {

  QString idname = ddevice.getDeviceIdName();
  for (int i = 0; i < devicesList->size(); ++i) {
    Device *dev = devicesList->at(i);

    if (!dev->getDeviceIdName().compare(idname)) {
      QMutexLocker locker(&mutexCtrl);

      dev->deviceCopyFrom(ddevice);
      return;
    }
  }
  outWarn << "setDevice failed: Cant found the deviceIdname";
}

void DeviceMgnt::printDeviceList() {
  Device *dev;
  for (int i = 0; i < devicesList->size(); ++i) {
    dev = devicesList->at(i);
    outDebug << "DEVICE:" << dev->getDeviceIdName() << dev->getDeviceAddress();
  }
}

// send tcp to get device info and write to list
void DeviceMgnt::getDeviceFuncByName(const QString &deviceId) {

  Device *dev = getDeviceByID(deviceId);
  if (dev == NULL) {
    outWarn << "getDeviceFuncByName failed:" + deviceId;
    return;
  }
  // outDebug << "Cant found the device:" << deviceId;
  QSharedPointer<QVector<QSharedPointer<DeviceCtrl>>> funcCtrlVector =
      dev->getDevicesCtrlVector();
  if (funcCtrlVector->size() != 0) {
    outWarn << "deviceFuncList is not empty!";
  }
  funcCtrlVector->clear();

  QByteArray data(R"(!FN#FNAME*(deviceNAME)?)");
  QByteArray recvdata;

  // QMutex *lock = new QMutex();
  if (sendAndGetTcpHandle(dev->getDeviceAddress(), data, recvdata)) {
    ProtocolHandler ph(recvdata);
    if (ph.isValid() && ph.getType() != e_Ptype::FNA) {

      QVector<QPair<e_Pkey, QString>> keyValues = ph.getKeyValues();
      for (int i = 0; i < keyValues.size(); ++i) {
        QPair<e_Pkey, QString> keyValue = keyValues.at(i);
        QStringList value = keyValue.second.split("/");
        outDebug << value;
        int valueType = value[1].toInt();
        QStringList nameAndDesc = value[0].split("<");
        outDebug << nameAndDesc;
        QSharedPointer<DeviceCtrl> funcCtrl;
        //        bool vaild = true;
        switch (valueType) {
        case 0:
          funcCtrl = QSharedPointer<DeviceCtrl>(
              new DeviceCtrl(keyValue.first, nameAndDesc[0], nameAndDesc[1],
                             valueType, value[2], true));
          break;
        case 1:
          funcCtrl = QSharedPointer<DeviceCtrl>(
              new DeviceCtrl(keyValue.first, nameAndDesc[0], nameAndDesc[1],
                             valueType, value[2], true));
          break;
        case 2:
          funcCtrl = QSharedPointer<DeviceCtrl>(
              new DeviceCtrl(keyValue.first, nameAndDesc[0], nameAndDesc[1],
                             valueType, value[2], true));
          break;
        default:
          outWarn << "unknown type";
          //          vaild = false;
        }
        funcCtrlVector->append(funcCtrl);
        outDebug << "already add func" << funcCtrl->getCtrlModName()
                 << funcCtrl->getDesc();
      }
      outDebug << "funcList size" << funcCtrlVector->size();
      dev->funcValid = true;
    }
  }

  // outDebug << "going to set tcphandle";
  // TcpHandle *th =
  //     new TcpHandle(dev->getDeviceAddress(), ESP8266_TCP_PORT, data);
  // th->connectAndSend();
  // bool success = true;
  // bool loop = true;

  // while (th->getStatus() != 2 && loop == true) {
  //   switch (th->getStatus()) {
  //   case 4:
  //     success = false;
  //     loop = false;
  //     break;
  //   case -1:
  //     success = false;
  //     loop = false;
  //     break;
  //   }
  //   Delay_MSec(100);
  // }
  // if (success) {
  //   QByteArray data = th->getRecvData();
  //   outDebug << "FIANL get data:" << data;

  //  else {
  //   outWarn << "getDeviceFuncByName failed:" << deviceId << "data is
  //   invalid";
  // }

  // delete th;
  // th->start();
  // while (tcpHandle.getStatus() != 2) {
  //   if (tcpHandle.getStatus() == -1) {
  //     outWarn << "Cant send data to device:" << dev->getDeviceIdName();
  //     outWarn << "setDevice func failed!";
  //     return;
  //   }
  // }
  // QByteArray recvData = tcpHandle.getRecvData();
  // outDebug <<"recvData:" << recvData;

  // delete lock;
  outDebug << "end";
}

// give a funclist it will set to device now funclist and send to device
void DeviceMgnt::setToDeviceFuncByName(
    const QString &deviceId,
    const QVector<QPair<QString, QString>> &devCtrlVector) {
  Device *dev = getDeviceByID(deviceId);
  if (dev == NULL) {
    outWarn << "getDeviceFuncByName failed:" + deviceId;
    return;
  }

  QSharedPointer<QVector<QSharedPointer<DeviceCtrl>>> funcCtrlVector =
      dev->getDevicesCtrlVector();

  // for (int i = 0; i < funcCtrlVector->size(); i++) {
  //   QSharedPointer<DeviceCtrl>  devCtrl = funcCtrlVector->at(i);
  for (int i = 0; i < devCtrlVector.size(); i++) {
    QPair<QString, QString> nowSet = devCtrlVector[i];
    for (int j = 0; j < funcCtrlVector->size(); j++) {
      if (funcCtrlVector->at(j)->getCtrlModName() == nowSet.first) {
        funcCtrlVector->at(j)->setValue(nowSet.second);
        break;
      }
    }
  }

  // QByteArray data;
  // data += "!SET";
  // for (int i = 0; i < funcCtrlVector->size(); i++) {
  //   data += '#';
  //   data += g_keysList.at((int)funcCtrlVector->at(i)->getKeyword()).toUtf8();
  //   data += '*';
  //   data += funcCtrlVector->at(i)->getCtrlModName().toUtf8();
  //   data += '/';
  //   data += QString::number(funcCtrlVector->at(i)->getType()).toUtf8();
  //   data += '/';
  //   data += funcCtrlVector->at(i)->getValue().toUtf8();
  // }
  // data += '?';

  // QByteArray recvData;
  // sendAndGetTcpHandle(dev->getDeviceAddress(), data, recvData);

  // if (recvData.contains("OK")) {
  //   outDebug << "SetOK";
  // };
  updateFuncToDevice(dev);

  return;
}

// directly send funcinfo from now device's funclist
void DeviceMgnt::updateFuncToDevice(Device *device) {
  outDebug << "going to update device:" << device->getDeviceIdName();

  Device *dev = device;
  QSharedPointer<QVector<QSharedPointer<DeviceCtrl>>> funcCtrlVector =
      dev->getDevicesCtrlVector();

  QByteArray data;
  data += "!SET";
  for (int i = 0; i < funcCtrlVector->size(); i++) {
    data += '#';
    data += g_keysList.at((int)funcCtrlVector->at(i)->getKeyword()).toUtf8();
    data += '*';
    data += funcCtrlVector->at(i)->getCtrlModName().toUtf8();
    data += '/';
    data += QString::number(funcCtrlVector->at(i)->getType()).toUtf8();
    data += '/';
    data += funcCtrlVector->at(i)->getValue().toUtf8();
  }
  data += '?';

  QByteArray recvData;
  sendAndGetTcpHandle(dev->getDeviceAddress(), data, recvData);

  if (recvData.contains("OK")) {
    outDebug << "SetOK";
  };
}

bool DeviceMgnt::sendAndGetTcpHandle(const QHostAddress &host,
                                     QByteArray &senddata,
                                     QByteArray &recvdata) {
  // QByteArray data(R"(!FN#FNAME*(deviceNAME)?)");
  // QMutex *lock = new QMutex();
  outDebug << "going to set tcphandle：" << host << senddata;
  TcpHandle *th = new TcpHandle(host, ESP8266_TCP_PORT, senddata);
  th->connectAndSend();
  bool success = true;
  bool loop = true;

  while (th->getStatus() != 2 && loop == true) {
    switch (th->getStatus()) {
    case 4:
      success = false;
      loop = false;
      break;
    case -1:
      success = false;
      loop = false;
      break;
    }
    Delay_MSec(100);
  }
  if (success) {
    recvdata = th->getRecvData();
    outDebug << "FIANL get data:" << recvdata;
    delete th;
    return true;
  } else {
    outWarn << "failed";
    delete th;

    return false;
  }
}
