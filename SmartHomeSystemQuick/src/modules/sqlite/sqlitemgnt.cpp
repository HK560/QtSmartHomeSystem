#include "sqlitemgnt.h"
#include "../usrMgnt/user.h"
#include "qdebug.h"
#include "qsqlerror.h"
#include "qsqlquery.h"
#include "src/modules/global/init.h"

SqliteMgnt::SqliteMgnt() {}

void SqliteMgnt::initDb() {
  qDebug() << "initDb start";
  // qDebug()<<QSqlDatabase::drivers();//打印驱动列表
  //  QSqlDatabase db;
  // 检测已连接的方式 - 默认连接名
  // QSqlDatabase::contains(QSqlDatabase::defaultConnection)
  if (QSqlDatabase::contains("qt_sql_default_connection"))
    db = QSqlDatabase::database("qt_sql_default_connection");
  else
    db = QSqlDatabase::addDatabase("QSQLITE");
  // 检测已连接的方式 - 自定义连接名
  /*if(QSqlDatabase::contains("mysql_connection"))
      db = QSqlDatabase::database("mysql_connection");
  else
      db = QSqlDatabase::addDatabase("QSQLITE","mysql_connection");*/
  // 设置数据库路径，不存在则创建
  db.setDatabaseName("sqltest.db");
  // db.setUserName("gongjianbo");  //SQLite不需要用户名和密码
  // db.setPassword("qq654344883");

  // 打开数据库
  if (db.open()) {
    qDebug() << "open success";
    // debugN("open success");
    // debugM("open success",1);

    // 关闭数据库
    //  db.close();
  }
}

void SqliteMgnt::createUserTable() {
  // 如果不存在则创建my_table表
  // id自增,name唯一
  const QString sql = R"(
                      CREATE TABLE IF NOT EXISTS  user (
                      id   INTEGER   PRIMARY KEY AUTOINCREMENT NOT NULL,
                      name CHAR (50) UNIQUE NOT NULL,
                      password  CHAR (50),
                      role INTEGER NOT NULL
                      );)";
  // QSqlQuery构造前，需要db已打开并连接
  // 未指定db或者db无效时使用默认连接进行操作
  QSqlQuery query(db);
  if (query.exec(sql)) {
    qDebug() << "init table success";
  } else {
    // 打印sql语句错误信息
    qDebug() << "init table error" << query.lastError();
  }
}

void SqliteMgnt::sqlExecute(const QString sqlstr) {
  QSqlQuery query;
  QString execSqlStr = sqlstr;
  if (query.exec(execSqlStr)) {
    qDebug() << "success";
    // debugN("success");
  } else {
    // 打印sql语句错误信息
    qDebug() << "error: " << query.lastError();
  }
}

void SqliteMgnt::userInsertRecord(const User &usr) {
  QSqlQuery query(db);
  // 方式一，直接执行SQL语句
  query.exec(
      QString(R"(INSERT INTO user(name,password,role) VALUES('%1','%2',%3);)")
          .arg(usr.getUsrName())
          .arg(usr.getUsrPwd())
          .arg(usr.getUsrRole()));
  // 方式二，绑定值，待定变量默认用问号占位,注意字符串也没有引号
  /*query.prepare(R"(INSERT INTO my_table(name,age) VALUES(?,?);)");
  query.addBindValue(name);
  query.addBindValue(age);
  query.exec();*/
}

// 删除数据
void SqliteMgnt::userDeleteRecord(const User &usr) {
  QSqlQuery query;
  // 方式一，直接执行SQL语句
  query.exec(
      QString(R"(DELETE FROM user WHERE name='%1';)").arg(usr.getUsrName()));
  // 方式二，绑定值，待定变量默认用问号占位
  /*query.prepare(R"(DELETE FROM my_table WHERE name=?;)");
  query.addBindValue(name);
  query.exec();*/
}

// 更新数据
void SqliteMgnt::userUpdateRecord(const User &usr) {
  QSqlQuery query;
  // 方式一，直接执行SQL语句
  query.exec(
      QString(R"(UPDATE user SET password='%2', role=%3 WHERE name='%1';)")
          .arg(usr.getUsrName())
          .arg(usr.getUsrPwd())
          .arg(usr.getUsrRole()));
  // 方式二，绑定值，待定变量默认问号，可自定义
  /*query.prepare(R"(UPDATE my_table SET age=:age WHERE name=:name;)");
  query.bindValue(":name",name);//通过自定义的别名来替代
  query.bindValue(":age",age);
  query.exec();*/
}

// 查询数据
User SqliteMgnt::userSearchRecord(const QString &name) {
  QSqlQuery query;
  query.exec(
      QString(R"(SELECT id, name, password, role FROM user WHERE name='%1';)")
          .arg(name));

  // 获取查询结果的第0个值，
  // 如果结果是多行数据，可用while(query.next()){}遍历每一行
  if (!query.size()) {
    qDebug() << "cant find " << name;
    return User();
  }

  User user;
  int id = -1;
  QString usrName;
  QString password;
  e_usrRole role = NORMAL;

  if (query.next()) {
    id = query.value(0).toInt();
    usrName = query.value(1).toString();
    password = query.value(2).toString();
    role = e_usrRole(query.value(3).toInt());
    qDebug() << "Find usr:" << id << usrName << password << str_usrRole[role];
    return User(usrName, password, role, false, id);
  }
  qDebug() << "error ";

  return User();
}

QStringList SqliteMgnt::userGetAllUsersName() {
  QSqlQuery query(db);
  query.exec(QString(R"(SELECT name FROM user ;)"));
  outDebug << query.lastError().text();
  QStringList userNamelist;
  while (query.next()) {
    userNamelist.append(query.value(0).toString());
  }
  outInfo << userNamelist;
  return userNamelist;
}

int SqliteMgnt::userGetAllUsersRecords(QList<User> *users) {
  QSqlQuery query(db);
  int userCount = 0;
  int id = -1;
  QString usrName;
  QString password = "";
  e_usrRole role = NORMAL;
  QStringList bannedDeviceList;

  query.exec(QString(
      R"(SELECT u.id, u.name, u.password, u.role, d.bannedDevice FROM user u LEFT JOIN usersetting d ON u.id = d.userid;)"));
  if (!query.size()) {
    qDebug() << "cant find any user ";
    return 0;
  }

  while (query.next()) {
    id = query.value(0).toInt();
    usrName = query.value(1).toString();
    password = query.value(2).toString();
    role = e_usrRole(query.value(3).toInt());
    bannedDeviceList = query.value(4).toString().split("/");
    bannedDeviceList.removeAll("");
    qDebug() << "Find usr:" << id << usrName << password << role
             << bannedDeviceList;
    users->append(User(usrName, password, role, false, id, bannedDeviceList));
    userCount++;
  }
  qDebug() << "all users count :" << userCount;
  return userCount;
}

bool SqliteMgnt::userExistsCheck(User &usr) {
  QSqlQuery query(db);
  QString sql =
      QString(
          R"(SELECT id, name, password, role FROM user WHERE name = '%1' and password = '%2';)")
          .arg(usr.getUsrName())
          .arg(usr.getUsrPwd());

  query.exec(sql);
  if (!query.size()) {
    qDebug() << "cant find any user ";
    return false;
  }

  if (query.next()) {
    usr.setUsrId(query.value(0).toInt());
    usr.setUsrName(query.value(1).toString());
    usr.setUsrPwd(query.value(2).toString());
    usr.setUsrRole(e_usrRole(query.value(3).toInt()));
    qDebug() << "Find Exist usr:" << usr.getUsrName();
    return true;
  }
  return false;
}

void SqliteMgnt::createDeviceInfoTable() {

  const QString sql = R"(
                      CREATE TABLE IF NOT EXISTS  device (
                      idname   CHAR (10)   PRIMARY KEY  NOT NULL,
                      name CHAR (50) ,
                      ip  CHAR (50),
                      enable INTEGER,
                      setting CHAR (50)
                      );)";
  QSqlQuery query(db);
  if (query.exec(sql)) {
    qDebug() << "init table success";
  } else {
    // 打印sql语句错误信息
    qDebug() << "init table error" << query.lastError();
  }
}

void SqliteMgnt::DeviceInfoInsertRecord(Device *device) {
  QSqlQuery query(db);
  // 方式一，直接执行SQL语句
  query.exec(
      QString(
          R"(INSERT INTO device(idname,name,ip,enable,setting) VALUES('%1','%2','%3',%4,'%5') 
                ON CONFLICT(idname) DO UPDATE SET name='%2', ip='%3',enable=%4, setting='%5';)")
          .arg(device->getDeviceIdName())
          .arg(device->getDeviceName())
          .arg(device->getDeviceAddress().toString())
          .arg((int)device->getDeviceEnabled())
          .arg(device->generateSettingStr()));
  outDebug << query.lastError().text();
}

bool SqliteMgnt::DeviceGetRecord(Device *device) {
  QSqlQuery query(db);
  QString sql =
      QString(
          R"(SELECT idname, name, ip, enable, setting FROM device WHERE idname = '%1';)")
          .arg(device->getDeviceIdName());

  query.exec(sql);
  outDebug << query.lastError().text();

  if (!query.size()) {
    outDebug << "cant find the device ";
    return false;
  }

  if (query.next()) {
    device->setDeviceName(query.value(1).toString());
    // device->setDeviceAddress(QHostAddress(query.value(2).toString())); //for
    // bug fix
    device->setDeviceEnabled(query.value(3).toInt());
    device->setSettingStr(query.value(4).toString());
    outDebug << "Find Exist device:" << query.value(0).toString();
    return true;
  }
  outWarn << "failed";
  return false;
}

QStringList SqliteMgnt::getAllDeviceIdRecord() {
  QSqlQuery query(db);
  query.exec(QString(R"(SELECT idname FROM device;)"));
  outDebug << query.lastError().text();
  QStringList deviceNamelist;
  while (query.next()) {
    deviceNamelist.append(query.value(0).toString());
  }
  outInfo << deviceNamelist;
  return deviceNamelist;
}

void SqliteMgnt::createUserSettingTable() {
  const QString sql = R"(
                      CREATE TABLE IF NOT EXISTS  usersetting (
                      userId   INTEGER  PRIMARY KEY  NOT NULL ,
                      weatherCityCode CHAR (50),
                      bannedDevice CHAR (50)
                      );)";
  // QSqlQuery构造前，需要db已打开并连接
  // 未指定db或者db无效时使用默认连接进行操作
  QSqlQuery query(db);
  if (query.exec(sql)) {
    qDebug() << "init table success";
  } else {
    // 打印sql语句错误信息
    qDebug() << "init table error" << query.lastError();
  }
}

void SqliteMgnt::initInsertUserSetting(QString userId) {
  QSqlQuery query(db);
  // 方式一，直接执行SQL语句
  query.exec(QString(
                 R"(INSERT INTO usersetting(userId) 
                SELECT %1
                WHERE NOT EXISTS (SELECT 1 FROM usersetting WHERE userId = %1);)")
                 .arg(userId));
  outDebug << query.lastError().text();
}

void SqliteMgnt::updateUserSettingBannedDevice(QString userId,
                                               QString deviceID) {
  QSqlQuery query(db);
  QString record;
  query.exec(QString(
                 R"(SELECT bannedDevice
          FROM usersetting
          WHERE userId = %1;)")
                 .arg(userId));
  outDebug << query.lastError().text();
  if (!query.size()) {
    outWarn << "cant find the usersetting ";
    return;
  }
  if (!query.next()) {
    outWarn << "failed";
    return;
  }

  record = query.value(1).toString();
  outDebug << "get bannedDevice from db:" << record;
  if (record.isEmpty()) {
    outDebug << "bannedDeivce is empty";
  }
  record.append('/');
  record.append(deviceID);

  query.exec(QString(
                 R"(
      UPDATE usersetting SET bannedDevice = '%2' WHERE userid = %1;
    )")
                 .arg(userId)
                 .arg(record));
  outDebug << query.lastError().text();

  // device->setDeviceAddress(QHostAddress(query.value(2).toString()));
}

QStringList SqliteMgnt::getUserSettingBannedDevices(int userId) {
  QSqlQuery query(db);
  QString record;
  query.exec(QString(
                 R"(SELECT bannedDevice
          FROM usersetting
          WHERE userId = %1;)")
                 .arg(QString::number(userId)));
  outDebug << query.lastError().text();
  if (!query.size()) {
    outWarn << "cant find the usersetting ";
    return QStringList();
  }
  if (!query.next()) {
    outWarn << "failed";
    return QStringList();
  }
  record = query.value(1).toString();
  outDebug << "get bannedDevice from db:" << record;
  if (!record.isEmpty()) {
    QStringList parts = record.split("/");
    parts.removeFirst();
    // for (const QString& part : parts) {
    //     qDebug() << part;
    // }
    return parts;
  } else {
    outDebug << "bannedDeivce is empty";
    return QStringList();
  }
}

void SqliteMgnt::settingInsertWeatherCode(QString userId, QString cityCode) {

  QSqlQuery query(db);
  // 方式一，直接执行SQL语句
  query.exec(
      QString(
          R"(INSERT INTO usersetting(userId,weatherCityCode) VALUES(%1,'%2') 
                ON CONFLICT(userId) DO UPDATE SET weatherCityCode='%2';)")
          .arg(userId)
          .arg(cityCode));
  outDebug << query.lastError().text() << "with value" << userId << cityCode;
}

QString SqliteMgnt::settingGetWeatherCode(QString userId) {
  QSqlQuery query(db);
  QString sql =
      QString(
          R"(SELECT userId, weatherCityCode FROM usersetting WHERE userId = '%1';)")
          .arg(userId);

  query.exec(sql);
  outDebug << query.lastError().text();

  if (!query.size()) {
    outDebug << "cant find the usersetting ";

    return "";
  }

  if (query.next()) {
    outDebug << "get weathercode from db:" << query.value(1).toString();
    return query.value(1).toString();
    // device->setDeviceAddress(QHostAddress(query.value(2).toString()));
  }
  outWarn << "failed";
  return "";
};

void SqliteMgnt::updateUserName(QString id, QString newName) {
  QSqlQuery query(db);
  QString sql = QString(R"(UPDATE user SET name = '%1' WHERE id = %2;)")
                    .arg(newName)
                    .arg(id);
  query.exec(sql);
  outDebug << query.lastError().text();
}

void SqliteMgnt::updateUserPwd(QString id, QString newPwd) {
  QSqlQuery query(db);
  QString sql = QString(R"(UPDATE user SET password = '%1' WHERE id = %2;)")
                    .arg(newPwd)
                    .arg(id);
  query.exec(sql);
  outDebug << query.lastError().text();
}

void SqliteMgnt::updateUserBannedDevice(const User &user) {
  QSqlQuery query(db);
  QString newbannedDevice;
  QString userid = QString::number(user.getUsrId());
  for (int i = 0; i < user.bannedDeviceList.size(); ++i) {
    newbannedDevice.append(user.bannedDeviceList[i]).append("/");
  }
  outInfo << "going to update banneddevice in " << user.getUsrName()
          << newbannedDevice;

  QString sql =
      QString(R"(UPDATE usersetting SET bannedDevice = '%1' WHERE userid = %2;)")
          .arg(newbannedDevice)
          .arg(userid);
  query.exec(sql);
  if (query.lastError().type() != QSqlError::NoError)
    outWarn<<query.lastError().text();
}