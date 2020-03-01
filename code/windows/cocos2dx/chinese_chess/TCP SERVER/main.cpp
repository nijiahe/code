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
	int client_as_a_server_port = -1;//���socket��Ϊһ��������ʱ���������Ķ˿ں�
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
		clientaddr.client_sockfd = accept(sockfd, (struct sockaddr*)&clientaddr.clientaddr, &clientaddrsize);//���������µ�����,���µ��������Ӻ���һ���µ��߳�ר�Ž��չ������sockfd����Ϣ
		std::cout << "client ip:" << inet_ntop(AF_INET,&clientaddr.clientaddr.sin_addr, clientipstr,clientaddrsize) << "port :" << ntohs(clientaddr.clientaddr.sin_port) << "connect" << std::endl;

		clientsockaddr_vector.push_back(clientaddr);//�����fd���뵽������
		std::cout << "main ����������� " << clientsockaddr_vector.size() << "receive" << std::endl;
		std::cout << "main ���ڵȴ�����Ҹ��� " << free_clientsockaddr_vector.size() << " receive " << std::endl;
		struct timeval timeout = { 60000,0 };//���ý���ʱ��Ϊ1����
		int ret = setsockopt(clientaddr.client_sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
		if (ret != 0)
		{
			std::cout << "����ʱ������ʧ��" << std::endl;
		}
		std::thread thread1(manage, clientaddr );//�����̴߳������fd����Ϣ
		thread1.detach();//�����̷߳���
	}
	return 0;
}

/*���������͸��ͻ���
1.  a  �ÿͻ�������Ŀ�������
2.	b  �ÿͻ����Լ�����һ��������
3.	c  �����ź�
*/

/*�ͻ��˷��͸�������
1.	'0'  //Ѱ�Ҷ�������
2.	'1'  //����ź�
3.	'2'  //�ѽ����������ź�
*/

/*  'z'  �����б�����������ĵ���*/

void manage(struct my_socket clientaddr)
{
	while (1)
	{	
		std::cout << "thread ���ڵȴ�����Ҹ��� "<< free_clientsockaddr_vector .size()<<" receive " << std::endl;
		std::cout << "thread ����������� " << clientsockaddr_vector.size() << "receive" << std::endl;
		char receive_buf[50];
		memset(receive_buf, 0, 50);
		int recv_Byte = recv(clientaddr.client_sockfd, receive_buf, 50, 0);
		if (recv_Byte <= 0)//�����һ�ν�����ϢΪ��
		{
			std::cout << "receive error" << std::endl;
			if (recv_Byte == 0)//�������ֵΪ0
			{
				std::cout << "���ӹر�" << std::endl;
				delete_by_sockfd(clientaddr.client_sockfd);
				break;
			}
			else if (recv_Byte == SOCKET_ERROR)//�������ֵΪSOCKET_ERROR��-1
			{
				int error_id = WSAGetLastError();
				if (error_id == WSAETIMEDOUT)//��������ǳ�ʱ,�Ƿ��������ͻ��˷���һ�������ź�,�����ʱ���ղ����ͻ��˵Ĵ���ź�,��ôɾ����sockfd
				{
					std::cout << "��ʱ,����������Ϣ" << std::endl;
					send(clientaddr.client_sockfd, "c", 1, 0);//c�������ź�
					int recv_Byte_second = recv(clientaddr.client_sockfd, receive_buf, 50, 0);
					if (recv_Byte_second <= 0)//����ڶ��λ�δ���յ���Ϣ,�Ͱ����sockfdɾ��
					{
						std::cout << "δ���ܵ�������Ϣ,�����sockfd" << std::endl;
						delete_by_sockfd(clientaddr.client_sockfd);
						break;
					}
				}
				else
				{
					switch (WSAGetLastError())
					{
					case WSANOTINITIALISED:
						std::cout << "��ʹ�ô�API֮ǰӦ���ȳɹ��ص���WSAStartup()" << std::endl;
						break;
					case WSAENETDOWN:
						std::cout << "WINDOWS�׽ӿ�ʵ�ּ�⵽������ϵͳʧЧ��" << std::endl;
						break; 
					case WSAENOTCONN:
						std::cout << "�׽ӿ�δ���ӡ�" << std::endl;
						break; 
					case WSAEINTR:
						std::cout << "�������̱�WSACancelBlockingCall()ȡ����" << std::endl;
						break; 
					case WSAEINPROGRESS:
						std::cout << "һ��������WINDOWS�׽ӿڵ������������С�" << std::endl;
						break; 
					case WSAENOTSOCK:
						std::cout << "�����ֲ���һ���׽ӿڡ�" << std::endl;
						break; 
					case WSAEOPNOTSUPP:
						std::cout << "ָ����MSG_OOB�����׽ӿڲ���SOCK_STREAM���͵ġ�" << std::endl;
						break; 
					case WSAESHUTDOWN:
						std::cout << "�׽ӿ��ѱ��رա���һ���׽ӿ���0��2��how��������shutdown()�رպ��޷�����recv()�������ݡ�" << std::endl;
						break; 
					case WSAEWOULDBLOCK:
						std::cout << "�׽ӿڱ�ʶΪ������ģʽ�������ղ��������������" << std::endl;
						break; 
					case WSAEMSGSIZE:
						std::cout << "���ݱ�̫���޷�ȫ��װ�뻺�������ʱ����С�" << std::endl;
						break; 
					case WSAEINVAL:
						std::cout << "�׽ӿ�δ��bind()��������" << std::endl;
						break; 
					case WSAECONNABORTED:
						std::cout << "���ڳ�ʱ������ԭ�����·ʧЧ��" << std::endl;
						break; 
					case WSAECONNRESET:
						std::cout << "Զ��ǿ����ֹ�����·��" << std::endl;
						break; 
					}
					
					std::cout << "���ǳ�ʱ,ֱ������" << std::endl;
					delete_by_sockfd(clientaddr.client_sockfd);
					break;
				}
			}
		}
		if (receive_buf[0]=='0')//Ѱ�Ҷ��ֵ�����
		{
			if (free_clientsockaddr_vector.size() > 0)//��������ڵȴ����ֵ����,��ô���϶��Ѿ����˷�����
			{
				std::cout << "�����ڵȴ����ֵ����" << std::endl;
				char send_buf[50];
				memset(send_buf, 0, 50);
				send_buf[0] = 'a';
				send_buf[1] = ':';
				struct my_socket free_player_socket = free_clientsockaddr_vector.front();//��õ�ǰ���еĵ�һ��
				
				free_player_socket.clientaddr.sin_port = htons(free_player_socket.client_as_a_server_port);//����������Ķ˿�
				std::cout << "����Ķ˿�" << free_player_socket.client_as_a_server_port << std::endl;
				std::cout << "convert ip:" << inet_ntop(AF_INET, &free_player_socket.clientaddr.sin_addr, send_buf+2, sizeof(free_player_socket.clientaddr)) << "port :" << ntohs(clientaddr.clientaddr.sin_port) << "connect" << std::endl;
				int len = strlen(send_buf);
				send_buf[len] = ':';
				sprintf_s(send_buf + len + 1, 20, "%d", ntohs(free_player_socket.clientaddr.sin_port));
				
				std::cout << "send_buf" << send_buf << std::endl;
				free_clientsockaddr_vector.erase(free_clientsockaddr_vector.begin());//������ӿ��ж�����Ĩȥ
				send(clientaddr.client_sockfd, send_buf, strlen(send_buf), 0);//�������Ϊ'a'�����ĸ������ǰip,������Ŀ����ҵ�sockaddr��Ϣ;

			}
			else//û�����ڵȴ������
			{
				std::cout << "û�����ڵȴ������" << std::endl;
				send(clientaddr.client_sockfd, "b", 1, 0);//����'b'����,���������Լ���һ��������,�������Ҽ���ȴ��������
				free_clientsockaddr_vector_mut.lock();
				free_clientsockaddr_vector.push_back(clientaddr);
				free_clientsockaddr_vector_mut.unlock();
			}
		}
		else if (receive_buf[0] == '1')//����ź�
		{
			std::cout << "���" << std::endl;
		}
		else if (receive_buf[0] == '2')//�Ѿ������÷�����
		{
			int  num = atoi(receive_buf + 1);
			std::cout << "���ݹ����Ķ˿�" << num << std::endl;
			
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

			
			clientaddr.client_as_a_server_port = *((int*)(receive_buf + 1));//���˵�һλ��ű�־����λ�������int���ͱ�������ʾ���Ѿ������˷�����
			std::cout << "�����" << clientaddr.client_as_a_server_port << std::endl;
			std::cout << "�ѽ���������" << std::endl;
		}
	}
	

}

void delete_by_sockfd(SOCKET sockfd)//��������ʱ��Ҫ�����������,��ֹ�̼߳����
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