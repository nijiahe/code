#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<iostream>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    MainWindow(int num);
    MainWindow(const MainWindow &it);
    ~MainWindow();
private:
    int x;
    int y;
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
