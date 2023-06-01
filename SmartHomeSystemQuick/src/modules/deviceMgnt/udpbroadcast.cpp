#include "udpbroadcast.h"
#include "../global/mglobal.h"
#include "qmutex.h"
#include "src/modules/deviceMgnt/devicemgnt.h"
#include "src/modules/deviceMgnt/udpbroadcast.h"

void UdpBroadcast::init() {
  timer = new QTimer(this);
  broadcastSocket = new QUdpSocket(this);
  mutex = new QMutex();
  connect(deviceMgnt, &DeviceMgnt::ctrlNowChanged, this,
          &UdpBroadcast::handleCtrlChanged);
}

void UdpBroadcast::sendDC() {
  QMutexLocker locker(mutex);
  deviceMgnt->clearDevicesList();
  QByteArray data = "!DC#IP*(SysIP)?";
  outDebug << "Going to send udp data" << data << QHostAddress::Broadcast;
  if (-1 == broadcastSocket->writeDatagram(data, data.size(),
                                           QHostAddress::Broadcast, 5600)) {
    outDebug << "Unexpected udp error" << QHostAddress::Broadcast;
  };
}

void UdpBroadcast::run() {
  outInfo << "UDP broadcast running";
  do {
    {
      QMutexLocker locker(&m_mutex);
      if (!enable)
        break;
    }
    if (!ctrlNow) {
      emit udpBroadcastReadyToSend();
      Delay_MSec(200);
      sendDC();
      Delay_MSec(cycleTime * 1000);
    } else {
      Delay_MSec(2000);
    }

  } while (true);

  emit udpBroadcastStop();
  outInfo << "udp broadcast stopped";
}
