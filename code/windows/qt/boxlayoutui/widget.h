#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QPushButton>//存放控制按钮部件方法的头文件
#include<QHBoxLayout>//界面横式布局头文件
#include<QVBoxLayout>//界面纵式布局头文件
#include<QGridLayout>//界面格子式布局头文件
#include<QLineEdit>//界面输入控件头文件
#include<QLabel>//界面输出头文件


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
private:
    QPushButton *pushButton1;
    QHBoxLayout *hlayout1;
    QLineEdit *lineedit1;
    QLabel *lable1;
private slots://事件函数定义后面需加slots
    void on_clicked();


};

#endif // WIDGET_H
