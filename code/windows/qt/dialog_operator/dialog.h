#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}
class Dialog : public QDialog
{
    Q_OBJECT
private:
    int x;
    int y;
    int cx;
    int cy;
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
public:
    Dialog* operator ()(int x,int y);
    Dialog* operator ()(Dialog *it);
    Dialog* operator ()(Dialog &it);
    Dialog* operator +(Dialog *it);
    Dialog* operator +(Dialog &it);
    Dialog* operator -(Dialog *it);
    Dialog* operator -(Dialog &it);
    Dialog* operator *(int largertimes);
    Dialog* operator /(int smallertimes);
    Dialog* operator ^(int);
    Dialog* operator =(Dialog *it);
    Dialog* operator =(Dialog &it);
    bool operator >(Dialog &it);
    bool operator >(Dialog *it);
    bool operator <(Dialog &it);
    bool operator <(Dialog *it);
    Dialog* operator +=(Dialog *it);
    Dialog* operator +=(Dialog &it);
    Dialog* operator -=(Dialog *it);
    Dialog* operator -=(Dialog &it);
    Dialog* operator *=(int times);
    friend Dialog* operator <<(Dialog &the,Dialog &it);
    friend Dialog* operator >>(Dialog &the,Dialog &it);
    Dialog* operator ++();
    Dialog* operator --();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
