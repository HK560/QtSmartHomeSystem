#include "usermgnt.h"

UserMgnt::UserMgnt(SqliteMgnt *mgnt) {
  sqlmgnt = mgnt;

  allUserList = new QList<User>;
}

void UserMgnt::init() {
  qDebug() << "userMgnt init start";
  // allUserList->clear();
  loadAllUsers();
}

QList<User> *UserMgnt::loadAllUsers() {
  sqlmgnt->userGetAllUsersRecords(allUserList);
  return allUserList;
}

bool UserMgnt::userLoginCheack(User &loginUser) {
  QString userName = loginUser.getUsrName();
  QString pwd = loginUser.getUsrPwd();
  for (auto i = allUserList->begin(); i != allUserList->end(); i++) {
    if (i->getUsrName() == userName && i->getUsrPwd() == pwd) {
      // loginUser.setUsrId(i->getUsrId());
      // loginUser.setUsrRole(i->getUsrRole());
      qDebug() << "login user exist!";
      return true;
    }
  }
  qDebug() << "cant find login user!";
  return false;
}

QStringList UserMgnt::getUserNameList() {
  QStringList userNameList;
  for (auto i = allUserList->begin(); i != allUserList->end(); i++) {
    userNameList.append(i->getUsrName());
  }
  outInfo<<userNameList;
  return userNameList;
}

int UserMgnt::getUserIdByNameByIndex(int index){
    return allUserList->at(index).getUsrId();
}