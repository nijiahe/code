#include "mainwindow.h"
#include<iostream>
#include <QApplication>
#include<QDebug>//不用windows控制台了，在qt的应用程序输出里输出
class mywindows
{
public:
    MainWindow* ptr;
    static int num;
public:
    mywindows()
    {
        qDebug()<<"create";
        ptr=new MainWindow;
        num++;
    }
    ~mywindows()
    {
        qDebug()<<"delete";
        delete ptr;
        ptr=NULL;
        num--;
    }
    static void run()//静态成员函数就算没有实例也能直接调用
    {
        system("calc");
    }
    void fun()//动态成员函数必须有实例然后才能通过实例的类成员方法调用
    {
        system("calc");
    }
};
int mywindows::num=0;
class onmywindows
{
public:
    mywindows &w;
public:onmywindows(mywindows m):w(m)
    {

    }
};

int main01(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //mywindows::fun();fun是一个动态类成员函数，不能直接通过类的作用域调用，必须通过实例调用
    mywindows *w=new mywindows;
    w->ptr->setWindowTitle("123");//修改对话框标题
    w->ptr->show();
    qDebug()<<mywindows::num;
    {
        mywindows *w=new mywindows;
        w->ptr->show();
        qDebug()<<mywindows::num;
    }
    {
        mywindows *w=new mywindows;
        w->ptr->show();
        qDebug()<<mywindows::num;
    }
    return a.exec();
}
/*class mymainwindows//Qmainwindow是MainWindow的公有继承，QmainWindow的拷贝函数是私有的
{
public:
    MainWindow &w;//类成员中有引用的对象在构造函数中就要初始化
public:
    mymainwindows(MainWindow m):w(m)//构造函数初始化表达方式
    {
        w.show();
    }
};
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow m;
    mymainwindows win(m);//QMainWindow的拷贝构造是私有的，这里调用的实质是QMainWindow的拷贝构造
    return a.exec();
}*/
class num
{
public:
    int &n;//类成员中有引用的对象在构造函数中就要初始化
public:
    num(int m):n(m)//构造函数初始化表达方式
    {

    }
};
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    num num1(3);
    qDebug()<<num1.n;
    return a.exec();
}
