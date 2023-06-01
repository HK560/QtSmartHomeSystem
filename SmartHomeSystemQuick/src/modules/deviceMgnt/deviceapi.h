#ifndef DeviceApi_H
#define DeviceApi_H

#include "../global/init.h"
#include "qpair.h"
#include "qvector.h"
#include "src/modules/deviceMgnt/devicemgnt.h"
#include "src/modules/global/init.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QString>
#include <QStringList>
#include <QVector>

struct DeviceControlData {
  QString deviceName;
  QString deviceFunc;
  QString ctrlType;
  QString value;
};
struct DeviceControlInfo {
  int deviceIndex;
  int funcIndex;
  QString funcName;
  QString value;
};
enum DeviceControlType { DT_switch, DT_int, DT_string, DT_COUNT };

struct DeviceFuncData {
  int funcIndex;
  QString funcName;
  DeviceControlType type;
};

struct DeviceData {
  int deviceIndex;
  QString deviceName;
  QVector<DeviceFuncData> deviceFuncAndIndex;
  // QVector<QPair<DeviceControlType, int>> ;
  // QVariant value;
};

class DeviceApi : public QObject {
  Q_OBJECT

  QVector<DeviceData> *deviceCtrlDataList = nullptr;

  DeviceMgnt *deviceMgnt = nullptr;
  // QVector<QPair<QString, int>> *deviceNamePairList;

  // QVector<QPair<QString, int>> *deviceFuncairList;

public:
  explicit DeviceApi(QObject *parent = nullptr,
                     DeviceMgnt *ddeviceMgnt = nullptr);

  void updateDeviceData();
  QString generateCommand();

  QVector<DeviceData> *getDeviceControlDataList() {
    return deviceCtrlDataList;
  };

  static void printDeviceControlData(const DeviceControlData &data) {
    outDebug << "Device Name: " << data.deviceName;
    outDebug << "Device Function: " << data.deviceFunc;
    outDebug << "Control Type: " << data.ctrlType;
    outDebug << "Value: " << data.value;
  }
  static DeviceControlData parseJsonString(const QString &inputString,
                                           QString &outputString,
                                           bool &jsonFound) {
    DeviceControlData data;
    int start = inputString.indexOf("##") + 2;
    int end = inputString.lastIndexOf("##");

    if (start == -1 || end == -1 || start >= end) {
      // JSON string not found
      jsonFound = false;
      outputString = inputString;
      outInfo << "JSON string not found";
      return data;
    }
    outInfo << "JSON string found !";

    jsonFound = true;
    QString jsonString = inputString.mid(start, end - start);

    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject jsonObj = jsonDoc.object();

    data.deviceName = jsonObj["deviceName"].toString();
    data.deviceFunc = jsonObj["deviceFunc"].toString();
    data.ctrlType = jsonObj["ctrlType"].toString();

    if (data.ctrlType == "switch") {
      data.value =jsonObj["value"].toString() == QString("true") ? "1":"0";
    } else if (data.ctrlType == "string") {
      data.value = jsonObj["value"].toString();
    } else if (data.ctrlType == "int") {
      data.value = jsonObj["value"].toInt();
    }

    outputString = inputString.left(start - 2) + inputString.mid(end + 2);
    return data;
  }

  QString type2Str(const DeviceControlType &type) {
    switch (type) {
    case DT_switch:
      return "switch";
    case DT_int:
      return "int";
    case DT_string:
      return "string";
    default:
      return "0";
    }
  }
  void printDeviceControlInfo(const DeviceControlInfo &info) {
    qDebug() << "Device Index: " << info.deviceIndex;
    qDebug() << "Function Index: " << info.funcIndex;
    qDebug() << "Control Value: " << info.value;
  }
  DeviceControlInfo findDeviceControl(const DeviceControlData &controlData);
signals:
  void sendDeviceCtrlSingle(const DeviceControlInfo &info);
};

#endif // DeviceApi_H
