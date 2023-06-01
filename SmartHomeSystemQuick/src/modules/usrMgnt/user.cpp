#include "user.h"


QString str_usrRole[2] = { "NORMAL", "ADMIN" };

User::User()
{

}



User::User(QString name, QString usrPwd, e_usrRole usrRole,bool empty, int id,QStringList bannedDevicesList)
{
    this->usrName = name;
    this->usrPwd = usrPwd;
    this->usrRole = usrRole;
    this->isEmpty = empty;
    this->id = id;
    this->bannedDeviceList = bannedDevicesList;
}
