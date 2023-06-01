#ifndef USERMGNT_H
#define USERMGNT_H

#include <QObject>
#include <QString>
// #include <qvector.h>
#include <QList>
#include <QVector>

#include "../global/init.h"
#include "../sqlite/sqlitemgnt.h"
#include "user.h"
#include "userlogin.h"

class UserMgnt : public QObject {
  Q_OBJECT

  QList<User> *allUserList = nullptr; // implemented in userMgnt init
  UserLogin nowLoginUsr;
  SqliteMgnt *sqlmgnt; // implemented in qmlCtrl

public:
  UserMgnt(SqliteMgnt *mgnt = nullptr);
  void init(); // read alluserlist

  QList<User> *loadAllUsers();
  QStringList getUserNameList();
  bool userLoginCheack(User &loginUser);
  int getUserIdByNameByIndex(int index);
  User *getUserByIndex(int index) { return &(*allUserList)[index]; }
  User *getUserById(QString username) {
    QList<User>::const_iterator it;
    for (it = allUserList->constBegin(); it != allUserList->constEnd(); ++it) {
      if ((it->getUsrName()) == username) {
        // 返回指向匹配的User对象的指针
        return const_cast<User *>(&(*it));
      }
    }
    // 如果未找到匹配的User对象，则返回null指针
    return nullptr;
  }
  int getUserListSize() { return allUserList->size(); }
};

#endif // USERMGNT_H
