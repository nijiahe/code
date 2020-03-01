#include "dialog.h"
#include <QApplication>
#include<windows.h>
/*********************************
 * class changesize
{
public:
    Dialog* win;
public:
    Dialog* set(Dialog* it)
    {
        this->win=it;
        return this->win;
    }
    void setsize(int x,int y)
    {
        win->resize(x,y);
    }
    void smalltobig()
    {
        for(int i=0;i<600;i++)
        {
            Sleep(5);
            win->resize(i,i);
        }
    }
    void bintosmall()
    {
        for(int i=600;i>0;i--)
        {
            Sleep(5);
            win->resize(i,i);
        }
    }
};

int main01(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog* win1=new Dialog;
    Dialog* win2=new Dialog;
    changesize fun1;
    fun1.set(win1);
    fun1.setsize(300,300);
    changesize fun2;
    fun2.set(win2);
    fun2.setsize(500,500);
    win1->show();
    win2->show();
    fun1.smalltobig();
    fun1.bintosmall();
    fun2.smalltobig();
    fun2.bintosmall();
    return a.exec();
}*
************************************/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.show();
    w.move(0,0);
    for(int i=0;i<600;i++)
    {
        w++;
    }
    return a.exec();
}

