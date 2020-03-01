#include <MyWidget.h>
#include <QtWidgets/QApplication>

int main(int argc,char * argv[])
{
    QApplication app(argc,argv);

    MyWidget w;
    w.setWindowTitle("Event");






    w.show();
    return app.exec();
}
