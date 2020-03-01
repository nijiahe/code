#include "MyWidget.h"
#include <QtWidgets/QApplication>
#include <QDebug>
#include <QMouseEvent>

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{

}

bool MyWidget::event(QEvent * ev)
{
    /*
    switch (ev->type()) {
    case QEvent::MouseButtonPress:
        qDebug()<<"MouseButtonPress";
        break;
    default:
        break;
    }

    //类似cocos中的init 需要调用父类的方法



    */
    QWidget::event(ev);


    return true;
}
//重载了鼠标点击事件
void MyWidget::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button()==Qt::LeftButton)
    {
        QPoint point = ev->pos();
        qDebug()<<point;
    }
    if(ev->modifiers()==Qt::ControlModifier)//伴随键
    {
        qDebug()<<"ctrl";
    }

}
