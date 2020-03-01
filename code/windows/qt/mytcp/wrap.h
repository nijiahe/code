#include<stdio.h>
#include<stdlib.h>

#include<sys/stat.h>
#include<sys/types.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>

#define socklen_t int

void my_err(const char* str);
SOCKET Accept(int sockfd,struct sockaddr* addr,socklen_t* addrlen);
void Bind(int sockfd,const struct sockaddr* addr,socklen_t addrlen);
void Connect(int sockfd,const struct sockaddr* addr,socklen_t addrlen);
void Listen(int sockfd,int backlog);
SOCKET Socket(int domain,int type,int protocol);
ssize_t Read(int fd,void* buf,size_t count);
ssize_t Write(int fd,void* buf,size_t count);
void Close(int fd);
ssize_t Readn(int fd,void* vptr,size_t n);
ssize_t Writen(int fd ,void* vptr,size_t n);
