#include "protocolhandler.h"
#include "qregexp.h"
#include "src/modules/global/protocolhandler.h"

static QStringList initTypesList() {
  QStringList types;
  types << "DC"
        << "DCA"
        << "FN"
        << "FNA"
        << "GET"
        << "GETA"
        << "SET"
        << "SETA"
        << "UNKNOW";
  return types;
}
// if have new key, need to update this func
static QStringList initKeysList() {
  QStringList keys;
  keys << "IP"
       << "ID"
       << "FNAME"
       << "F_LIGHT"
       << "F_NULL"
       << "F_VOLUME"
       << "RV_TEMP"
       << "RV_VALUE"
       << "RV_STR"
       << "RV_SWITCH"
       << "UNKNOW";
  return keys;
}

QStringList g_typesList = initTypesList();
QStringList g_keysList = initKeysList();

bool ProtocolHandler::isValid() {
  if (data.front() == '!' && data.back() == '?')
    return true;
  else {
    outDebug << "data is not valid:[" << data.front() << data.back() << "]";
    return false;
  }
}

e_Ptype ProtocolHandler::getType() {

  QRegExp regex("!(.*)#"); //(.*?)#
  regex.setMinimal(true);
  outDebug << data << regex.indexIn(data);
  QString type = regex.cap(1);
  outDebug << "type:" << type;
  e_Ptype ptype;
  switch (g_typesList.indexOf(type)) {
  case 0:
    ptype = e_Ptype::DC;
  case 1:
    ptype = e_Ptype::DCA;
  case 2:
    ptype = e_Ptype::FN;
  case 3:
    ptype = e_Ptype::FNA;
  case 4:
    ptype = e_Ptype::GET;
  case 5:
    ptype = e_Ptype::GETA;
  case 6:
    ptype = e_Ptype::SET;
  case 7:
    ptype = e_Ptype::SETA;
  default:
    ptype = e_Ptype::UNKNOW;
  }
  this->type = ptype;
  return ptype;
}

//(#.*?\*[^#*?]+) group
// #(.*?)\*([^#*?]+)[#?]*
QVector<QPair<e_Pkey, QString>> ProtocolHandler::getKeyValues() {
  QRegExp regexGroup(R"(#(.+)\?)");
  // regexGroup.setMinimal(true);

  QRegExp regexKey(R"((.[^*]+)\*(.*))");
  // regexGroup.setMinimal(true);

  QVector<QPair<e_Pkey, QString>> keyValueVector;
  regexGroup.indexIn(data);
  QStringList keyGroup = regexGroup.cap(1).split("#");
  // outDebug <<"keyGroupLen =
  // "<<keyGroup.length()<<keyGroup.front()<<keyGroup.back();
  for (int i = 0; i < keyGroup.length(); i++) {
    regexKey.indexIn(keyGroup[i]);
    QStringList keyValue = regexKey.capturedTexts();
    outDebug << "Key and value: " << keyValue;
    keyValueVector.append(
        QPair<e_Pkey, QString>(getKeyFromStr(keyValue[1]), keyValue[2]));
  }
  this->KeyValues = keyValueVector;
  return keyValueVector;
}

e_Pkey ProtocolHandler::getKeyFromStr(const QString &str) {

  switch (g_keysList.indexOf(str)) {
  case 0:
    return e_Pkey::IP;
  case 1:
    return e_Pkey::ID;
  case 2:
    return e_Pkey::FNAME;
  case 3:
    return e_Pkey::F_LIGHT;
  case 4:
    return e_Pkey::F_NULL;
  case 5:
    return e_Pkey::F_VOLUME;
  case 6:
    return e_Pkey::RV_TEMP;
  case 7:
    return e_Pkey::RV_VALUE;
  case 8:
    return e_Pkey::RV_STR;
  case 9:
    return e_Pkey::RV_SWITCH;
  default:
    return e_Pkey::UNKNOW;
  }
  return e_Pkey::UNKNOW;
}

void ProtocolHandler::printTest(QVector<QPair<e_Pkey, QString>> test) {
  outDebug << "print test";
  for (int i = 0; i < test.length(); i++) {
    outDebug << int(test[i].first) << test[i].second;
  }
}

QString ProtocolHandler::getValueByKey(e_Pkey key) {
  QString value;
  for (int i = 0; i < this->KeyValues.size(); ++i) {
    if (this->KeyValues[i].first == key) {
      return this->KeyValues[i].second;
    }
  }
  outWarn << "Cant find the specify key and value";
  return QString();
}

QString
ProtocolHandler::getValueByKey(e_Pkey key,
                               QVector<QPair<e_Pkey, QString>> KeyValues) {
  QString value;
  for (int i = 0; i < KeyValues.size(); ++i) {
    if (KeyValues[i].first == key) {
      return KeyValues[i].second;
    }
  }
  outWarn << "Cant find the specify key and value";
  return QString();
}

DeviceFunc
ProtocolHandler::getDeviceFuncFromKeyValues(QPair<e_Pkey, QString> keyValue) {
  QStringList value = keyValue.second.split("/");
  // outDebug << value;
  int valueType = value[1].toInt();
  QStringList nameAndDesc = value[0].split("<");
  
  // QSharedPointer<DeviceCtrl> funcCtrl;
  // bool vaild = true;

  DeviceFunc deviceFunc;
  deviceFunc.keyword = keyValue.first;
  deviceFunc.ctrlModName = nameAndDesc[0];
  deviceFunc.desc = nameAndDesc[1];
  deviceFunc.type = valueType;
  deviceFunc.value = value[2];
  outDebug << nameAndDesc<<value;
  return deviceFunc;
}
