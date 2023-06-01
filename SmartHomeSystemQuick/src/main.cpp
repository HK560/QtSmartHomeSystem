#include <QApplication>
#include <QFontDatabase>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickView>
#include <QtGlobal>
#include <QTimer>
#include "modules/global/init.h"
#include "modules/global/configmanager.h"


#include "modules/keyborad/virtual_keyboard.h"
#include "modules/qmlConnect/qmlctrl.h"
#include "modules/sqlite/sqlitemgnt.h"
#include "modules/usrMgnt/usermgnt.h"
#include "modules/wifiMgnt/wifimgnt.h"
#include "modules/global/terminalexec.h"
#include "src/modules/global/configmanager.h"
#include "src/modules/global/init.h"
#include "src/modules/global/terminalexec.h"
#include "src/modules/wifiMgnt/wifimgnt.h"
#include "src/modules/qmlConnect/connectcpp.h"
#include "src/modules/deviceMgnt/udphandle.h"
#include <QMessageBox>
// #include <QApplicationAttribute>
QQuickWidget *v_keyboard = nullptr;

int main(int argc, char *argv[]) {

#ifdef Q_OS_WIN32
  outDebug << "*****Program running in Windows environment*****";
#endif
#ifdef Q_OS_LINUX
  outDebug << "*****Program running in Linux environment*****";
#endif
  qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
  qSetMessagePattern("[%{type}] %{time yyyy-MM-dd hh:mm:ss.zzz}  "
                     "%{file}:%{function}:%{line} %{message}");

  QFontDatabase::addApplicationFont(":/myyahei.ttf");

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
  // QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QCoreApplication::setAttribute(
      Qt::ApplicationAttribute::AA_ShareOpenGLContexts, true);

#endif

  QGuiApplication app(argc, argv);
  qmlRegisterType<ConnectCpp>("ConnectCpp",1,0,"ConnectCppObj");
  QQmlApplicationEngine engine;
  // app.setAttribute(Qt::ApplicationAttribute::AA_ShareOpenGLContexts, true);
  // my qml ctrl with c++
  QmlCtrl qctrl;
  qctrl.QmlCtrlInit();
//   TerminalExec terminal;

//~~~~~~~~~~~~~~~~~~TESTS~~~~~~~~~~~~~~~~
outDebug<<ConfigManager::getInstance().getValue(ConfigManager::WindowSize);
// UdpHandle udp_handle;
// udp_handle.init();
// udp_handle.startUdpBroadcast();
#ifdef Q_OS_WIN32
//   terminal.execute("cmd", QStringList()<<"/c"<<"dir");
#endif
// WifiMgnt wifiManager;

#ifdef Q_OS_LINUX
// wifiManager.getAllWifiConnectionsList();
// wifiManager.printWifiList();
  // qctrl.connectWifi("elbadaernU", "02316800");

#endif
  // add rootContext
  // USE "qmlCtrl" to connect to the c++ backend
  engine.rootContext()->setContextProperty("appDir", qApp->applicationDirPath());
  outInfo<<"Now program path is "<<qApp->applicationDirPath();
  engine.rootContext()->setContextProperty("qmlCtrl", &qctrl);

  engine.addImportPath("qrc:/qml/imports");

  const QUrl url(QStringLiteral("qrc:/qml/content/App.qml"));

  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreated, &app,
      [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
          QCoreApplication::exit(-1);
      },
      Qt::QueuedConnection);


    QObject::disconnect(&engine,&QQmlApplicationEngine::quit,nullptr,nullptr);
    QObject::disconnect(&engine,&QQmlApplicationEngine::exit,nullptr,nullptr);
    QObject::connect(&engine,&QQmlApplicationEngine::quit,[]{
        qDebug()<<"quit";
        if(QMessageBox::warning(nullptr,"提示","确认退出？",
                             QMessageBox::Ok|QMessageBox::Cancel)==QMessageBox::Ok)
            qApp->quit();
    });
    QObject::connect(&engine,&QQmlApplicationEngine::exit,[](int code){
        qDebug()<<"exit"<<code;
        if(QMessageBox::warning(nullptr,"提示","确认退出？",
                             QMessageBox::Ok|QMessageBox::Cancel)==QMessageBox::Ok)
            qApp->quit();
    });

  engine.load(url);

#if (0)
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    QQuickView view;
//        view.engine()->addImportPath("qrc:/qml/imports");
//        view.setSource(QUrl("qrc:/qml/content/Screen01.ui.qml"));
//        if (!view.errors().isEmpty())
//            return -1;
//        view.show();
//        view.engine();
#endif
  // UserMgnt tst;
  // SqliteMgnt sql;
  // sql.initDb();
  // sql.createUserTable();
  return app.exec();
}
