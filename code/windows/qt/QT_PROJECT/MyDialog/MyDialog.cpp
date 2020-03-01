#include "MyDialog.h"
#include <QPushButton>
#include <QDebug>
#include <QFileDialog>
#include <QColorDialog>
#include <QFontDialog>
#include <QMessageBox>

MyDialog::MyDialog(QWidget * parent):
    QDialog(parent)
{
    QPushButton * button = new QPushButton("click me",this);
    QObject::connect(button,SIGNAL(clicked()),this,SLOT(SlotButtonClick()));
}

void MyDialog::SlotButtonClick()
{
#if 0
    //模态对话框
    QDialog * dia = new QDialog;

    QPushButton * button = new QPushButton("accept",dia);
    QObject::connect(button,SIGNAL(clicked()),dia,SLOT(accept()));

    int ret = dia->exec();//这种方式显示的对话框是模态对话框,原理是截取代理所有原来对话框的事件
    //int ret = dia->show();//这种方式的对话框不会截取原来对话框的消息
    //exec显示 用accept和rejected关闭窗口
    //show显示 用close关闭窗口
    if(ret==QDialog::Accepted)//接受
    {
        qDebug()<<"accepted";
    }
    if(ret==QDialog::Rejected)//拒绝
    {
        qDebug()<<"Rejected";
    }
#endif
    //选择保存路径
    //QString strFileName = QFileDialog::getSaveFileName(NULL,"选择文件",_strfile,"Png (*.png *.jpg)");
    //选择文件路径
    //QString strFileName = QFileDialog::getOpenFileName(NULL,"选择文件",_strfile,"Png (*.png *.jpg)");
    //选择目录
    //QString strFileName = QFileDialog::getExistingDirectory();

    /*qDebug()<<strFileName;
    QFileInfo fileinfo(strFileName);
    _strfile =fileinfo.filePath();*/

    //选择颜色
    /*QColorDialog color;
    color.exec();
    QColor c = color.selectedColor();*/

    //选择字体
    /*QFontDialog fontdialog;
    fontdialog.exec();
    QFont font = fontdialog.selectedFont();*/

    //弹框
    QMessageBox::information(this,"title","inner...");
    //ret保存选择了哪个按键
    int ret = QMessageBox::question(this,"title","inner",QMessageBox::Yes|QMessageBox::No|QMessageBox::YesAll|QMessageBox::NoAll);


}


