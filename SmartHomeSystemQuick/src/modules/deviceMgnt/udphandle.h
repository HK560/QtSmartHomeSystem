#ifndef UDPHANDLE_H
#define UDPHANDLE_H

#include "../global/init.h"
#include "../global/protocolhandler.h"
#include "device.h"
#include "qobject.h"
#include "qobjectdefs.h"
#include "qthread.h"
#include "qudpsocket.h"
#include "src/modules/deviceMgnt/devicemgnt.h"
#include "src/modules/deviceMgnt/udpbroadcast.h"
#include "udpbroadcast.h"
#include <QByteArray>
#include <QMutex>
#include <QMutexLocker>
#include <QNetworkDatagram>
#include <QObject>
#include <QThread>
#include <QUdpSocket>

class UdpHandle : public QObject {
  Q_OBJECT

  QUdpSocket *udpSocket;
  // QThread *udpBroadcastThread;
  UdpBroadcast *udpBroadcast;

  DeviceMgnt *deviceMgnt;
  void processTheDatagram(QNetworkDatagram data);

public:
  QMutex *m_mutex;
  UdpHandle(DeviceMgnt *ddeviceMgnt) : deviceMgnt(ddeviceMgnt){};
  void init();
  // virtual void run() override;

  // void
public slots:
  void readPendingDatagrams();
  void startUdpBroadcast() {
    if (udpBroadcast)
      udpBroadcast->start();
  };
  void stopUdpBroadcast() {
    if (udpBroadcast)
      udpBroadcast->stop();
  };
  void updateCycleTimeUdpBroadcast(int newCycleTime) {
    if (udpBroadcast)
      udpBroadcast->updateCycleTime(newCycleTime);
  };
  void sendUdpBroadcastNow(){
    udpBroadcast->sendDC();
  };
  void handleCtrlNow(const bool &status){
    emit ctrlNowChanged(status);
  }
signals:
  void foundDevice(QString device);
  void ctrlNowChanged(const bool &status);
};

#endif // UDPHANDLE_H
