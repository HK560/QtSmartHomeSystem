#ifndef USER_H
#define USER_H

#include <QString>
#include <QVector>
// #include <QDateTime>
#include <QStringList>

enum e_usrRole { NORMAL, ADMIN };
extern QString str_usrRole[2];

class User {

  int id = -1;
  QString usrName = "<NULL>";
  QString usrPwd = "";

  e_usrRole usrRole = NORMAL;

  bool isEmpty = true;

  
  // avator image
public:
  User();
  User(QString name, QString usrPwd, e_usrRole usrRole = NORMAL,
       bool empty = false, int id = -1, QStringList bannedDevicesList = QStringList());

  QStringList bannedDeviceList;

  QString getUsrName() const { return usrName; }
  QString getUsrPwd() const { return usrPwd; }
  e_usrRole getUsrRole() const { return usrRole; }
  bool getUsrEmpty() const { return isEmpty; }
  int  getUsrId() const { return id; }

  void setUsrName(QString name) { usrName = name; }
  void setUsrPwd(QString pwd) { usrPwd = pwd; }
  void setUsrRole(e_usrRole role) { usrRole = role; }
  void setUsrEmpty(bool empty) {isEmpty = empty;}
  void setUsrId(int idd) {id = idd;}



};
#endif // USER_H
