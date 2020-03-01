#include<iostream>
#include<boost/asio.hpp>
#include<stdlib.h>



using namespace std;
using namespace boost::asio;

void main()
{
	io_service iosev;//io服务
	ip::tcp::socket mysocket(iosev);//创建一个TCP协议
	ip::tcp::endpoint ep(ip::address_v4::from_string("127.0.0.1"), 1100);//初始化一个端口

	boost::system::error_code ec;
	mysocket.connect(ep, ec);//用这个端口初始化这个协议
	while (1)
	{
		char str[1024] = { 0 };
		cout << "输入 " ;
		cin >> str;
		cout << endl;
		mysocket.write_some(buffer(str), ec);//
		memset(str, 0, 1024);
		mysocket.read_some(buffer(str), ec);
		cout << "收到" << str << endl;

	}

	system("pause");
}