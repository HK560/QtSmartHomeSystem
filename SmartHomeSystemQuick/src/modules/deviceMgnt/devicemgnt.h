#ifndef _DEVICEMGNT_H_
#define _DEVICEMGNT_H_

#include "../global/init.h"
#include "../sqlite/sqlitemgnt.h"

#include "../global/protocolhandler.h"
#include "device.h"
#include "devicectrl.h"
#include "qobjectdefs.h"
#include "qvector.h"
#include "src/modules/deviceMgnt/device.h"
#include "tcphandle.h"
#include <QList>
#include <QMutex>
#include <QMutexLocker>
#include <QObject>

class DeviceMgnt : public QObject {

  Q_OBJECT

  QList<Device *> *devicesList = nullptr;

  QList<Device *> rvDeviceList;

  SqliteMgnt *sqlmgnt; // implemented in qmlCtrl

  QMutex mutexCtrl;

  bool ctrlEnabled = true;

  bool ctrlNow = false;

signals:
  void ctrlNowChanged(const bool& status);


public:
  DeviceMgnt(SqliteMgnt *sqlmgnt)
      : sqlmgnt(sqlmgnt){

        };
  ~DeviceMgnt(){
      // delete udpHandle;
  };

  void setCtrlNow(const bool &status){
    ctrlNow = status;
    emit ctrlNowChanged(ctrlNow);
  }

  bool getCtrlNow(){
    return ctrlNow;
  }
  void setCtrlEnabled(const bool &status){
    ctrlEnabled = status;
  }
  bool getCtrlEnabled(){
    return ctrlEnabled;
  }
  void init() {
    devicesList = new QList<Device *>();
    sqlmgnt->createDeviceInfoTable();
  }
  void clearDevicesList() {
    QMutexLocker locker(&mutexCtrl);
    if (devicesList)
    outInfo<<"clear devices list";
      devicesList->clear();
  }
  void loadDeviceList();
  void addDevice(Device device);
  Device *getDeviceByID(const QString &deviceId);
  void setDevice(const Device &device); // dont use this, it is directly copy
  bool checkDeviceExists(Device &device);
  bool sendAndGetTcpHandle(const QHostAddress &host, QByteArray &senddata,
                           QByteArray &recvdata);
  void getDeviceFuncByName(const QString &deviceId);
  // void setToDeviceFuncByName(const QString &deviceId,const
  // QVector<QPair<QString, QString>> &devCtrlVector);

  void
  setToDeviceFuncByName(const QString &deviceId,
                        const QVector<QPair<QString, QString>> &devCtrlVector);

  void updateFuncToDevice(Device *device);

  void printDeviceList();
  // for qmlCtrl
  int getDeviceListSize() {
    QMutexLocker locker(&mutexCtrl);
    return devicesList->size();
  };
  QString getDeviceNameFromListIndex(int index) {
    QMutexLocker locker(&mutexCtrl);
    return devicesList->at(index)->getDeviceName();
  };
  QString getDeviceIDFromListIndex(int index) {
    QMutexLocker locker(&mutexCtrl);
    return devicesList->at(index)->getDeviceIdName();
  };

  QStringList *getAllDeviceNameList(QStringList &list) {
    list.clear();
    Device *dev;
    for (int i = 0; i < devicesList->size(); ++i) {
      dev = devicesList->at(i);
      list.append(dev->getDeviceIdName());
    }
    return &list;
  }
  Device *getDeviceByListIndex(int index);

  QList<Device *> *getRvDeviceList() { return &rvDeviceList; }

  void printRvDeviceList() {
    for (int i = 0; i < rvDeviceList.size(); i++) {
      for (int j = 0; j < rvDeviceList[i]->getDeviceRvVector()->size(); j++)
        outInfo << rvDeviceList[i]->getDeviceRvVector()->at(j).ctrlModName
                << rvDeviceList[i]->getDeviceRvVector()->at(j).value;
    }
  };
};

bool checkDeviceInfo(const Device &device);

#endif
