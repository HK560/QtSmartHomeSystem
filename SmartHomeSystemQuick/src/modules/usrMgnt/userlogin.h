#ifndef USERLOGIN_H
#define USERLOGIN_H

#include <QDebug>

#include "../global/init.h"
#include "user.h"

class UserLogin {

  // deviceList
public:
  UserLogin(User *user) { usr = user; };
  UserLogin(){};
  User* usr; // public for convenience


  bool loginState = false; 

  void setUser(User *user) { usr = user; loginState = true;}
  void outputUsrInfo() {
    qDebug() << "Now UsrLogin usr info:" << usr->getUsrId() << usr->getUsrName()
             << usr->getUsrPwd() << usr->getUsrRole();
  }
};

#endif // USERLOGIN_H
