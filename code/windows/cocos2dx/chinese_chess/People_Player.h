#ifndef __People_PLAYER_H__
#define __People_PLAYER_H__

#include <WinSock2.h>

#include "PLayer.h"
#include "Chesspiece_Place.h"

#include "cocos2d.h"
USING_NS_CC;


class People_Player :public PLayer
{
public:
	//�����߼�
	static bool connect_with_net_server();//���������������
	static void make_server();//��������Ϊһ������������,�൱�ڴ�������
	static void connect_with_other_player();//����������Ҵ����ķ�����,�൱�ڼ��뷿��
	static void run_recv_with_serverthread();//����ȡ�������˵�����
	static void server_with_other_thread();//�����õĽ���
	static void client_with_other_thread();//�ͻ����õĽ���

	void make_step(Chesspiece * origin_chess,Chesspiece_Place des_place);

	static struct sockaddr_in  server_socket_addr;//������socket_in
	static SOCKET server_connectfd;//������������Ĺܵ��Ĺܵ���

	static SOCKET my_connectfd;//����Ϊ����������������������ź�
	static struct sockaddr_in  my_socket_addr;//����Ϊ�������Լ���socket_in
	static int my_bind_port;//����Ϊ�������󶨵Ķ˿ں�

	static SOCKET server_with_other;//�����洢���������Ϣ�ĵط�
	static sockaddr_in server_with_other_sockaddr_in;//�����洢������ҵĵط�

	static SOCKET client_with_other;//������Ҵ洢�����ĵط�
	static sockaddr_in client_with_other_player_sockaddr_in;//������Ҵ洢�����ĵط�
};
#endif