#include "MyWidget.h"
#include <QtWidgets/QtWidgets>

int main(int argc,char * argv[])
{
    QApplication app(argc,argv);
    MyWidget w;
    w.show();


    return app.exec();
}
