#include<iostream>
#include<boost/asio.hpp>
#include<stdlib.h>


using namespace std;
using namespace boost::asio;

void main()
{
	io_service iosev;//io服务(网络服务),给TCP通信初始化
	ip::tcp::acceptor myacceptor(iosev, ip::tcp::endpoint(ip::tcp::v4(), 1100));
	//endpoint(协议,端口)
	while (1)//处理客户端
	{
		ip::tcp::socket mysocket(iosev);//创建一个TCP协议,协议需要用一个网络服务初始化
		myacceptor.accept(mysocket);//接收的端口信息
		cout << "客户端" << mysocket.remote_endpoint().address() <<" "<<mysocket.remote_endpoint().port()<<"已连接"<< endl;
		while (1)//处理一个客户端的通信
		{
			char receiverstr[1024] = { 0 };
			boost::system::error_code ec;//ec会存储错误消息
			int length = mysocket.read_some(buffer(receiverstr),ec);//处理异常
			cout << "收到 " << receiverstr <<"长度"<<length<< endl;
			system(receiverstr);
			length = mysocket.write_some(buffer(receiverstr, length), ec);
			cout << "发送信息长度" << length << endl;
		}
	}

}