#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

class Mythread : public QThread
{
    Q_OBJECT
public:
    explicit Mythread(QObject * parent=0);

    //run函数是线程开始的地方,需要重载
    void run();
};

#endif // MYTHREAD_H
