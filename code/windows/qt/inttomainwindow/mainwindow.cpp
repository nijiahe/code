#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    x=y=300;
    this->resize(x,y);
    std::cout<<"creat"<<std::endl;
}
MainWindow::MainWindow(int num)
{
    this->x=num;
    this->y=num;
    resize(this->x,this->y);
    std::cout<<"creat"<<std::endl;
}
MainWindow::MainWindow(const MainWindow &it)
{//拷贝构造也会自动创建一个对象，但不是调用构造函数构造的
    this->ui=it.ui;
    this->x=it.x;
    this->y=it.y;
    resize(this->x,this->y);
    std::cout<<this<<std::endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}
