#include "TcpServer.h"
#include <QHBoxLayout>
#include "ChooseInterface.h"

TcpServer::TcpServer(QWidget *parent) : QWidget(parent)
{
    _server = new QTcpServer;
    ChooseInterface dialog;
    int ret = dialog.exec();//exec结束了只是这个对话框没有消息循环了,并不是他从内存释放了
    if(ret ==QDialog::Rejected)
    {

        exit(0);
    }

    _server->listen(QHostAddress(dialog._ipstr),9988);
    QObject::connect(_server,SIGNAL(newConnection()),this,SLOT(slotNewConnection()));//有新连接时的槽函数
    _show = new QTextBrowser;

    QHBoxLayout * hbox = new QHBoxLayout(this);
    hbox->addWidget(_show);

    _show->append(dialog._ipstr);
}

void TcpServer::slotNewConnection()
{
    while(_server->hasPendingConnections())
    {
        _show->append("new connect...");
        _sockets.append(_server->nextPendingConnection()); //相当于c语言的accept,返回一个socket编号(即文件指针)
        QObject::connect(_sockets.last(),SIGNAL(readyRead()),this,SLOT(slotReadyRead()));//当有消息来时的槽函数
    }

}

void TcpServer::slotReadyRead()
{
    QTcpSocket * socket = dynamic_cast<QTcpSocket *>(sender());
    while(socket->bytesAvailable()>0)
    {
        QByteArray buf = socket->readAll();
        _show->append(buf);
    }
}

