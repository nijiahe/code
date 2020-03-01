#include "Mybutton.h"
#include "Mywidget.h"
#include <QtWidgets/QtWidgets>

int main(int argc,char * argv[])
{
    QApplication app(argc,argv);

    QWidget w;
    w.setWindowTitle("window");
    Mybutton button("button",&w);
    //SIGNAL和SLOT是两个字符串处理宏,辉自动获取前面传入参数的类,在调用前一个函数时自动调用后一个函数
    QObject::connect(&button,SIGNAL(clicked()),&button,SLOT(slotMybuttonClicked()));
    w.show();

    return app.exec();
}
