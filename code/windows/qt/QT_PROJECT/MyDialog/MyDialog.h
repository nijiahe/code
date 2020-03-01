#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>

//Dialog与Widget的区别:Dialog可以exev,即可以有个自己的消息循环
class MyDialog : public QDialog       
{
    Q_OBJECT
public:
    explicit MyDialog(QWidget * parent=0);


    QString _strfile;
signals:

public slots:
    void SlotButtonClick();
};

#endif // MYDIALOG_H
