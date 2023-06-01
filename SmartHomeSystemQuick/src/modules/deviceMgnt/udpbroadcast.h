#ifndef UDPBROADCAST_H
#define UDPBROADCAST_H

#include "../global/init.h"
#include "devicemgnt.h"
#include "qobjectdefs.h"
#include <QByteArray>
#include <QEventLoop>
#include <QHostAddress>
#include <QMutex>
#include <QMutexLocker>
#include <QNetworkDatagram>
#include <QObject>
#include <QThread>
#include <QTimer>
#include <QUdpSocket>

class UdpBroadcast : public QThread {

  Q_OBJECT
  QUdpSocket *broadcastSocket;
  QMutex *mutex;
  QMutex m_mutex;
  QMutex m_mutexCycleTime;

  bool enable = true;
  QTimer *timer;
  int cycleTime = 10;
  DeviceMgnt *deviceMgnt;
  bool ctrlNow = false;

public:
  UdpBroadcast(int cycletime, DeviceMgnt *ddeviceMgnt)
      : cycleTime(cycletime = 10), deviceMgnt(ddeviceMgnt){};

  ~UdpBroadcast() {
    stop();
    quit();
    wait();
  };
  virtual void run() override;
  void init();

public slots:
  void handleCtrlChanged(const bool &status) {outInfo<<"ctrlNow changed";ctrlNow = status;}
  void sendDC();
  void updateCycleTime(int newCycleTime) {
    QMutexLocker locker(&m_mutexCycleTime);
    cycleTime = newCycleTime;
  };
  void stop() {
    outDebug << "try to stop udp broadcast";
    QMutexLocker locker(&m_mutex);
    enable = false;
  }
signals:
  void udpBroadcastStop();
  void udpBroadcastReadyToSend();
};
void Delay_MSec(unsigned int msec);
#endif // UDPBROADCAST_H
