#include "connectcpp.h"

ConnectCpp::ConnectCpp(QObject *parent)
    : QObject{parent}
{
    connect(&networkConfigurationManager,
          SIGNAL(onlineStateChanged(bool)), this,
          SLOT(setWifiStatus(bool)));
}
