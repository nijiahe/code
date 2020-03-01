#include<iostream>
#include<string>
#include<boost/asio.hpp>

using namespace std;


void main()
{
	boost::asio::io_service io_serviceA;//io服务(网络服务),给UDP通信初始化
	boost::asio::ip::udp::socket udp_socket(io_serviceA);//创建一个服务协议
	boost::asio::ip::udp::endpoint local_add(boost::asio::ip::address::from_string("127.0.0.1"),1080);
	//端口(获取信息的ip地址,端口)
	
	udp_socket.open(local_add.protocol());//用设置的这个端口打开udp_socket服务协议,添加协议
	udp_socket.bind(local_add);//绑定设置的ip和端口
	char receive_str[1024] = {0};//用于存放发送的信息
	while (1)
	{
		boost::asio::ip::udp::endpoint sendpoint;//发送方端口
		udp_socket.receive_from(boost::asio::buffer(receive_str, 1024),sendpoint);//接收发送方端口发来的信息
		//接受一个消息并把它复制到数组内,发送到目标端口
		cout << "收到 " << receive_str << endl;
		udp_socket.send_to(boost::asio::buffer(receive_str), sendpoint);//发送给发送方端口
		system(receive_str);
		memset(receive_str,0,1024);
	}
	
	system("pause");
}