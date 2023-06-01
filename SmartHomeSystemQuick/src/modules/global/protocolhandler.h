#ifndef PROTOCOLHANDLER_H
#define PROTOCOLHANDLER_H

#include "init.h"
#include "qpair.h"
#include <QByteArray>
#include <QPair>
#include <QString>
#include <QVector>
#include <QRegExp>


#define MIN_F_KEY 3
#define MAX_F_KEY 5
#define MIN_RV_KEY 6
#define MAX_RV_KEY 9

enum class e_Ptype { DC, DCA, FN, FNA, GET, GETA, SET, SETA 

,UNKNOW};

enum class e_Pkey {
  IP,
  ID,
  FNAME,

  F_LIGHT,
  F_NULL,
  F_VOLUME,

  RV_TEMP,
  RV_VALUE,
  RV_STR,
  RV_SWITCH,

  UNKNOW
};

//if have new key, need to update this func

typedef struct {
  e_Pkey keyword;
  QString ctrlModName;
  QString desc;
  int type;
  QString value;
} DeviceFunc;

class ProtocolHandler {
  QByteArray data;
  e_Ptype type;
   QVector<QPair<e_Pkey, QString>> KeyValues;

public:
  ProtocolHandler(QByteArray ddata) : data(ddata){
    
  };
  bool isValid();
  e_Ptype getType() ; //if have new key, need to update this func
//   e_Pkey getKey() const;
  QVector<QPair<e_Pkey, QString>> getKeyValues();
  e_Pkey getKeyFromStr(const QString &str); //if have new key, need to update this func
  QString getValueByKey(e_Pkey key);
  QString getValueByKey(e_Pkey key, QVector<QPair<e_Pkey, QString>> KeyValues); 

  DeviceFunc getDeviceFuncFromKeyValues(QPair<e_Pkey, QString> keyValue);
  
  void printTest( QVector<QPair<e_Pkey, QString>> test);
};



extern QStringList g_typesList ;
extern QStringList g_keysList ;
#endif // PROTOCOLHANDLER_H
