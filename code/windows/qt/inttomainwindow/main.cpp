#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(600);
    std::cout<<&w<<std::endl;
    w.show();
    MainWindow w2(w);
    std::cout<<&w2<<std::endl;
    w2.show();
    return a.exec();
}
