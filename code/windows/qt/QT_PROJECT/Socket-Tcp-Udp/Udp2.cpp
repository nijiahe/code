#include "Udp2.h"
#include <QUdpSocket>
#include <QHBoxLayout>
#include <QTimer>
#include <QDateTime>
#include <QTextBrowser>

Udp2::Udp2(QWidget *parent) : QWidget(parent)
{
    _udp = new QUdpSocket;
    _udp->bind(QHostAddress::AnyIPv4,10002);

    QObject::connect(_udp,SIGNAL(readyRead()),this,SLOT(slotReadyRead()));

    _show = new QTextBrowser;

    QHBoxLayout * lay = new QHBoxLayout(this);
    lay->addWidget(_show);

    //每隔一段时间传送一段字符串
    QTimer * timer = new QTimer;
    timer->setInterval(1000);//每隔1秒
    timer->start();
    QObject::connect(timer,&QTimer::timeout,[&](){
        quint64 timesamp = QDateTime::currentMSecsSinceEpoch();//获得从1970年计算机刚出的那时候到现在的时间
        QString str = QString::number(timesamp);
        _udp->writeDatagram(str.toUtf8(),QHostAddress("127.0.0.1"),10001);
    });

    _udp->joinMulticastGroup(QHostAddress("224.0.0.131"));//加入这个多播地址,要加入IPV4的多播地址,bind时的地址也要是IPV4的
}


void Udp2::slotReadyRead()
{
    while(_udp->hasPendingDatagrams())//有数据传入时
    {
        quint32 datagramSize = _udp->pendingDatagramSize();//数据大小
        QByteArray buf(datagramSize,0);
        _udp->readDatagram(buf.data(),buf.size());
        _show->append(buf);
    }
}
