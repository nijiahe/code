#include<iostream>
#include<boost/asio.hpp>
#include<stdlib.h>



using namespace std;
using namespace boost::asio;

void main()
{
	io_service iosev;//io����
	ip::tcp::socket mysocket(iosev);//����һ��TCPЭ��
	ip::tcp::endpoint ep(ip::address_v4::from_string("127.0.0.1"), 1100);//��ʼ��һ���˿�

	boost::system::error_code ec;
	mysocket.connect(ep, ec);//������˿ڳ�ʼ�����Э��
	while (1)
	{
		char str[1024] = { 0 };
		cout << "���� " ;
		cin >> str;
		cout << endl;
		mysocket.write_some(buffer(str), ec);//
		memset(str, 0, 1024);
		mysocket.read_some(buffer(str), ec);
		cout << "�յ�" << str << endl;

	}

	system("pause");
}