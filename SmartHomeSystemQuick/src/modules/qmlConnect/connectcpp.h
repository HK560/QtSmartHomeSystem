#ifndef CONNECTCPP_H
#define CONNECTCPP_H

#include "../global/init.h"
#include <QObject>
#include <QNetworkConfigurationManager>
class ConnectCpp : public QObject {
  Q_OBJECT
public:
  explicit ConnectCpp(QObject *parent = nullptr);
  QNetworkConfigurationManager networkConfigurationManager;
  bool m_wifiStatus = false;
  
  
  Q_PROPERTY(bool wifiStatus MEMBER m_wifiStatus NOTIFY wifiStatusChanged);


public slots:
  
  void setWifiStatus(bool status) {
    m_wifiStatus = status;
    outDebug << "network status changed:" << status;
  };



signals:
  void wifiStatusChanged(const bool &newStatus);


};

#endif // CONNECTCPP_H
