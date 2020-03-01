#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>

class QWidget;
class QSystemTrayIcon;

class MyMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MyMainWindow(QWidget *parent = 0);

    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);



    //这个窗口用来设置空白区域,专门用来做空白区域的控件,空白区域指不被工具栏菜单栏等占用的区域
    QWidget * _view;
    QMenu * _menu;
    QSystemTrayIcon * _icon;
signals:

public slots:
    void slotOpenFile();
    void slotactivated(QSystemTrayIcon::ActivationReason);
};

#endif // MYMAINWINDOW_H
