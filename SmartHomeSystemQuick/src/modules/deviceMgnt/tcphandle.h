#ifndef TCPHANDLE_H
#define TCPHANDLE_H

#include <QObject>
#include <QTcpSocket>
#include <QMutex>
#include <QMutexLocker>
#include <QHostAddress>
#include "../global/init.h"
#include "qmutex.h"
#include "qobject.h"
#include <QThread>

class TcpHandle : public QObject
{
    Q_OBJECT

    QTcpSocket *socket;

    QHostAddress ipAddress;

    int port;

    QByteArray buffer;

    int status = 0;

    QMutex * lock;

    QByteArray recvData;
public:
    explicit TcpHandle(const QHostAddress &ip, const int &port, QByteArray& data);
    ~TcpHandle();
    // virtual void run() override;
    void connectAndSend();
    bool sendData();
    int getStatus(){QMutexLocker locker(lock);return status;};
    QByteArray getRecvData(){return recvData;};
    
signals:
    void getDataReady(QByteArray data);
};

#endif // TCPHANDLE_H
