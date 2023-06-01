#include "mglobal.h"
#include <QEventLoop>
#include <QTimer>
#include <QDir>

void Delay_MSec(unsigned int msec) {
  QEventLoop loop; // 定义一个新的事件循环
  QTimer::singleShot(
      msec, &loop, SLOT(quit())); // 创建单次定时器，槽函数为事件循环的退出函数
  loop.exec(); // 事件循环开始执行，程序会卡在这里，直到定时时间到，本循环被退出
}

void createOrClearFolder(QString folderPath) {
    QDir folder(folderPath);
    if (!folder.exists()) {
        folder.mkpath(".");
    } else {
        folder.setNameFilters(QStringList() << "*");
        folder.setFilter(QDir::Files);
        foreach(QString dirFile, folder.entryList()) {
            folder.remove(dirFile);
        }
    }
}