#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
#include <QTextBrowser>

class TcpServer : public QWidget
{
    Q_OBJECT
public:
    explicit TcpServer(QWidget *parent = 0);


    QTcpServer * _server;
    QVector<QTcpSocket *> _sockets;//Sockets数组
    QTextBrowser * _show;
signals:

public slots:
    void slotNewConnection();
    void slotReadyRead();
};

#endif // TCPSERVER_H
