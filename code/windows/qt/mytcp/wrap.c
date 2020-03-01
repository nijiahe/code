#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<winsock2.h>
#include <WS2tcpip.h>

#define socklen_t int

void my_err(const char* str)
{
    perror(str);
    exit(1);
}

SOCKET Accept(SOCKET sockfd,struct sockaddr* addr,socklen_t* addrlen)
{
   SOCKET n;
again:
   if((n=accept(sockfd,addr,addrlen))==INVALID_SOCKET)//接收客户端连接请求
   {
       if(errno==ECONNABORTED||errno==EINTR)//如果错误类型为重传一定次数失败或者被信号打断去执行信号处理函数
       {
        goto again;//重新尝试
       }
       else
       {
            my_err("accept");
       }
       return n;
   }
   return -1;
}

void Bind(SOCKET sockfd,const struct sockaddr* addr,socklen_t addrlen)
{
    if(bind(sockfd,addr,addrlen)==-1)
    {
        my_err("bind");
    }
}

void Connect(SOCKET sockfd,const struct sockaddr* addr,socklen_t addrlen)
{
    int num;
    if((num=connect(sockfd,addr,addrlen))==-1)
    {
        printf("errno=%d\n",errno);
        printf("num = %d\n",num);
        my_err("conncet");
    }
}

void Listen(SOCKET sockfd,int backlog)
{
    if(listen(sockfd,backlog)==-1)
    {
        my_err("listen");
    }
}

SOCKET Socket(int domain,int type,int protocol)
{
    SOCKET n=socket(domain,type,protocol);
    return n;
}

/*ssize_t Read(int fd,void* buf,size_t count)
{
    ssize_t n;
again:
    if((n=read(fd,buf,count))==-1)//如果=-1代表发生错误
    {
    if(errno=EINTR)
    {
        goto again;
    }
    else
    {
        return -1;
    }
    }
    return n;
}

ssize_t Write(int fd,void* buf,size_t count)
{
    ssize_t n;
again:
    if((n=write(fd,buf,count))==-1)//如果=-1代表发生错误
    {
    if(errno=EINTR)
    {
        goto again;
    }
    else
    {
        return -1;
    }
    }
    return n;
}*/

void Close(int fd)
{
    if(closesocket(fd)==-1)
    {
        my_err("close");
    }
}

/*
ssize_t Readn(int fd,void* vptr,size_t n)//读一直到文件末尾或者读到设置数量
{
    size_t nleft=n;//未读的数量
    char* ptr=vptr;//当前读到的指针
    size_t nread;//每次读到的量

    while(nleft>0)
    {
    if((nread=read(fd,ptr,nleft))<0)
    {
        if(errno==EINTR)//如果errno=EINTR(被信号中断去执行信号处理函数)
        {
        nread=0;
        }
        else//其他错误
        {
        return -1;
        }
    }
    else if(nread==0)//读到末尾
    {
        break;
    }
    nleft-=nread;
    ptr+=nread;
    }
    return n-nleft;
}

ssize_t Writen(int fd,void* vptr,size_t n)//写一直到文件末尾或者读到设置数量
{
    size_t nleft=n;//未读的数量
    char* ptr=vptr;//当前读到的指针
    size_t nwrite;//每次读到的量

    while(nleft>0)
    {
    if((nwrite=write(fd,ptr,nleft))<0)
    {
        if(errno==EINTR)//如果errno=EINTR(被信号中断去执行信号处理函数)
        {
        nwrite=0;
        }
        else//其他错误
        {
        return -1;
        }
    }
    else if(nwrite==0)//写到末尾
    {
        break;
    }
    nleft-=nwrite;
    ptr+=nwrite;
    }
    return n-nleft;
}
*/
