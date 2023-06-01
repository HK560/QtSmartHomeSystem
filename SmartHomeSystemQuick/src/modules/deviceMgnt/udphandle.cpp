#include "udphandle.h"
#include "devicemgnt.h"
#include "qhostaddress.h"
#include "qvector.h"
#include "src/modules/deviceMgnt/device.h"
#include "src/modules/deviceMgnt/udphandle.h"
#include "src/modules/global/protocolhandler.h"

void UdpHandle::init() {
  outDebug << "udp init";
  m_mutex = new QMutex;
  udpSocket = new QUdpSocket;
  if (!udpSocket->bind(56700, QUdpSocket::ShareAddress)) {
    outDebug << "udpSocket failed to bind";
  };
  connect(udpSocket, &QUdpSocket::readyRead, this,
          &UdpHandle::readPendingDatagrams);

  udpBroadcast = new UdpBroadcast(10, deviceMgnt);
  connect(udpBroadcast, &UdpBroadcast::udpBroadcastReadyToSend, this,
          [=]() { outInfo<<"UDP broadcast have Send";deviceMgnt->clearDevicesList(); });
  connect(deviceMgnt,&DeviceMgnt::ctrlNowChanged,this,&UdpHandle::handleCtrlNow);
  udpBroadcast->init();
}

void UdpHandle::readPendingDatagrams() {
  // outDebug <<"Got Udp data to handle";
  // QMutexLocker locker(m_mutex);
  while (udpSocket->hasPendingDatagrams()) {
    QNetworkDatagram datagram = udpSocket->receiveDatagram();
    processTheDatagram(datagram);
  }
}

void UdpHandle::processTheDatagram(QNetworkDatagram datagram) {
  deviceMgnt->setCtrlEnabled(false);
  QByteArray Data = datagram.data();
  outDebug << "********************HANDLE DATA****************";
  outDebug << "Handles received datagram from" << datagram.senderAddress()
           << datagram.senderPort();
  outDebug << "DATA: " << Data;

  ProtocolHandler ph(Data);
  if (ph.isValid()) {
    outDebug << int(ph.getType());
    QVector<QPair<e_Pkey, QString>> keyValues = ph.getKeyValues();
    // ph.printTest(keyValues);
    QString idname = ph.getValueByKey(e_Pkey::ID);
    QString ip = ph.getValueByKey(e_Pkey::IP);
    if (!idname.isEmpty() && !ip.isEmpty()) {
      Device newDevice(idname, QHostAddress(ip));
      QVector<DeviceFunc> *tempDevicefunc = newDevice.getDeviceRvVector();
      for (int i = 0; i < keyValues.size(); ++i) {
        for (int j = MIN_RV_KEY; j <= MAX_RV_KEY; ++j) {
          if (keyValues[i].first == (e_Pkey)j) {
            tempDevicefunc->append(
                ph.getDeviceFuncFromKeyValues(keyValues.at(i)));
            break;
          };
        }
      }
      outInfo << "DeviceRV size:" << tempDevicefunc->size();
      deviceMgnt->addDevice(newDevice);
      deviceMgnt->printDeviceList();
      // outInfo<<*deviceMgnt->getRvDeviceList();
      emit foundDevice(idname);
      // QVector<QPair<QString,QString>> test;
      // test.append(QPair<QString,QString>("Light", "1"));
      // test.append(QPair<QString,QString>("Test", "niubi"));

      deviceMgnt->printRvDeviceList();
    } else {
      outWarn << "Cant get device id and ip, skiped";
    }
  } else {
    outWarn << "not valid data";
  }
  outDebug << "********************HANDLE END*****************";
  deviceMgnt->setCtrlEnabled(true);
}
