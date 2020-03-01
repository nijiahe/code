//应用程序抽象类
#include <QtWidgets/QApplication>
//窗口类
#include <QtWidgets/QtWidgets>

int main3(int argc,char * argv[])
{
    QApplication app(argc,argv);

    //构造一个窗口
    QWidget w;
    w.setWindowTitle("helloworld");
    QPushButton button;
    button.setText("close");
    button.setParent(&w);
    //button.setGeometry();

    QLineEdit le;
    le.setParent(&w);

    //QVBoxLayout
    QHBoxLayout hbox;
    hbox.addStretch(1);//弹簧,参数为比重
    hbox.addWidget(&button);
    hbox.addSpacing(50);//间距
    hbox.addWidget(&le);
    hbox.addStretch(1);

    w.setLayout(&hbox);

    w.setGeometry(200,200,500,500);
    w.show();
    //exec中有一个消息循环
    return app.exec();
}

