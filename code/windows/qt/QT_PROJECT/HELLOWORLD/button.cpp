//应用程序抽象类
#include <QtWidgets/QApplication>
//窗口类
#include <QtWidgets/QtWidgets>

int main1(int argc,char * argv[])
{
    QApplication app(argc,argv);

    //构造一个窗口
    QWidget w;
    w.setWindowTitle("helloworld");
    //添加一个按钮,任何控件都是一个窗口
    QPushButton button;
    button.setText("close");
    //父亲影响显示和逻辑上的关系
    button.setParent(&w);
    //button.setDefault(true);//setDefault可以让按钮能用回车键触发
    //显示窗口
    w.show();

    //注册一下button的点击响应,点击关闭,前两个称为信号,后两个成为槽
    QObject::connect(&button,SIGNAL(clicked()),&w,SLOT(close()));


    w.update();

    //exec中有一个消息循环
    return app.exec();
}
