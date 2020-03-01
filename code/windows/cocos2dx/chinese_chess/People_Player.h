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
	//网络逻辑
	static bool connect_with_net_server();//与网络服务器相连
	static void make_server();//将自身作为一个服务器创建,相当于创建房间
	static void connect_with_other_player();//连接其他玩家创建的服务器,相当于加入房间
	static void run_recv_with_serverthread();//来获取服务器端的数据
	static void server_with_other_thread();//主机用的交互
	static void client_with_other_thread();//客户机用的交互

	void make_step(Chesspiece * origin_chess,Chesspiece_Place des_place);

	static struct sockaddr_in  server_socket_addr;//服务器socket_in
	static SOCKET server_connectfd;//与服务器相连的管道的管道号

	static SOCKET my_connectfd;//我作为服务器与其他玩家相连的信号
	static struct sockaddr_in  my_socket_addr;//我作为服务器自己的socket_in
	static int my_bind_port;//我作为服务器绑定的端口号

	static SOCKET server_with_other;//主机存储其他玩家信息的地方
	static sockaddr_in server_with_other_sockaddr_in;//主机存储其他玩家的地方

	static SOCKET client_with_other;//其他玩家存储主机的地方
	static sockaddr_in client_with_other_player_sockaddr_in;//其他玩家存储主机的地方
};
#endif