#include "mainwindow.h"
#include <QApplication>
class mywindow1
{
public:
    MainWindow **pA;//p指向的是一个MainWindow类型的指针
    MainWindow *(*p)[5];//指向了一个存放了5个MainWindow*数组的指针
    mywindow1()
    {
        pA=new MainWindow* [20];
        p=(MainWindow *(*)[5]) pA;
        for(int i=0;i<5;i++)
        {
            for(int j=0;j<4;j++)
            {
                p[i][j]=new MainWindow;
                p[i][j]->move(130*i,130*j);
                p[i][j]->show();
            }
        }
    }
    ~mywindow1()
    {
        for(int i=0;i<5;i++)
        {
            for(int j=0;j<4;j++)
            {
                delete p[i][j];
            }
        }
       delete []pA;
    }
};
class mywindow2
{
public:
    MainWindow *(*pA)[20];//p指向的是一个存放了20个Mainwindow*数组的指针
    mywindow2()
    {
        pA=(MainWindow *(*)[20])new MainWindow* [20];
        for(int i=0;i<5;i++)
        {
            for(int j=0;j<4;j++)
            {
                pA[i][j]=new MainWindow;
                pA[i][j]->move(130*i,130*j);
                pA[i][j]->show();
            }
        }
    }
    ~mywindow2()
    {
        for(int i=0;i<5;i++)
        {
            for(int j=0;j<4;j++)
            {
                delete pA[i][j];
            }
        }
       delete []pA;
    }
    MainWindow* operator [](int index)
    {
        return *pA[index];
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mywindow2 win2;
    win2[1]->hide();

    return a.exec();
}
