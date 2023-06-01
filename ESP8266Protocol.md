# SmartHomeSys and ESP8266 Protocol

This protocol is designed to be used for the sys communication with the ESP8266.

It is designed to be used with udp protocol;

## Details

### ESP8266 discovery UDP

```
sys:    !DC#IP*(SysIP)?                       //!DC#IP#*192.168.31.6*?  
8266:   !DCA#IP*(8266IP)#ID*(deviceID)#RV_TEMP*(Name)<(desc)/(type)/(value)?     

//!DCA#IP*192.168.31.78#ID*D0001?
```
sys收到udp包后，创建一个设备对象用ip和id初始化，名字可以重名，用id区分， 设备列表的设备对象维护一个独立的id

### ESP8266 get function
```
sys:    !FN#FNAME*(deviceNAME)?
8266:   !FNA#F_LIGHT*(Name)<(desc)/(type)/(value)#F_NULL*(Name)<(desc)/(type)/(value)?       //注意要禁用这些特殊符号

```
### get value ESP8266
```
sys:    !GET#FNAME*(deviceNAME)?
8266:   !GETA#F_LIGHT*(Name)<(desc)/(type)/(value)#F_NULL*(Name)<(desc)/(type)/(value)?  
```
### set value ESP8266

```
sys:    !SET#F_LIGHT*(Name)/(type)/(value)#F_NULL*(Name)/(type)/(value)?
8266:   !SETA#OK*0?
```

## type

0   bool
1   int
2   str

F_LIGHT     light setting
F_VOlUME    volume setting
F_SWITCH    switch setting
F_NULL
F_TRIGGER   trigger