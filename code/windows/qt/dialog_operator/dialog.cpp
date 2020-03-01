#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    x=y=cx=cy=0;
}

Dialog::~Dialog()
{
    delete ui;
}

Dialog* Dialog::operator ()(int x, int y)
{
    this->x=x;
    this->y=y;
    this->resize(this->x,this->y);
    return this;
}
Dialog* Dialog::operator ()(Dialog *it)
{
    this->x=it->x;
    this->y=it->y;
    resize(this->x,this->y);
    return this;
}

Dialog *Dialog::operator ()(Dialog &it)
{
    this->x=it.x;
    this->y=it.y;
    resize(this->x,this->y);
    return this;
}
Dialog* Dialog::operator +(Dialog *it)
{
    this->x+=it->x;
    this->y+=it->y;
    resize(this->x,this->y);
    return this;
}

Dialog *Dialog::operator +(Dialog &it)
{
    this->x+=it.x;
    this->y+=it.y;
    resize(this->x,this->y);
    return this;
}

Dialog* Dialog::operator -(Dialog *it)
{
    this->x=it->x;
    this->y-=it->y;
    resize(this->x,this->y);
    return this;
}

Dialog *Dialog::operator -(Dialog &it)
{
    this->x=it.x;
    this->y-=it.y;
    resize(this->x,this->y);
    return this;
}
Dialog* Dialog::operator *(int largertimes)
{
    this->x*=largertimes;
    this->y*=largertimes;
    resize(this->x,this->y);
    return this;
}
Dialog* Dialog::operator /(int smallertimes)
{
    this->x/=smallertimes;
    this->y/=smallertimes;
    resize(this->x,this->y);
    return this;
}

Dialog* Dialog::operator ^(int)
{
    this->x=this->x+this->y;
    this->y=this->x-this->y;
    this->x=this->x-this->y;
    resize(this->x,this->y);
    return this;
}

Dialog* Dialog::operator =(Dialog *it)
{
    this->x=it->x;
    this->y=it->y;
    resize(this->x,this->y);
    return this;
}

Dialog *Dialog::operator =(Dialog &it)
{
    this->x=it.x;
    this->y=it.y;
    resize(this->x,this->y);
    return this;
}

bool Dialog::operator >(Dialog &it)
{
    if(this->x>=it.x&&this->y>=it.y)
    {
        return 1;
    }
    return 0;
}

bool Dialog::operator >(Dialog *it)
{
    if(this->x>=it->x&&this->y>=it->y)
    {
        return 1;
    }
    return 0;
}

bool Dialog::operator <(Dialog &it)
{
    if(this->x<=it.x&&this->y>=it.y)
    {
        return 1;
    }
    return 0;
}

bool Dialog::operator <(Dialog *it)
{
    if(this->x<=it->x&&this->y>=it->y)
    {
        return 1;
    }
    return 0;
}

Dialog* Dialog::operator +=(Dialog *it)
{
    this->x+=it->x;
    this->y+=it->y;
    resize(this->x,this->y);
    return this;
}

Dialog *Dialog::operator +=(Dialog &it)
{
    this->x+=it.x;
    this->y+=it.y;
    resize(this->x,this->y);
    return this;
}
Dialog* Dialog::operator -=(Dialog *it)
{
    this->x-=it->x;
    this->y-=it->y;
    resize(this->x,this->y);
    return this;
}

Dialog *Dialog::operator -=(Dialog &it)
{
    this->x-=it.x;
    this->y-=it.y;
    resize(this->x,this->y);
    return this;
}

Dialog* Dialog::operator *=(int times)
{
    this->x*=times;
    this->y*=times;
    resize(this->x,this->y);
    return this;
}
Dialog* Dialog::operator ++()
{
    this->x++;
    this->y++;
    this->resize(this->x,this->y);
    return this;
}
Dialog* operator <<(Dialog &the,Dialog &it)
{
    the.x=it.x;
    the.y=it.y;
    the.resize(the.x,the.y);
    return &the;
}
Dialog* operator >>(Dialog &the,Dialog &it)
{
    it.x=the.x;
    it.y=the.y;
    it.resize(it.x,it.y);
    return &it;
}


