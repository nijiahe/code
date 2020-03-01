#include "MyMainWindow.h"
#include <QtWidgets/QtWidgets>

int main(int argc,char * argv[])
{
    QApplication app(argc,argv);
    MyMainWindow window;
    window.show();

    return app.exec();
}
