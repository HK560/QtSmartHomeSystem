QT +=
QT       += core gui quickwidgets
QT += widgets
QT += sql
QT += network
QT += multimedia multimediawidgets


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


TARGET = SmartHomeSystem
TEMPLATE = app

M_src_path = src

CONFIG += c++11 console
CONFIG+="lang-en_GB lang-zh_CN"
CONFIG+=resources_big
SOURCES += \
        $${M_src_path}/main.cpp \
    src/modules/apiService/baiduspeech.cpp \
    src/modules/apiService/baiduspeechrecognizer.cpp \
    src/modules/apiService/chatgptapi.cpp \
    src/modules/audio/audiorecorder.cpp \
    src/modules/deviceMgnt/deviceapi.cpp \
    src/modules/deviceMgnt/tcphandle.cpp \
    src/modules/deviceMgnt/udpbroadcast.cpp \
    src/modules/deviceMgnt/udphandle.cpp \
    src/modules/global/mglobal.cpp \
    src/modules/global/networkservice.cpp \
    src/modules/global/protocolhandler.cpp \
    src/modules/global/terminalexec.cpp \
    src/modules/global/configmanager.cpp \
    src/modules/qmlConnect/connectcpp.cpp \
    src/modules/qmlConnect/qmlctrl.cpp \
    src/modules/sqlite/sqlitemgnt.cpp \
    src/modules/usrMgnt/user.cpp \
    src/modules/usrMgnt/userlogin.cpp \
    src/modules/usrMgnt/usermgnt.cpp \
    src/modules/deviceMgnt/devicemgnt.cpp \
    src/modules/deviceMgnt/device.cpp \
    src/modules/deviceMgnt/devicectrl.cpp  \
    src/modules/weather/weatherinfo.cpp \
    src/modules/wifiMgnt/wifimgnt.cpp



HEADERS += \
        $${M_src_path}/modules/keyborad/virtual_keyboard.h \
        src/modules/apiService/baiduspeech.h \
        src/modules/apiService/baiduspeechrecognizer.h \
        src/modules/apiService/chatgptapi.h \
        src/modules/audio/audiorecorder.h \
        src/modules/deviceMgnt/deviceapi.h \
        src/modules/deviceMgnt/tcphandle.h \
        src/modules/deviceMgnt/udpbroadcast.h \
        src/modules/deviceMgnt/udphandle.h \
        src/modules/global/init.h \
        src/modules/global/mglobal.h \
        src/modules/global/networkservice.h \
        src/modules/global/protocolhandler.h \
        src/modules/global/terminalexec.h \
        src/modules/global/configmanager.h \
        src/modules/qmlConnect/connectcpp.h \
        src/modules/qmlConnect/qmlctrl.h \
        src/modules/sqlite/sqlitemgnt.h \
        src/modules/usrMgnt/user.h \
        src/modules/usrMgnt/userlogin.h \
        src/modules/usrMgnt/usermgnt.h \
        src/modules/deviceMgnt/devicemgnt.h \
        src/modules/deviceMgnt/device.h \
        src/modules/deviceMgnt/devicectrl.h \
        src/modules/weather/weatherinfo.h \
        src/modules/wifiMgnt/wifimgnt.h


FORMS += \


RESOURCES += res/qml.qrc

RESOURCES += \
    $$files(qml/*)

RESOURCES += \
    res/resources.qrc
# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = qml/imports
QML_IMPORT_PATH += D:\Qt\5.15.2\mingw81_64\qml
# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
