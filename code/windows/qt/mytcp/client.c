#include <stdio.h>
#include<pthread.h>
#include<signal.h>
#include<string.h>
#include<stdlib.h>
#include<winsock2.h>
#include <WS2tcpip.h>
#include<string.h>

#include"wrap.h"

#define PORT 80
#define TEXTSIZE 128
#define MYIP "118.25.62.177"

int main()
{
    DWORD ver;//unsigned short
    WSADATA wsaData;
    //WSAStartup中的两个参数
    ver = MAKEWORD(1,1);//用socket版本1.1
    WSAStartup(ver,&wsaData);

    SOCKET sockfd=Socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in serveraddr;
    memset(&serveraddr,0,sizeof(serveraddr));
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_addr.s_addr=inet_addr(MYIP);
    serveraddr.sin_port=htons(PORT);

    Connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));

    char TEXT[TEXTSIZE];
    while(1)
    {
        fgets(TEXT,TEXTSIZE,stdin);
        send(sockfd,TEXT,strlen(TEXT),0);
        if(strcmp(TEXT,"quit")==0)
        {
            break;
        }
    }
    WSACleanup();//释放初始化时调用的资源
    Close(sockfd);
    return 0;

}

