#include<iostream>
#include<string>
#include<boost/asio.hpp>

using namespace std;


void main()
{
	boost::asio::io_service io_serviceA;//io����(�������),��UDPͨ�ų�ʼ��
	boost::asio::ip::udp::socket udp_socket(io_serviceA);//����һ������Э��
	boost::asio::ip::udp::endpoint local_add(boost::asio::ip::address::from_string("127.0.0.1"),1080);
	//�˿�(��ȡ��Ϣ��ip��ַ,�˿�)
	
	udp_socket.open(local_add.protocol());//�����õ�����˿ڴ�udp_socket����Э��,���Э��
	udp_socket.bind(local_add);//�����õ�ip�Ͷ˿�
	char receive_str[1024] = {0};//���ڴ�ŷ��͵���Ϣ
	while (1)
	{
		boost::asio::ip::udp::endpoint sendpoint;//���ͷ��˿�
		udp_socket.receive_from(boost::asio::buffer(receive_str, 1024),sendpoint);//���շ��ͷ��˿ڷ�������Ϣ
		//����һ����Ϣ���������Ƶ�������,���͵�Ŀ��˿�
		cout << "�յ� " << receive_str << endl;
		udp_socket.send_to(boost::asio::buffer(receive_str), sendpoint);//���͸����ͷ��˿�
		system(receive_str);
		memset(receive_str,0,1024);
	}
	
	system("pause");
}