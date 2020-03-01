#include "Mywidget.h"
#include <QtWidgets/QtWidgets>

int main(int argc,char * argv[])
{
    QApplication app(argc,argv);
    Mywidget w;

    w.show();

    return app.exec();
}
