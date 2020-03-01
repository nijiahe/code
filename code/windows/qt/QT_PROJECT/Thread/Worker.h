#ifndef WORKER_H
#define WORKER_H

#include <QObject>


class Worker : public QObject
{
    Q_OBJECT
public:

signals:

public slots:
    void dowork();
};

#endif // WORKER_H
