//UDP使用一次通信,较快捷
#include<iostream>
#include<boost/asio.hpp>
#include<string>
#include<stdlib.h>

using namespace boost::asio;
using namespace std;

void main()
{
	boost::asio::io_service io_serviceA;//io服务(网络服务),给UDP通信初始化
	boost::asio::ip::udp::socket udp_socket(io_serviceA);//创建一个服务协议
	boost::asio::ip::udp::endpoint local_add(boost::asio::ip::address::from_string("127.0.0.1"), 1080);
	//端口(获取信息的ip地址,端口)

	//客户端不需要绑定端口
	//udp_socket.bind(local_add);//绑定设置的ip和端口
	udp_socket.open(local_add.protocol());//用设置的这个端口打开udp_socket服务协议,添加协议
	char receive_str[1024] = {0};//用于存放发送的信息
	while (1)
	{
		string sendstr;
		cout << "输入 ";
		cin >> sendstr;
		cout << endl;
		udp_socket.send_to(buffer(sendstr.c_str(),sendstr.size()),local_add);
		udp_socket.receive_from(buffer(receive_str, 1024), local_add);
		cout << "收到 "<<receive_str << endl;

	}

	system("pause");
}