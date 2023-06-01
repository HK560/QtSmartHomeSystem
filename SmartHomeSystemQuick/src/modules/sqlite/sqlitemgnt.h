#ifndef SQLITEMGNT_H
#define SQLITEMGNT_H

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include "../deviceMgnt/device.h"
#include "../global/init.h"
#include "../usrMgnt/user.h"

class SqliteMgnt {
public:
  SqliteMgnt();
  ~SqliteMgnt() {
    db.close();
    qDebug("db close");
  }
  void initDb();

  void createUserTable();
  void userInsertRecord(const User &usr);
  void userDeleteRecord(const User &usr);
  void userUpdateRecord(const User &usr);
  User userSearchRecord(const QString &name);
  int userGetAllUsersRecords(QList<User> *users);
  bool userExistsCheck(User &usr);

  void createDeviceInfoTable();
  void DeviceInfoInsertRecord(Device *device);
  bool DeviceGetRecord(Device *device);

  void createUserSettingTable();
  void initInsertUserSetting(QString userId);
  void updateUserSettingBannedDevice(QString userId, QString deviceID);
  QStringList getUserSettingBannedDevices(int userId);
  void settingInsertWeatherCode(const QString userId, const QString cityCode);
  QString settingGetWeatherCode(const QString userId);
  QStringList getAllDeviceIdRecord();
  void updateUserName(QString id, QString newName);
  void updateUserPwd(QString id, QString newPwd);
  QStringList userGetAllUsersName();
  void updateUserBannedDevice(const User &user);

private:
  QSqlDatabase db;

  void sqlExecute(const QString sql);
};

#endif // SQLITE_H
