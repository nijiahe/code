#include "Mythread.h"
#include "Worker.h"

#include <QCoreApplication>
#include <QTimer>
#include <QObject>


#include <QDebug>

int main(int argc,char * argv[])
{
   QCoreApplication app(argc,argv);

#if 0
   Mythread thread;
   thread.start();
#endif
   QThread thread;

   qDebug()<<"main thread is "<<QThread::currentThread();
   Worker worker;
   worker.moveToThread(&thread);
   thread.start();
   QTimer * timer = new QTimer;
   timer->setInterval(1000);
   timer->start();
   QObject::connect(timer,SIGNAL(timeout()),&worker,SLOT(dowork()));

    return app.exec();
}
