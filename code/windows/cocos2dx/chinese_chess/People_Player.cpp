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

SOCKET People_Player::my_connectfd;//我作为服务器属于自己的管道号
struct sockaddr_in  People_Player::my_socket_addr;//我作为服务器自己的socket_in
int People_Player::my_bind_port ;//我作为服务器绑定的端口号
SOCKET People_Player::server_with_other;//主机存储其他玩家信息的地方
sockaddr_in People_Player::server_with_other_sockaddr_in;//主机存储其他玩家的地方

SOCKET People_Player::client_with_other;//其他玩家存储主机的地方
sockaddr_in People_Player::client_with_other_player_sockaddr_in;//其他玩家存储主机的地方

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

bool People_Player::connect_with_net_server()//与网络服务器相连,只需要知道目标的服务器端口号及IP即可
{
	server_connectfd = socket(AF_INET, SOCK_STREAM, 0);

	int port = 9000;//指服务器用的端口号
	char ipstr[] = "192.168.80.1";//服务器ip
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
		if (receive_buf[0] == 'b')//接收到让我自己建立一个服务器的信号,主机
		{
			make_server();
			send_buf[0] = '2';
			CCLOG("my_bind_port %d", my_bind_port);
			sprintf_s(send_buf + 1, 40, "%d", my_bind_port);
			CCLOG("in_array my_bind_port %s", send_buf + 1);

			std::thread thread1(People_Player::server_with_other_thread);//开启和其他玩家交互的线程,开始accept其他玩家的连接
			thread1.detach();
			send(People_Player::server_connectfd, send_buf, 50, 0);//向服务器发送一个我已经建立好服务器的信号
		}
		else if (receive_buf[0] == 'a')//接收到连接其他服务器的信号,客户机
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
			//服务器端需要开启recv


			int sendByte = send(People_Player::client_with_other, "Z", 1, 0);//向主机发送一个我已经连接到他的服务器的信号
			
			std::thread thread1(People_Player::client_with_other_thread);//开启和主机交互的线程
			thread1.detach();

			
			
			
			if (sendByte <= 0)
			{
				return;
			}
			

		}
		else if (receive_buf[0] == 'c')//接收到心跳信号
		{
			send_buf[0] = '1';
			send(People_Player::server_connectfd, send_buf, 1, 0);//向服务器发送一个存活信号
		}
		
	}
}

/*主机发送给客户机的信号
1.   'A'  代表棋子颜色信号   后一位0代表主机使用红色,1代表主机使用黑色
2.   'Z'  开始游戏信号
*/






void People_Player::server_with_other_thread()//主机用的交互
{
	int clientaddrsize = sizeof(server_with_other_sockaddr_in);
	server_with_other = accept(my_connectfd, (struct sockaddr*)&server_with_other_sockaddr_in, &clientaddrsize);//阻塞接收新的连接,有新的连接连接后开启一个新的线程专门接收管理这个sockfd的信息
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
			
			//建立棋盘的过程
			
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

			int num = rand() % 2;//得到自己用什么颜色的棋

			if (num == 0)//主机用红色
			{
				player->_chess_color = Chess_Color(Chess_Color::Holder_Color::red);
				other_player->_chess_color = Chess_Color(Chess_Color::Holder_Color::black);
				player->add_my_all_chess();
				other_player->add_other_all_chess();
				//send(server_with_other, "A0", 2, 0);//发送主机用红子的信息
			}

			else if (num == 1)
			{
				player->_chess_color = Chess_Color(Chess_Color::Holder_Color::black);
				other_player->_chess_color = Chess_Color(Chess_Color::Holder_Color::red);
				player->add_my_all_chess();
				other_player->add_other_all_chess();
				//send(server_with_other, "A1", 2,0);//发送主机用黑子的信息
			}

			Sprite * sprite = Sprite::create("HelloWorld.png");
			board->addChild(sprite);
			sprite->setContentSize(Size(1000, 1000));

			//board->_chess_vec.pushBack(player->_chess_vector);
			//board->_chess_vec.pushBack(other_player->_chess_vector);
	
			
			

		}
	}
}

void People_Player::client_with_other_thread()//客户机用的交互
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
			//建立棋盘的过程
			{
				Chess_Board * board = Chess_Board::create();
				board->_player_type = Chess_Board::player_type::People;
				People_Player * player = new People_Player;//我自己
				People_Player * other_player = new People_Player;//其他玩家
				player->_chess = board;
				other_player->_chess = board;
				board->_me = (PLayer*)player;
				board->_other_player = (PLayer*)other_player;

				Scene * scene = Scene::create();
				scene->addChild(board);
				Director::getInstance()->replaceScene(scene);

				if (receive_buf[1] == '0')//主机用红色
				{
					player->_chess_color = Chess_Color(Chess_Color::Holder_Color::black);
					other_player->_chess_color = Chess_Color(Chess_Color::Holder_Color::red);
					player->add_my_all_chess();
					other_player->add_other_all_chess();
				}

				else if (receive_buf[1] == '1')//主机用黑色
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


void People_Player::make_server()//将自身作为一个服务器创建,相当于创建房间
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
void People_Player::connect_with_other_player()//连接其他玩家创建的服务器,相当于加入房间
{
	
}