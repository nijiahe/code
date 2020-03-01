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

void Dialog::on_pushButton_clicked()
{
    QString str1=ui->lineEdit->text();
    QString str2=ui->lineEdit_2->text();
    double db1=str1.toDouble();
    double db2=str2.toDouble();
    QString str3;
    str3.setNum(db1+db2);
    ui->label->setText(str3);
}
