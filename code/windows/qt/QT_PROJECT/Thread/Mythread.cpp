#include "Mythread.h"
#include <QDebug>

Mythread::Mythread(QObject *parent)
{

}

void Mythread::run()
{
    qDebug()<<"run";
}
