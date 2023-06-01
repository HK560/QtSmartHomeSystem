#include "tcphandle.h"
#include "qhostaddress.h"
#include "qmutex.h"
#include "qtcpsocket.h"

TcpHandle::TcpHandle(const QHostAddress &ip, const int &port, QByteArray &data)
    : ipAddress(ip), port(port), buffer(data) {
  socket = new QTcpSocket(this);
  lock = new QMutex();
  connect(socket, &QTcpSocket::readyRead, [=]() {
    // 接收服务器发送的数据
    outDebug << "Get tcp msg";
    QByteArray data = socket->readAll();
    if (!data.isEmpty()) {
      recvData = data;
      outDebug << "msg: " << recvData;
      QMutexLocker locker(lock);
      status = 2;
      emit getDataReady(data);
    }
  });

  // 检测是否和服务器是否连接成功了
  connect(socket, &QTcpSocket::connected, this, [=]() {
    outDebug << "connect to tcpserver success";
    QMutexLocker locker(lock);
    status = 1;
  });

  // 检测服务器是否和客户端断开了连接
  connect(socket, &QTcpSocket::disconnected, this, [=]() {
    QMutexLocker locker(lock);
    outDebug << "disconnect from tcpserver";
    status = 4;
  });

  connect(socket, &QTcpSocket::errorOccurred, this,
          [=](QAbstractSocket::SocketError error) { outDebug << error; });
}

bool TcpHandle::sendData() {
  buffer.append('\r');
  int size = socket->write(buffer);
  outDebug << "write tcp data" << buffer << size;
  {
    QMutexLocker locker(lock);
    if (size <= 0) {
      status = -1;
      return status;
    } else {
      status = 3;
      outDebug <<"already write tcp data";
      return status;
    };
  }
}

TcpHandle::~TcpHandle() {
  socket->disconnect();
  socket->close();
  // quit();
  // wait();
  delete lock;
  delete socket;
}

void TcpHandle::connectAndSend() {
  socket->connectToHost(QHostAddress(ipAddress), port);
  //   socket->isValid();
  bool isconnect = socket->waitForConnected();
  if (isconnect)
    sendData();
  outDebug <<"done";
}