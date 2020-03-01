#include "MyWidget.h"
#include <QPainter>
#include <QPixmap>

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{

}

void MyWidget::paintEvent(QPaintEvent *)
{
    //如果Qpainter画的是窗口,每条指令都需要重新画一遍,用QPixmap包装绘画的操作让他一次性画完
    QPixmap pixmap(this->size());//此窗口的大小


    QPainter p(&pixmap);
    p.setRenderHint(QPainter::Antialiasing);//设置锯齿
    p.translate(100,100);//整体移动(调用这个函数之后,后面画的东西才会有效果)
    //旋转
    QTransform transform;
    transform.rotate(30);//以左上角为锚点
    //transform.scale(0.5,0.5);
    p.setTransform(transform,true);//bool值代表此次设置的transform是覆盖的形式还是叠加的形式给对象

    p.setPen(QPen(Qt::red,2,Qt::DashLine));//设置画笔款式
    p.setBrush(Qt::yellow);//设置背景
    p.setFont(QFont("aaa",40,700,true));//设置字体


    p.drawLine(QPoint(0,0),QPoint(55,55));
    p.drawEllipse(QPoint(300,300),50,20);//椭圆
    p.drawText(QPoint(100,50),"Hello World");
    //p.drawPixmap(QPoint(50,200),QPixmap("../莎雾.jpg"));

    p.drawRect(50,200,100,50);

    p.end();//画在pixmap上的画结束

    p.begin(this);//开始画在这个窗口上
    p.drawPixmap(0,0,pixmap);
}



