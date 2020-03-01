#ifndef DIALOG_H
#define DIALOG_H
#include<QString>
#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
public:
    int x;
    int y;
    int cx;
    int cy;
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
/*******************************************
 * void operator ++(int)用来表示i++类型的调用;*
 * void operator ++()用来表示++i类型的调用;   *
 * *****************************************/
public:
    void operator ++(int)
    {
        this->cx++;
        this->cy++;
        this->move(this->cx,this->cy);
    }
private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
