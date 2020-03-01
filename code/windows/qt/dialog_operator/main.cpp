#include "dialog.h"
#include <QApplication>
#include<windows.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w1;
    w1.show();
    Sleep(1000);
    w1(600,300);
    Sleep(1000);
    w1^(0);//传入任意整数
    Dialog w2;
    w2.show();
    w2(300,300);
    Sleep(1000);
    w2<<w1;
    return a.exec();
}
