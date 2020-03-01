#include "Worker.h"
#include <QDebug>
#include <QThread>

void Worker::dowork()
{
    qDebug() << QThread::currentThread();
}
