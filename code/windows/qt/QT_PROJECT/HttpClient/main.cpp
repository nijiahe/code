#include <QCoreApplication>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QByteArray>

#include <QObject>

int main(int argc,char * argv[])
{
    QCoreApplication app(argc,argv);

    QNetworkAccessManager * manager = new QNetworkAccessManager;

    QNetworkRequest req;
    req.setUrl(QUrl("http://118.25.62.177/"));
    manager->get(req);
    QObject::connect(manager,&QNetworkAccessManager::finished,[](QNetworkReply *reply){
        //if error
        if(reply->error()!=QNetworkReply::NoError)
        {
            qDebug()<<reply->errorString();
            return;
        }
        else
        {
            QByteArray buf = reply->readAll();
            qDebug()<<buf;
        }
    });

    return app.exec();
}
