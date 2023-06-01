#ifndef INIT_H
#define INIT_H

#include <QDebug>
#include <QString>
#include <QtGlobal>
#include <QSharedPointer>

#if _MSC_VER >= 1600

#pragma execution_character_set("utf-8")

#endif
#define debugN(str) qDebug("%s:%d  FUNC(%s):\t%s",__FILE__,__LINE__,__FUNCTION__,str)
#define debugM(str, ...) qDebug("%s(%d)-<%s>: str"##str, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define outDebug qDebug()
#define outInfo qInfo()
#define outWarn qWarning()

#define ESP8266_TCP_PORT 5656
#define ESP8266_UDP_PORT 5600
#define LOCAL_UDP_PORT 56700




#endif // INIT_H
