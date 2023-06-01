#include <QApplication>
#include "main_window.h"
#include "virtual_keyboard.h"

QQuickWidget *v_keyboard = nullptr;

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
