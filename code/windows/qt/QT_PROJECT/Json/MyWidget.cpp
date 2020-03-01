#include "MyWidget.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QCryptographicHash>
#include <QDebug>

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{
    QByteArray md5 = QCryptographicHash::hash(QByteArray("123456"),QCryptographicHash::Md5);


    QJsonObject obj;
    obj.insert("username",QString("nijiahe"));
    obj.insert("password",QString(md5.toHex()));
    obj.insert("age",19);
    obj.insert("length",12.5);

    QJsonDocument doc(obj);
    QByteArray json = doc.toJson(QJsonDocument::Compact);
    qDebug()<<json;

    QJsonDocument recdoc = QJsonDocument::fromJson(json);
    QJsonObject recobj = recdoc.object();
    qDebug()<<recobj.value("username").toString();
    qDebug()<<recobj.value("password").toString();
    qDebug()<<recobj.value("age").toInt();
    qDebug()<<recobj.value("length").toDouble();

}
