#include "main_window.h"
#include "ui_main_window.h"
#include "virtual_keyboard.h"

#include <QDesktopWidget>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lineEdit->installEventFilter(this);

    // 居中
    QDesktopWidget pDesk;
    this->setFixedSize(1024, 768);
    int shift_y = (pDesk.height() - this->height()) / 2;
    this->move((pDesk.width() - this->width()) / 2, shift_y);

    // 虚拟键盘
    v_keyboard = new QQuickWidget();
    v_keyboard->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowDoesNotAcceptFocus);
    v_keyboard->setResizeMode(QQuickWidget::SizeRootObjectToView);
    v_keyboard->setSource(QUrl("qrc:/virtual_keyboard.qml"));
    v_keyboard->setFixedSize(760, 264);
    v_keyboard->move((pDesk.width() - v_keyboard->width()) / 2,
                     pDesk.height() - shift_y - v_keyboard->height() - 10);
    v_keyboard->setAttribute(Qt::WA_AcceptTouchEvents);
    v_keyboard->setAttribute(Qt::WA_ShowWithoutActivating);
    v_keyboard->setFocusPolicy(Qt::NoFocus);
    v_keyboard->hide();
}

MainWindow::~MainWindow()
{    
    if(v_keyboard)
    {
        v_keyboard->close();
        delete v_keyboard;
    }
    delete ui;
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->lineEdit)
    {
        if (event->type()==QEvent::FocusIn)
        {
            v_keyboard->show();
        }
        else if (event->type()==QEvent::FocusOut)
        {
            v_keyboard->hide();
        }
    }

    return QMainWindow::eventFilter(watched, event);
}
