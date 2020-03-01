#include <WinSock2.h>
#include <iostream>
#include <vector>
#include <thread>
#include <Ws2tcpip.h>
#include <mutex>

int Port = 9000;

struct my_socket
{
	struct sockaddr_in clientaddr;
	SOCKET client_sockfd;
	int client_as_a_server_port = -1;//这个socket作为一个服务器时它服务器的端口号
};

std::vector<my_socket> clientsockaddr_vector;
std::vector<my_socket> free_clientsockaddr_vector;

void manage(struct my_socket clientaddr);
void delete_by_sockfd(SOCKET sockfd);

std::mutex clientsockaddr_vector_mut;
std::mutex free_clientsockaddr_vector_mut;

int main() 
{
	WSADATA data;
	int flag = WSAStartup(MAKEWORD(2, 2), &data);


	SOCKET sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == INVALID_SOCKET)
	{
		return 0;
	}
		
	struct sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(Port);
	serveraddr.sin_addr.S_un.S_addr = INADDR_ANY;

	int ret = bind(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if (ret != 0)
	{
		return 0;
	}


	if (listen(sockfd, 20) != 0)
	{
		return 0;
	}
	
	while (1)
	{
		std::cout << "waiting" << std::endl;
		struct my_socket clientaddr;
		int clientaddrsize = sizeof(clientaddr.clientaddr);
		char clientipstr[128];
		clientaddr.client_sockfd = accept(sockfd, (struct sockaddr*)&clientaddr.clientaddr, &clientaddrsize);//阻塞接收新的连接,有新的连接连接后开启一个新的线程专门接收管理这个sockfd的信息
		std::cout << "client ip:" << inet_ntop(AF_INET,&clientaddr.clientaddr.sin_addr, clientipstr,clientaddrsize) << "port :" << ntohs(clientaddr.clientaddr.sin_port) << "connect" << std::endl;

		clientsockaddr_vector.push_back(clientaddr);//将这个fd加入到数组中
		std::cout << "main 总在线玩家数 " << clientsockaddr_vector.size() << "receive" << std::endl;
		std::cout << "main 正在等待的玩家个数 " << free_clientsockaddr_vector.size() << " receive " << std::endl;
		struct timeval timeout = { 60000,0 };//设置接收时间为1分钟
		int ret = setsockopt(clientaddr.client_sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
		if (ret != 0)
		{
			std::cout << "接收时间设置失败" << std::endl;
		}
		std::thread thread1(manage, clientaddr );//创建线程处理这个fd的信息
		thread1.detach();//设置线程分离
	}
	return 0;
}

/*服务器发送给客户端
1.  a  让客户端连接目标服务器
2.	b  让客户端自己建立一个服务器
3.	c  心跳信号
*/

/*客户端发送给服务器
1.	'0'  //寻找对手请求
2.	'1'  //存活信号
3.	'2'  //已建立服务器信号
*/

/*  'z'  代表有别的玩家连到你的电脑*/

void manage(struct my_socket clientaddr)
{
	while (1)
	{	
		std::cout << "thread 正在等待的玩家个数 "<< free_clientsockaddr_vector .size()<<" receive " << std::endl;
		std::cout << "thread 总在线玩家数 " << clientsockaddr_vector.size() << "receive" << std::endl;
		char receive_buf[50];
		memset(receive_buf, 0, 50);
		int recv_Byte = recv(clientaddr.client_sockfd, receive_buf, 50, 0);
		if (recv_Byte <= 0)//如果第一次接收消息为空
		{
			std::cout << "receive error" << std::endl;
			if (recv_Byte == 0)//如果返回值为0
			{
				std::cout << "连接关闭" << std::endl;
				delete_by_sockfd(clientaddr.client_sockfd);
				break;
			}
			else if (recv_Byte == SOCKET_ERROR)//如果返回值为SOCKET_ERROR即-1
			{
				int error_id = WSAGetLastError();
				if (error_id == WSAETIMEDOUT)//如果错误是超时,那服务器给客户端发送一个心跳信号,如果此时接收不到客户端的存活信号,那么删除该sockfd
				{
					std::cout << "超时,接收心跳消息" << std::endl;
					send(clientaddr.client_sockfd, "c", 1, 0);//c代表存活信号
					int recv_Byte_second = recv(clientaddr.client_sockfd, receive_buf, 50, 0);
					if (recv_Byte_second <= 0)//如果第二次还未接收到信息,就把这个sockfd删除
					{
						std::cout << "未接受到心跳消息,清理此sockfd" << std::endl;
						delete_by_sockfd(clientaddr.client_sockfd);
						break;
					}
				}
				else
				{
					switch (WSAGetLastError())
					{
					case WSANOTINITIALISED:
						std::cout << "在使用此API之前应首先成功地调用WSAStartup()" << std::endl;
						break;
					case WSAENETDOWN:
						std::cout << "WINDOWS套接口实现检测到网络子系统失效。" << std::endl;
						break; 
					case WSAENOTCONN:
						std::cout << "套接口未连接。" << std::endl;
						break; 
					case WSAEINTR:
						std::cout << "阻塞进程被WSACancelBlockingCall()取消。" << std::endl;
						break; 
					case WSAEINPROGRESS:
						std::cout << "一个阻塞的WINDOWS套接口调用正在运行中。" << std::endl;
						break; 
					case WSAENOTSOCK:
						std::cout << "描述字不是一个套接口。" << std::endl;
						break; 
					case WSAEOPNOTSUPP:
						std::cout << "指定了MSG_OOB，但套接口不是SOCK_STREAM类型的。" << std::endl;
						break; 
					case WSAESHUTDOWN:
						std::cout << "套接口已被关闭。当一个套接口以0或2的how参数调用shutdown()关闭后，无法再用recv()接收数据。" << std::endl;
						break; 
					case WSAEWOULDBLOCK:
						std::cout << "套接口标识为非阻塞模式，但接收操作会产生阻塞。" << std::endl;
						break; 
					case WSAEMSGSIZE:
						std::cout << "数据报太大无法全部装入缓冲区，故被剪切。" << std::endl;
						break; 
					case WSAEINVAL:
						std::cout << "套接口未用bind()进行捆绑。" << std::endl;
						break; 
					case WSAECONNABORTED:
						std::cout << "由于超时或其他原因，虚电路失效。" << std::endl;
						break; 
					case WSAECONNRESET:
						std::cout << "远端强制中止了虚电路。" << std::endl;
						break; 
					}
					
					std::cout << "不是超时,直接清理" << std::endl;
					delete_by_sockfd(clientaddr.client_sockfd);
					break;
				}
			}
		}
		if (receive_buf[0]=='0')//寻找对手的请求
		{
			if (free_clientsockaddr_vector.size() > 0)//如果有正在等待对手的玩家,那么他肯定已经建了服务器
			{
				std::cout << "有正在等待对手的玩家" << std::endl;
				char send_buf[50];
				memset(send_buf, 0, 50);
				send_buf[0] = 'a';
				send_buf[1] = ':';
				struct my_socket free_player_socket = free_clientsockaddr_vector.front();//获得当前队列的第一个
				
				free_player_socket.clientaddr.sin_port = htons(free_player_socket.client_as_a_server_port);//保存服务器的端口
				std::cout << "保存的端口" << free_player_socket.client_as_a_server_port << std::endl;
				std::cout << "convert ip:" << inet_ntop(AF_INET, &free_player_socket.clientaddr.sin_addr, send_buf+2, sizeof(free_player_socket.clientaddr)) << "port :" << ntohs(clientaddr.clientaddr.sin_port) << "connect" << std::endl;
				int len = strlen(send_buf);
				send_buf[len] = ':';
				sprintf_s(send_buf + len + 1, 20, "%d", ntohs(free_player_socket.clientaddr.sin_port));
				
				std::cout << "send_buf" << send_buf << std::endl;
				free_clientsockaddr_vector.erase(free_clientsockaddr_vector.begin());//将这个从空闲队列中抹去
				send(clientaddr.client_sockfd, send_buf, strlen(send_buf), 0);//发送序号为'a'的密文给这个当前ip,并传入目标玩家的sockaddr信息;

			}
			else//没有正在等待的玩家
			{
				std::cout << "没有正在等待的玩家" << std::endl;
				send(clientaddr.client_sockfd, "b", 1, 0);//发送'b'密文,让这个玩家自己起一个服务器,将这个玩家加入等待玩家行列
				free_clientsockaddr_vector_mut.lock();
				free_clientsockaddr_vector.push_back(clientaddr);
				free_clientsockaddr_vector_mut.unlock();
			}
		}
		else if (receive_buf[0] == '1')//存活信号
		{
			std::cout << "存活" << std::endl;
		}
		else if (receive_buf[0] == '2')//已经建立好服务器
		{
			int  num = atoi(receive_buf + 1);
			std::cout << "传递过来的端口" << num << std::endl;
			
			std::vector<my_socket>::iterator ibegin1 = clientsockaddr_vector.begin();
			std::vector<my_socket>::iterator iend1 = clientsockaddr_vector.end();
			for (; ibegin1 != iend1; ibegin1++)
			{
				if ((*ibegin1).client_sockfd == clientaddr.client_sockfd)
				{
					(*ibegin1).client_as_a_server_port = num;
					break;
				}
			}

			std::vector<my_socket>::iterator ibegin2 = free_clientsockaddr_vector.begin();
			std::vector<my_socket>::iterator iend2 = free_clientsockaddr_vector.end();
			for (; ibegin2 != iend2; ibegin2++)
			{
				if ((*ibegin2).client_sockfd == clientaddr.client_sockfd)
				{
					(*ibegin2).client_as_a_server_port = num;
					break;
				}
			}

			
			clientaddr.client_as_a_server_port = *((int*)(receive_buf + 1));//除了第一位存放标志后四位用来存放int类型变量来表示它已经建立了服务器
			std::cout << "保存的" << clientaddr.client_as_a_server_port << std::endl;
			std::cout << "已建立服务器" << std::endl;
		}
	}
	

}

void delete_by_sockfd(SOCKET sockfd)//处理数组时需要给数组加上锁,防止线程间干扰
{
	std::vector<my_socket>::iterator ibegin1 = clientsockaddr_vector.begin();
	std::vector<my_socket>::iterator iend1 = clientsockaddr_vector.end();
	for (; ibegin1 != iend1; ibegin1++)
	{
		if ((*ibegin1).client_sockfd == sockfd)
		{
			clientsockaddr_vector_mut.lock();
			clientsockaddr_vector.erase(ibegin1);
			clientsockaddr_vector_mut.unlock();
			break;
		}
	}

	std::vector<my_socket>::iterator ibegin2 = free_clientsockaddr_vector.begin();
	std::vector<my_socket>::iterator iend2 = free_clientsockaddr_vector.end();
	for (; ibegin2 != iend2; ibegin2++)
	{
		if ((*ibegin2).client_sockfd == sockfd)
		{
			free_clientsockaddr_vector_mut.lock();
			free_clientsockaddr_vector.erase(ibegin2);
			free_clientsockaddr_vector_mut.unlock();
			break;
		}
	}

	closesocket(sockfd);
}