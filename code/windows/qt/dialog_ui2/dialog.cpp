#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->x=0;
    this->y=0;
    QString str1,str2;
    str1.setNum(this->x);
    str2.setNum(this->y);
    ui->lineEdit->setText(str1);
    ui->lineEdit_2->setText(str2);
}

Dialog::~Dialog()
{
    delete ui;
}
