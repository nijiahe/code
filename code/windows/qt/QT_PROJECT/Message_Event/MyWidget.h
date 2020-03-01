#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

//QT的消息机制:所有的消息传到窗口类的event中,然后由窗口类的event调用其它的窗口类函数来处理不同的事件,也可以用event函数来截断消息

//returnPressed指按回车键触发的信号
class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = 0);

    bool event(QEvent *) override;//重载的函数,所有的事件都经过这个函数

    void mousePressEvent(QMouseEvent * ev) override;//专门用来处理鼠标事件的虚函数
    /*void mouseReleaseEvent(QMouseEvent * ev);
    void mouseMoveEvent(QMouseEvent * ev);
    void mouseDoubleClickEvent(QMouseEvent * ev);

    void keyPressEvent(QKeyEvent * ev);
    void keyReleaseEvent(QKeyEvent * ev);

    void showEvent();
    void hideEvent(QHideEvent *);
    void closeEvent();
    void paintEvent();//重绘消息*/

    /*消息机制函数
    bool eventFilter(QObject *, QEvent *);
    */

signals:

public slots:
};

#endif // MYWIDGET_H
