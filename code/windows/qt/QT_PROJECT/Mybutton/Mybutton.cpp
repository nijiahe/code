#include "Mybutton.h"
#include <QPainter>
#include <QDebug>

Mybutton::Mybutton(QWidget *parent) : QWidget(parent),_rect(0,0,100,30)
{
    this->setGeometry(_rect);
}

Mybutton::Mybutton(const QString &text, QWidget *parent): QWidget(parent),_text(text),_rect(0,0,100,30)
{

}

void Mybutton::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    if(_IsPressed)
    {
        p.setBrush(Qt::darkGray);
    }
    else
    {
        p.setBrush(Qt::yellow);
    }
    p.drawRect(_rect);
    p.drawText(_rect,_text,QTextOption(Qt::AlignCenter));//画文字 在_rect内 居中对齐
    this->setGeometry(_rect);
}

void Mybutton::mousePressEvent(QMouseEvent *)
{
    _IsPressed=true;
    update();
}
//mouseRelease事件:如果点下时在这个里面,则不管在哪里松开都会触发这个函数
void Mybutton::mouseReleaseEvent(QMouseEvent *)
{
    _IsPressed=false;
    update();
    //当鼠标松开后发出clicked信号
    emit clicked();
    qDebug()<<"mouse release";
}

void Mybutton::slotMybuttonClicked()
{
    qDebug()<<"Mybutton slot clicked";
}
