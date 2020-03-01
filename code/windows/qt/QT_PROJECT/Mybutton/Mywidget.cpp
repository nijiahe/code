#include "Mywidget.h"
#include "Mybutton.h"

Mywidget::Mywidget(QWidget *parent) : QWidget(parent)
{
    _button = new Mybutton("button",this);
}


