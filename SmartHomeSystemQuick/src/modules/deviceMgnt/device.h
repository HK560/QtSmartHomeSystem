#ifndef _DEVICE_H_
#define _DEVICE_H_

#include "../global/init.h"
#include "devicectrl.h"
#include "qhostaddress.h"
#include "qvector.h"
#include "src/modules/deviceMgnt/devicectrl.h"
#include "src/modules/global/protocolhandler.h"

#include <QString>
#include <QVector>
#include <QHostAddress>
#include <QSharedPointer>
enum class e_deviceType { UNKNOW, TYPE_1, TYPE_2 };

enum class e_deviceStatus {
  UNKNOW,
  CONNECTING,
  CONNECTED,
  DISCONNECTED,
  OFFLINE,
  ONLINE
};

class Device {

  QString idname;     // maybe some commbine name and version
  QString deviceName; // show as device name which for user, can be changed

  bool enabled = true; //this device is enabled or disabled

  QHostAddress ipAddress; //

  e_deviceType
      deviceType; // device type, for program to decide how to show and control
  e_deviceStatus deviceStatus; // device status, show status

  QSharedPointer<QVector<QSharedPointer<DeviceCtrl>>> devicesCtrlVector;
  // QVector<DeviceCtrl*>*devicesCtrlVector; 
  // this vector contains devices all connected ctrl
                         // methods, need to be initialized in this class
  QString settingStr;
  QVector<DeviceFunc> deviceRvVector;
public:
  bool funcValid = false;
  Device(QString idname, QHostAddress ip =QHostAddress(),QString deviceName = "<NULL>",
         e_deviceType deviceType = e_deviceType::UNKNOW,
         e_deviceStatus deviceStatus = e_deviceStatus::UNKNOW)
      : idname(idname), deviceName(deviceName),ipAddress(ip), deviceType(deviceType),
        deviceStatus(deviceStatus){
          init();
        };
  ~Device(){ devicesCtrlVector->clear();};

  void setDeviceIdName(const QString idname){this->idname = idname;};
  void setDeviceName(const QString deviceName){this->deviceName = deviceName;};
  void setDeviceType(const e_deviceType type){this->deviceType = type;};
  void setDeviceStatus(const e_deviceStatus status){this->deviceStatus = status;};
  void setDeviceAddress(const QHostAddress address){this->ipAddress = address;};
  void setDeviceEnabled(bool enabled){this->enabled = enabled;};

  QString getDeviceIdName() const{return this->idname;};
  QString getDeviceName() const{return this->deviceName;};
  e_deviceType getDeviceType() const{return this->deviceType;};
  e_deviceStatus getDeviceStatus() const{return this->deviceStatus;};
  QHostAddress getDeviceAddress() const{return this->ipAddress;}
  bool getDeviceEnabled() const{return this->enabled;};
  QSharedPointer<QVector<QSharedPointer<DeviceCtrl>>> getDevicesCtrlVector(){return devicesCtrlVector;};
  void deviceCopyFrom(const Device& device);
  void init();// important 

  QVector<DeviceFunc>* getDeviceRvVector(){return &deviceRvVector;}
  void setDeviceRvVector( QVector<DeviceFunc> ddeviceRvVector){deviceRvVector = ddeviceRvVector;};
  void setFuncValueByName(QString &funcName, QString &funcValue,QString &enabledForAi);

  void setSettingStr(QString settingStr){this->settingStr = settingStr;};

  QString generateSettingStr();
  void readGenerateSettingStr();

};

#endif