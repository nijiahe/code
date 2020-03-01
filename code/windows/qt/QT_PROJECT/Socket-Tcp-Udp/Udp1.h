#ifndef UDP1_H
#define UDP1_H

#include <QWidget>
#include <QTextBrowser>


class QUdpSocket;

class Udp1 : public QWidget
{
    Q_OBJECT
public:
    explicit Udp1(QWidget *parent = 0);


    QUdpSocket * _udp;
    QTextBrowser * _show;
signals:

public slots:
    void slotReadyRead();
};

#endif // UDP1_H
