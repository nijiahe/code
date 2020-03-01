#include "ChooseInterface.h"
#include <QNetworkInterface>
#include <QHBoxLayout>

ChooseInterface::ChooseInterface(QWidget *parent) : QDialog(parent)
{
    _combobox = new QComboBox;

    QHBoxLayout * lay = new QHBoxLayout(this);
    lay->addWidget(_combobox);

    /*得到所有的ip地址*/
    QList<QHostAddress> addrList = QNetworkInterface::allAddresses();//返回这个机器所有的IP地址
#if 0
    QList<QNetworkInterface> interfaceList = QNetworkInterface::allInterfaces();//返回的是网口
    interfaceList.at(0).addressEntries()；//入口地址
#endif

    foreach (QHostAddress addr, addrList) {
        quint32 ipaddr = addr.toIPv4Address();
        if(ipaddr == 0)
        {
            continue;
        }
        _combobox->addItem(QHostAddress(ipaddr).toString());
    }

    _button = new QPushButton("确定");
    QObject::connect(_button,SIGNAL(clicked()),this,SLOT(slotButtonClieked()));
    lay->addWidget(_button);
}

void ChooseInterface::slotButtonClieked()
{
    _ipstr = _combobox->currentText();
    this->accept();
}




