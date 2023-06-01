#ifndef WIFIMGNT_H
#define WIFIMGNT_H

#include "../global/init.h"
#include "../global/terminalexec.h"
#include "src/modules/global/terminalexec.h"
#include <QNetworkConfigurationManager>
#include <QList>
#include <QPair>
#include <QRegExp>


class WifiMgnt {

  // QNetworkSession *session;
  TerminalExec terminal;
  QList<QPair<QString, QString>> wifiList;
  QString testText = "bssid / frequency / signal level / flags / ssid\n   \
     a4:39:b3:75:f6:e5	2447	-24	[WPA2-PSK-CCMP][WPS][ESS]	elbadaernU\n    \
     a4:39:b3:75:f6:e6	5765	-28	[WPA2-PSK-CCMP][WPS][ESS]	别人家的wifi\n    \
    ";

public:
  WifiMgnt();
  QNetworkConfigurationManager networkConfigurationManager;
  QList<QPair<QString, QString>> getAllWifiConnectionsList();
  void printWifiList();
  void regexTest();

  bool connectWIFI(QString ssid, QString pwd);

  int getWifiListSize() { return wifiList.size(); };
  QString getWifiName(int index) { return wifiList[index].first; };
  QString getWifiLevel(int index);


};

#endif // WIFIMGNT_H
