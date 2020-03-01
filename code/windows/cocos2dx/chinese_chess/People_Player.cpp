#include "People_Player.h"
#include "Chesspiece.h"
#include "Chess_Board.h"
#include "Chesspiece_Place.h"
#include "Chess_Step.h"
#include <WinSock2.h>
#include <Ws2tcpip.h>
#include "Chess_Color.h"
#include "Player.h"




SOCKET People_Player::server_connectfd = -1;
struct sockaddr_in  People_Player::server_socket_addr;

SOCKET People_Player::my_connectfd;//����Ϊ�����������Լ��Ĺܵ���
struct sockaddr_in  People_Player::my_socket_addr;//����Ϊ�������Լ���socket_in
int People_Player::my_bind_port ;//����Ϊ�������󶨵Ķ˿ں�
SOCKET People_Player::server_with_other;//�����洢���������Ϣ�ĵط�
sockaddr_in People_Player::server_with_other_sockaddr_in;//�����洢������ҵĵط�

SOCKET People_Player::client_with_other;//������Ҵ洢�����ĵط�
sockaddr_in People_Player::client_with_other_player_sockaddr_in;//������Ҵ洢�����ĵط�

void People_Player::make_step(Chesspiece * origin_chess, Chesspiece_Place des_place)
{
	if (_chess == nullptr)
	{
		return;
	}
	Chess_Step * step = Chess_Step::create();
	step->_move_chesspiece = origin_chess;
	step->_origin_place = origin_chess -> _place;
	if (_chess->is_has_differentcolor_chesspiece(_chess_vector.at(0), des_place))
	{
		step->_be_eaten_chesspiece = _chess->find_chesspiece_by_position(des_place);
	}
	else
	{
		step->_be_eaten_chesspiece = nullptr;
	}
	step->_des_place = des_place;
	_chess_step_vector.pushBack(step);
	_current_step = step;
}

bool People_Player::connect_with_net_server()//���������������,ֻ��Ҫ֪��Ŀ��ķ������˿ںż�IP����
{
	server_connectfd = socket(AF_INET, SOCK_STREAM, 0);

	int port = 9000;//ָ�������õĶ˿ں�
	char ipstr[] = "192.168.80.1";//������ip
	server_socket_addr.sin_family = AF_INET;
	server_socket_addr.sin_port = htons(port);
	inet_pton(AF_INET, ipstr, &server_socket_addr.sin_addr);
	int ret = connect(People_Player::server_connectfd, (struct sockaddr*)&server_socket_addr, sizeof(server_socket_addr));

	if (ret != 0)
	{
		return false;
	}
}

void People_Player::run_recv_with_serverthread()
{
	char receive_buf[50];
	char send_buf[50];
	while (1)
	{
		memset(receive_buf, 0, 50);
		memset(send_buf, 0, 50);
		int recv_Byte = recv(People_Player::server_connectfd, receive_buf, 50, 0);
		if (receive_buf[0] == 'b')//���յ������Լ�����һ�����������ź�,����
		{
			make_server();
			send_buf[0] = '2';
			CCLOG("my_bind_port %d", my_bind_port);
			sprintf_s(send_buf + 1, 40, "%d", my_bind_port);
			CCLOG("in_array my_bind_port %s", send_buf + 1);

			std::thread thread1(People_Player::server_with_other_thread);//������������ҽ������߳�,��ʼaccept������ҵ�����
			thread1.detach();
			send(People_Player::server_connectfd, send_buf, 50, 0);//�����������һ�����Ѿ������÷��������ź�
		}
		else if (receive_buf[0] == 'a')//���յ������������������ź�,�ͻ���
		{
			
			client_with_other = socket(AF_INET, SOCK_STREAM, 0);
			CCLOG("socket_with_other %d", client_with_other);

			CCLOG("recvbuf %s", receive_buf);

			char ip[20];
			char port[10];
			int flag_num = 0;
			CCLOG("%d", strlen(receive_buf));
			int flag[2];
			int flag_value = 0;
			for (int i = 0; i < strlen(receive_buf); i++)
			{
				if (receive_buf[i] == ':')
				{
					flag[flag_value] = i;
					flag_value++;
				}
			}
			receive_buf[flag[0]] = '\0';
			receive_buf[flag[1]] = '\0';
			strcpy_s(ip, 20, receive_buf+flag[0] + 1);
			strcpy_s(port, 10, receive_buf + flag[1] + 1);

			CCLOG("ip %s ", ip);
			CCLOG("port %s", port);
			
			client_with_other_player_sockaddr_in.sin_family = AF_INET;
			client_with_other_player_sockaddr_in.sin_port = htons(atoi(port));
			inet_pton(AF_INET, ip, &client_with_other_player_sockaddr_in.sin_addr);

			int ret = connect(People_Player::client_with_other, (struct sockaddr*)&client_with_other_player_sockaddr_in, sizeof(client_with_other_player_sockaddr_in));

			
			if (ret != 0)
			{
				return;
			}
			
			CCLOG("People_Player::socket_with_other %d", People_Player::client_with_other);
			//����������Ҫ����recv


			int sendByte = send(People_Player::client_with_other, "Z", 1, 0);//����������һ�����Ѿ����ӵ����ķ��������ź�
			
			std::thread thread1(People_Player::client_with_other_thread);//�����������������߳�
			thread1.detach();

			
			
			
			if (sendByte <= 0)
			{
				return;
			}
			

		}
		else if (receive_buf[0] == 'c')//���յ������ź�
		{
			send_buf[0] = '1';
			send(People_Player::server_connectfd, send_buf, 1, 0);//�����������һ������ź�
		}
		
	}
}

/*�������͸��ͻ������ź�
1.   'A'  ����������ɫ�ź�   ��һλ0��������ʹ�ú�ɫ,1��������ʹ�ú�ɫ
2.   'Z'  ��ʼ��Ϸ�ź�
*/






void People_Player::server_with_other_thread()//�����õĽ���
{
	int clientaddrsize = sizeof(server_with_other_sockaddr_in);
	server_with_other = accept(my_connectfd, (struct sockaddr*)&server_with_other_sockaddr_in, &clientaddrsize);//���������µ�����,���µ��������Ӻ���һ���µ��߳�ר�Ž��չ������sockfd����Ϣ
	char receive_buf[50];
	
	while (1)
	{
		memset(receive_buf, 0, 50);
		int recv_Byte = recv(server_with_other, receive_buf, 50, 0);
		CCLOG("recv %s  %d", receive_buf,strlen(receive_buf));

		

		if (recv_Byte <= 0)
		{
			return;
		}
		if (receive_buf[0] == 'Z')
		{
			send(server_with_other, "Z", 1, 0);
			
			//�������̵Ĺ���
			
			Chess_Board * board = Chess_Board::create();
			board->_player_type = Chess_Board::player_type::People;
			People_Player * player = new People_Player;
			People_Player * other_player = new People_Player;
			player->_chess = board;
			other_player->_chess = board;
			board->_me = (PLayer*)player;
			board->_other_player = (PLayer*)other_player;

			Scene * scene = Scene::create();
			scene->addChild(board);
			Director::getInstance()->replaceScene(scene);

			int num = rand() % 2;//�õ��Լ���ʲô��ɫ����

			if (num == 0)//�����ú�ɫ
			{
				player->_chess_color = Chess_Color(Chess_Color::Holder_Color::red);
				other_player->_chess_color = Chess_Color(Chess_Color::Holder_Color::black);
				player->add_my_all_chess();
				other_player->add_other_all_chess();
				//send(server_with_other, "A0", 2, 0);//���������ú��ӵ���Ϣ
			}

			else if (num == 1)
			{
				player->_chess_color = Chess_Color(Chess_Color::Holder_Color::black);
				other_player->_chess_color = Chess_Color(Chess_Color::Holder_Color::red);
				player->add_my_all_chess();
				other_player->add_other_all_chess();
				//send(server_with_other, "A1", 2,0);//���������ú��ӵ���Ϣ
			}

			Sprite * sprite = Sprite::create("HelloWorld.png");
			board->addChild(sprite);
			sprite->setContentSize(Size(1000, 1000));

			//board->_chess_vec.pushBack(player->_chess_vector);
			//board->_chess_vec.pushBack(other_player->_chess_vector);
	
			
			

		}
	}
}

void People_Player::client_with_other_thread()//�ͻ����õĽ���
{
	char receive_buf[50];
	while (1)
	{
		memset(receive_buf, 0, 50);
		int recv_Byte = recv(client_with_other, receive_buf, 50, 0);
		CCLOG("recv %s", receive_buf);
		if (recv_Byte <= 0)
		{
			return;
		}
		if (receive_buf[0] == 'Z')
		{
			CCLOG("start game");
		}
		if (receive_buf[0] == 'A')
		{
			//�������̵Ĺ���
			{
				Chess_Board * board = Chess_Board::create();
				board->_player_type = Chess_Board::player_type::People;
				People_Player * player = new People_Player;//���Լ�
				People_Player * other_player = new People_Player;//�������
				player->_chess = board;
				other_player->_chess = board;
				board->_me = (PLayer*)player;
				board->_other_player = (PLayer*)other_player;

				Scene * scene = Scene::create();
				scene->addChild(board);
				Director::getInstance()->replaceScene(scene);

				if (receive_buf[1] == '0')//�����ú�ɫ
				{
					player->_chess_color = Chess_Color(Chess_Color::Holder_Color::black);
					other_player->_chess_color = Chess_Color(Chess_Color::Holder_Color::red);
					player->add_my_all_chess();
					other_player->add_other_all_chess();
				}

				else if (receive_buf[1] == '1')//�����ú�ɫ
				{
					player->_chess_color = Chess_Color(Chess_Color::Holder_Color::red);
					other_player->_chess_color = Chess_Color(Chess_Color::Holder_Color::black);
					player->add_my_all_chess();
					other_player->add_other_all_chess();
				}
				board->_chess_vec.pushBack(player->_chess_vector);
				board->_chess_vec.pushBack(other_player->_chess_vector);

			}
		}
	}
}


void People_Player::make_server()//��������Ϊһ������������,�൱�ڴ�������
{
	my_connectfd = socket(AF_INET, SOCK_STREAM, 0);
	if (my_connectfd == INVALID_SOCKET)
	{
		return;
	}

	my_bind_port = 9001;
	my_socket_addr.sin_family = AF_INET;
	my_socket_addr.sin_port = htons(my_bind_port);
	my_socket_addr.sin_addr.S_un.S_addr = INADDR_ANY;

	int ret = bind(my_connectfd, (struct sockaddr*)&my_socket_addr, sizeof(my_socket_addr));
	if (ret != 0)
	{
		return;
	}

	if (listen(my_connectfd, 2) != 0)
	{
		return;
	}
}
void People_Player::connect_with_other_player()//����������Ҵ����ķ�����,�൱�ڼ��뷿��
{
	
}