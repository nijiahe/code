//窗口
#include <QtWidgets/QtWidgets>
//应用程序
#include <QtWidgets/QApplication>

int main4(int argc,char * argv[])
{
    QApplication app(argc,argv);

    QWidget w;
    w.setWindowTitle("TITLE");
    //w.setFixedSize(500,500);

    QPushButton button1,button2,button3;
    button1.setText("按钮1");
    button1.setParent(&w);
    button2.setText("按钮2");
    button2.setParent(&w);
    button3.setText("按钮3");
    button3.setParent(&w);

    QLineEdit le1,le2;
    le1.setParent(&w);
    le2.setParent(&w);

    QGridLayout glay;
    glay.addWidget(&button1,1,1);
    glay.addWidget(&button2,1,2);
    glay.addWidget(&le1,2,1);
    glay.addWidget(&le2,2,2);
    glay.addWidget(&button3,3,1,1,2);//合并单元格,后面两个参数代表合并几行几列
    glay.setColumnStretch(0,1);
    glay.setColumnStretch(3,1);


    glay.setRowStretch(0,1);
    glay.setRowStretch(5,1);

    w.setLayout(&glay);

    w.show();
    return app.exec();
}
