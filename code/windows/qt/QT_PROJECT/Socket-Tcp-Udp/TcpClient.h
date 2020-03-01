#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QLineEdit>
#include <QPushButton>

class TcpClient : public QWidget
{
    Q_OBJECT
public:
    explicit TcpClient(QWidget *parent = 0);


    QTcpSocket * _socket;
    QLineEdit * _lineEdit;
    QPushButton * _button;
signals:

public slots:
    void slotButtonClick();
};

#endif // TCPCLIENT_H
