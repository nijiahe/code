#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)//构造函数
{
    hlayout1 = new QHBoxLayout(this);//建立一个横向布局，参数代表在这个界面里
    pushButton1 = new QPushButton(this);//建立一个按钮，参数代表这个按钮是在这个界面上的
    lable1 = new QLabel(this);
    lineedit1 = new QLineEdit(this);//建立一个输入空间，参数代表是在这个界面
    hlayout1->addWidget(lineedit1);//输入框
    hlayout1->addWidget(lable1);//输出框
    hlayout1->addWidget(pushButton1);//按钮
    pushButton1->setText("确定");

    connect(pushButton1,SIGNAL(clicked()),this,SLOT(on_clicked()));
            //按钮1   事件(单击)  事件在这个界面发生   执行(on_clicked)
            //单机了按钮1调用on_clicked()这个函数
}

Widget::~Widget()//析构函数
{

}

void Widget::on_clicked()
{
       QString str = lineedit1->text();
       lable1->setText(str);
}
