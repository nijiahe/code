#include "TcpClient.h"
#include <QHBoxLayout>


TcpClient::TcpClient(QWidget *parent) : QWidget(parent)
{
    _socket = new QTcpSocket(this);
    _lineEdit = new QLineEdit;

    _socket->connectToHost("192.168.91.1",9988);

    QHBoxLayout * lay = new QHBoxLayout(this);
    lay->addWidget(_lineEdit);

    _button = new QPushButton("发送");
    lay->addWidget(_button);
    QObject::connect(_button,SIGNAL(clicked()),this,SLOT(slotButtonClick()));//点击按钮时发送消息

    QObject::connect(_lineEdit,SIGNAL(returnPressed()),this,SLOT(slotButtonClick()));//注册在_lineEdit中按回车会发送的功能
}

void TcpClient::slotButtonClick()
{
    QString text = _lineEdit->text();//获取数据转换为QByteArray类型并发送
    if(text.isEmpty())
    {
        return;
    }
    _socket->write(text.toUtf8());
    _lineEdit->clear();
}
