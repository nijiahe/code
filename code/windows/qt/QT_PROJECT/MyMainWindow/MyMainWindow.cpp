#include "MyMainWindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QLabel>
#include <QPainter>
#include <QDialog>
#include <QCursor>//获取鼠标相关信息
#include <QMouseEvent>
//菜单栏头文件
#include <QMenu>
#include <QMenuBar>
#include <QAction>
//工具栏头文件
#include <QToolBar>
//状态栏头文件
#include <QStatusBar>
//托盘头文件
#include <QSystemTrayIcon>

MyMainWindow::MyMainWindow(QWidget *parent) : QMainWindow(parent)
{
    //添加菜单栏
    QMenuBar * menubar = menuBar();
    QMenu * menu = menubar->addMenu("文件");
    _menu = menu;
    QAction * openaction = menu->addAction("打开",this,SLOT(slotOpenFile()),QKeySequence::Open);//这个宏是QT默认设置好的一些快捷键,根据不同平台有不同快捷方式
    QAction * saveaction = menu->addAction("保存",this,SLOT(slotOpenFile()),QKeySequence::Save);
    QAction * closeaction = menu->addAction("关闭",this,SLOT(close()),QKeySequence::Close);

    //添加工具栏
    QToolBar * toolbar = this->addToolBar("工具栏");
    toolbar->addAction(openaction);
    toolbar->addAction(saveaction);
    toolbar->addAction(closeaction);

    //添加下方状态栏
    QStatusBar * statusbar = this->statusBar();
    QLabel * label = new QLabel("状态");
    statusbar->addWidget(label);
    label->setText("<font size=3>状态:正常</font>");

    //设置空白区域归_view
    _view = new QWidget;
    //这个函数的传入参数为QWidget,而QPainter如果设置的是为QWidget绘画,那只能在QWidget的paintEvent中调用QPainter
    this->setCentralWidget(_view);


    //托盘
    _icon = new QSystemTrayIcon;
    _icon->setIcon(QIcon("../favicon.ico"));
    _icon->setToolTip("jingdong");
    _icon->show();
    _icon->setContextMenu(_menu);//右键触发

    QObject::connect(_icon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(slotactivated(QSystemTrayIcon::ActivationReason)));
}

void MyMainWindow::paintEvent(QPaintEvent *)
{
    //此时原点仍然在原来的地方,即菜单栏和工具栏将原点覆盖了
    /*QPainter p(_view);
    p.drawLine(QPoint(0,0),QPoint(100,100));*/
}

void MyMainWindow::mousePressEvent(QMouseEvent * ev)
{
    if(ev->button()==Qt::RightButton)
    {
        _menu->exec(QCursor::pos());
    }
}

void MyMainWindow::slotactivated(QSystemTrayIcon::ActivationReason reason)
{
    //如果行为原因是点击
    if(reason==QSystemTrayIcon::Trigger)
    {
        if(this->isHidden())
        {
            this->show();
        }
        else
        {
            this->hide();
        }
    }
}

void MyMainWindow::slotOpenFile()
{
    QString strFile = QFileDialog::getOpenFileName();
    qDebug()<<strFile;
}

