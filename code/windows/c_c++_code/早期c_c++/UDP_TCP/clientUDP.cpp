//UDPʹ��һ��ͨ��,�Ͽ��
#include<iostream>
#include<boost/asio.hpp>
#include<string>
#include<stdlib.h>

using namespace boost::asio;
using namespace std;

void main()
{
	boost::asio::io_service io_serviceA;//io����(�������),��UDPͨ�ų�ʼ��
	boost::asio::ip::udp::socket udp_socket(io_serviceA);//����һ������Э��
	boost::asio::ip::udp::endpoint local_add(boost::asio::ip::address::from_string("127.0.0.1"), 1080);
	//�˿�(��ȡ��Ϣ��ip��ַ,�˿�)

	//�ͻ��˲���Ҫ�󶨶˿�
	//udp_socket.bind(local_add);//�����õ�ip�Ͷ˿�
	udp_socket.open(local_add.protocol());//�����õ�����˿ڴ�udp_socket����Э��,���Э��
	char receive_str[1024] = {0};//���ڴ�ŷ��͵���Ϣ
	while (1)
	{
		string sendstr;
		cout << "���� ";
		cin >> sendstr;
		cout << endl;
		udp_socket.send_to(buffer(sendstr.c_str(),sendstr.size()),local_add);
		udp_socket.receive_from(buffer(receive_str, 1024), local_add);
		cout << "�յ� "<<receive_str << endl;

	}

	system("pause");
}