#include<stdio.h>
#include<string.h>


#ifdef mylinux//linux系统define mylinux
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define closesocket close
#define SOCKET int

#else//windows系统
#include<winsock2.h>
#define socklen_t int
#endif

int socket_send(const char *ip)
{
#ifndef mylinux
    DWORD ver;//unsigned short
    WSADATA wsaData;
    //WSAStartup中的两个参数
     ver = MAKEWORD(1,1);//用socket版本1.1
     WSAStartup(ver,&wsaData);
     //初始化
#endif


//SOCKET：指向无符号的整数的指针
     //socket()函数用于根据指定的地址族、数据类型和协议来分配一个套接口的描述字及其所用的资源。
     SOCKET st = socket(AF_INET,SOCK_DGRAM,0);//使用TPC/IP协议,使用UDP协议，一般默认0；
     struct sockaddr_in addr;
     /*struct sockaddr_in {
     short	sin_family;//结构指向什么类型的地址
     u_short	sin_port;//端口
     struct in_addr	sin_addr;//地址中的数字内容的指针
     char	sin_zero[8];
 };*/
     memset(&addr,0,sizeof(addr));//初始化结构体
     addr.sin_family=AF_INET;//TCP/IP类型地址
     addr.sin_port=htons(8080);//将大于一个字节的数转化为网络能够识别的数htonl（long）
     addr.sin_addr.s_addr=inet_addr(ip);//inet_addr的作用：将ip地址转化为一个整数，一个ip地址四个字节
     //127.0.0.1代表自己 sin_addr里面的s.addr存储地址数据
     char buf[1024]={0};
     size_t rc = 0;
     while(1)
     {
         memset(buf,0,sizeof(buf));
        fgets(buf,sizeof(buf),stdin);
        if(buf[0]=='0')
            break;
        rc = sendto(st,buf,strlen(buf),0,(struct sockaddr *)&addr,sizeof(addr));
        //存放通信通道类似管道，发送的信息，信息的长度，优先级，(存放协议类型，端口，ip地址的结构体)，结构体的大小
     }
     closesocket(st);
#ifndef mylinux
     WSACleanup();//释放初始化时调用的资源
#endif
     return rc;

}

int socket_rec()
{
#ifndef mylinux
    DWORD ver;//unsigned short
    WSADATA wsaData;
    //WSAStartup中的两个参数
     ver = MAKEWORD(1,1);//用socket版本1.1
     WSAStartup(ver,&wsaData);
     //初始化
#endif


//SOCKET：指向无符号的整数的指针
     //socket()函数用于根据指定的地址族、数据类型和协议来分配一个套接口的描述字及其所用的资源。
     SOCKET st = socket(AF_INET,SOCK_DGRAM,0);//使用TPC/IP协议,使用UDP协议，一般默认0；
     struct sockaddr_in addr;
     /*struct sockaddr_in {
     short	sin_family;//结构指向什么类型的地址
     u_short	sin_port;//端口
     struct in_addr	sin_addr;//地址中的数字内容的指针
     char	sin_zero[8];
 };*/
     //memset(&addr,0,sizeof(addr));初始化结构体
     addr.sin_family=AF_INET;//TCP/IP类型地址
     addr.sin_port=htons(8080);//将大于一个字节的数转化为网络能够识别的数htonl（long）
     addr.sin_addr.s_addr=htonl(INADDR_ANY);//表示接收方的任意ip
     size_t rc=0;
     if(bind(st,(struct sockaddr *)&addr,sizeof(addr)) == -1)
         //将端口号与程序绑定，接收方必须
     {
         printf("端口已被占用\n");
         return 0;
     }
     else
     {
         char buf[1024]={0};
         struct sockaddr_in senderaddr;//用于存放发送方的ip地址
         memset(&senderaddr,0,sizeof(senderaddr));
         socklen_t len=sizeof(senderaddr);
         while(1)
            {
             memset(buf,0,sizeof(buf));
             rc = recvfrom(st,buf,sizeof(buf),0,(struct sockaddr *)&addr,&len);
             printf("%s:%s\n",inet_ntoa(addr.sin_addr),buf);
            //存放通信通道类似管道，接收的信息，信息的长度，优先级，（存放协议类型，端口，ip地址的结构体），结构体的大小
            //inet_ntoa(addr.sin_addr)将其中存放的ip地址信息转化为字符串
            }
     }

     closesocket(st);
#ifndef mylinux
     WSACleanup();//释放初始化时调用的资源
#endif
     return rc;

}

