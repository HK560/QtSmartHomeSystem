#ifndef _DEVICE_CTRL_H_
#define _DEVICE_CTRL_H_

#include "../global/init.h"

#include "../global/protocolhandler.h"
#include "src/modules/global/protocolhandler.h"
#include <QByteArray>
#include <QString>

class DeviceCtrl {

protected:
  // e_Pkey keyType;
  int type;     // value type
  bool enabled; // control whether this ctrl is enabled or disabled

  QString ctrlModName; //show up name
  e_Pkey keyword; // show up type

  QString desc;

  QString value;

  bool enabledForAI = false;
public:
  DeviceCtrl(e_Pkey kkeyword, QString cctrlModName, QString ddesc, int ttype,
             QString vvalue, bool eenabled = false)
      : type(ttype), enabled(eenabled), ctrlModName(cctrlModName),desc(ddesc),
        keyword(kkeyword), value(vvalue){};

  QString getCtrlModName() { return ctrlModName; };
  e_Pkey getKeyword() { return keyword; };
  int getType() { return type; };
  bool isEnabled() { return enabled; };
  QString getValue() { return value; };
  QString getDesc() { return desc; };
  bool getEnabledForAI(){return enabledForAI;};

  void setKeyword(e_Pkey kkeyword) { keyword = kkeyword; };
  void setValue(QString vvalue) { value = vvalue; };
  void setEnabled(bool eenabled) { enabled = eenabled; };
  void setType(int ttype) { type = ttype; };
  void setCtrlModName(QString cctrlModName) { ctrlModName = cctrlModName; };
  void setDesc(QString ddesc) { desc = ddesc; };
  void setEnabledForAI(const bool &eenabled) { enabledForAI = eenabled; };
};

// class DeviceCtrlBool : public DeviceCtrl {

//   bool status; // control status

// public:
//   DeviceCtrlBool(e_Pkey kkeyword, QString cctrlModName, int ttype,
//                  bool eenabled = false, bool sstatus = false)
//       : DeviceCtrl(kkeyword, cctrlModName, ttype, eenabled), status(sstatus){};

//   void setStatus(bool sstatus) { status = sstatus; };
//   bool getStatus() { return status; };
// };

// class DeviceCtrlValue : public DeviceCtrl {

//   int value;

// public:
//   DeviceCtrlValue(e_Pkey kkeyword, QString cctrlModName, int ttype,
//                   bool eenabled = false, int vvalue = -1)
//       : DeviceCtrl(kkeyword, cctrlModName, ttype, eenabled), value(vvalue){};

//   void setValue(int vvalue) { value = vvalue; };
//   int getValue() { return value; };
// };

// class DeviceCtrlStr : public DeviceCtrl {

//   QString str;

// public:
//   DeviceCtrlStr(e_Pkey kkeyword, QString cctrlModName, int ttype,
//                 bool eenabled = false, QString sstr = QString())
//       : DeviceCtrl(kkeyword, cctrlModName, ttype, eenabled), str(sstr){};

//   void setStr(QString sstr) { str = sstr; };
//   QString getValue() { return str; };
// };

#endif
