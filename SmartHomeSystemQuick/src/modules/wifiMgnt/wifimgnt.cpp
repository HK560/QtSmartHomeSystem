#include "wifimgnt.h"
#include "qpair.h"
#include "qregexp.h"

WifiMgnt::WifiMgnt() {

  outDebug <<"network is online :"<<networkConfigurationManager.isOnline();
  // QList<QNetworkConfiguration> activeConfigs = networkConfigurationManager.allConfigurations(QNetworkConfiguration::Active);
  // for(auto i = activeConfigs.begin();i!=activeConfigs.end();i++){
  //     outDebug <<i->name()<<i->state();
  // }
}

QList<QPair<QString, QString>> WifiMgnt::getAllWifiConnectionsList() {
#ifdef Q_OS_LINUX
  QString result;
  result = terminal.execute("wpa_cli", QStringList() << "-i"
                                                     << "wlan0"
                                                     << "scan");
  if (result != "OK\n") {
    // outDebug << "wifi scan failed:" << result;
    return QList<QPair<QString, QString>>();
  }
  result = terminal.execute("wpa_cli", QStringList() << "-i"
                                                     << "wlan0"
                                                     << "scan_result");
  // outDebug << "wifi scan result:" << result;
#else
  QString result = testText;
  outDebug << "wifi TEST result:" << result;

#endif
  QStringList list = result.split(QRegExp("[\r\n]"), Qt::SkipEmptyParts);
  //   QStringList wifiList;
  QRegExp rx("([\\w:]+)\\t([\\d]+)\\t([-\\d]+)\\t[\\[\\]\\w-]+\\t(.+)");
  wifiList.clear();
  for (auto i = list.begin(); i != list.end(); i++) {
    rx.indexIn(*i);
    // all / bssid / frequency / signal level / flags / ssid
    // outDebug << rx.cap(0) << rx.cap(1) << rx.cap(2) << rx.cap(3) << rx.cap(4);
    if (!rx.cap(0).isEmpty()) {
      wifiList.append(QPair<QString, QString>(rx.cap(4), rx.cap(3)));
    }
  }
  outDebug << "wifiList size:" << wifiList.size();
  return wifiList;
}

void WifiMgnt::regexTest() {

  QStringList list = testText.split(QRegExp("[\r\n]"), Qt::SkipEmptyParts);
  outDebug << list;
  QRegExp rx("([\\w:]+)\\t([\\d]+)\\t([-\\d]+)\\t[\\[\\]\\w-]+\\t(.+)");
  for (auto i = list.begin(); i != list.end(); i++) {
    rx.indexIn(*i);
    outDebug << rx.cap(0) << rx.cap(1) << rx.cap(2) << rx.cap(3) << rx.cap(4);
  }
}

void WifiMgnt::printWifiList() {

  for (auto i = wifiList.begin(); i != wifiList.end(); i++) {
    outDebug << i->first << " " << i->second;
  }
}

QString WifiMgnt::getWifiLevel(int index) {
  int level = wifiList[index].second.toInt();
  // outDebug << "level:" << level;
  QString result = "unknow";
  if (-70 <= level) {
    return QString("Strong");
  } else if (-80 <= level && -70 > level) {
    return QString("mid");
  } else if (-80 > level) {
    return QString("weak");
  }
  return result;
};

bool WifiMgnt::connectWIFI(QString ssid, QString pwd) {
  if (ssid.isEmpty() || pwd.isEmpty()) {
    outDebug << "ssid and pwd must not be empty";
    return false;
  }
  outDebug << ssid << ":" << pwd;
  // add network then sudo wpa_cli -i wlan0 reconfigure
#ifdef Q_OS_LINUX

#if(0)
  outDebug << "trying to write networkdata";
  QString result;
  result = terminal.execute(
          "head", 
          QStringList()
          << "-n"
          << "-5"
          << "/etc/wpa_supplicant/wpa_supplicant.conf"
          << ">"
          << "tmp.conf"
          << "&&mv"
          << "tmp.conf"
          << "/etc/wpa_supplicant/wpa_supplicant.conf");

  result = terminal.execute(
      "echo",
      QStringList()
          << "-e"
          << QString("\"network{\\n\\tssid=\"%1\"\\n\\tpsk=\"%2\"\\n}\\n\"").arg(ssid).arg(pwd)
          << ">>"
          << "/etc/wpa_supplicant/wpa_supplicant.conf");

  result = terminal.execute("wpa_cli", 
                            QStringList()
                            << "-i"
                            << "wlan0"
                            << "reconfigure");
#endif
outDebug << "trying to write networkdata";
QString result;
result = terminal.execute("bash", QStringList()<<"/etc/wpa_supplicant/addNetwork.sh"<<ssid << pwd);

#endif
  return true;
}
