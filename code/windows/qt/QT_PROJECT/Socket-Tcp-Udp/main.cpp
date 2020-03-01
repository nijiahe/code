#include "TcpServer.h"
#include "TcpClient.h"
#include "Udp1.h"
#include "Udp2.h"
#include <QApplication>


int main(int argc,char * argv[])
{
    QApplication app(argc,argv);
#if 0
    TcpServer server;server.setWindowTitle("server");server.show();
    TcpClient client;client.setWindowTitle("client");client.show();
#endif
    Udp1 udp1;udp1.setWindowTitle("udp1");udp1.show();
    Udp2 udp2;udp2.setWindowTitle("udp2");udp2.show();

    return app.exec();
}
