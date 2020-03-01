#include "Mywidget.h"
#include <QtWidgets/QtWidgets>
#include <QPainter>

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{

}
//鼠标按下时要新建一条线然后追加进数组
void MyWidget::mousePressEvent(QMouseEvent *ev)
{
    QVector<QPoint> line;
    lines.append(line);
    line.append(ev->pos());
    update();
}

void MyWidget::mouseReleaseEvent(QMouseEvent *ev)
{
    QVector<QPoint>& line;
    if(lines.length()!=0)
    {
        line = lines.last();
    }

    line.append(ev->pos());
}

void MyWidget::mouseMoveEvent(QMouseEvent *ev)
{
    QVector<QPoint>& line;
    if(lines.length()!=0)
    {
        line = lines.last();
    }
    line.append(ev->pos());
    update();
}
//每次update调用这个函数来重绘,
void MyWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    for(int i=0;i<lines.length();i++)
    {
        const QVector<QPoint>& line=lines.at(i);
        for(int j=0;j<line.length()-1;j++)
        {
            p.drawLine(line.at(j),line.at(j+1));
        }
    }
}
