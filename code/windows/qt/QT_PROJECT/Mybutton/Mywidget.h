#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

class Mybutton;

class Mywidget : public QWidget
{
    Q_OBJECT
public:
    explicit Mywidget(QWidget *parent = 0);

    Mybutton * _button;

signals:

public slots:
};

#endif // MYWIDGET_H
