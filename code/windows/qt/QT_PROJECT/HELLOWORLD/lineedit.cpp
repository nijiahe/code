//应用程序抽象类
#include <QtWidgets/QApplication>
//窗口类
#include <QtWidgets/QtWidgets>

int main2(int argc,char * argv[])
{
    QApplication app(argc,argv);

    //构造一个窗口
    QWidget w;
    w.setWindowTitle("helloworld");

    QLineEdit lineedit;
    //s设置输入密码的样式
    //lineedit.setEchoMode(QLineEdit::Password);
    lineedit.text();//获得文字
    lineedit.setPlaceholderText("haha");

    QCompleter com(QStringList()<<"123"<<"234"<<"345");//提示
    com.setFilterMode(Qt::MatchContains);//设置提示的风格为包含
    lineedit.setCompleter(&com);

    //lineedit.setGeometry(w.width()/2,w.height()/2,lineedit.width(),lineedit.height());
    lineedit.setParent(&w);
    //显示窗口
    w.show();

    //exec中有一个消息循环
    return app.exec();
}
