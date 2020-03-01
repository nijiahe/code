#include <iostream>
#include <string>
using namespace std;
//����ģʽ������ģʽ��ĳһ�������ṩһ���������
//���ɴ��������ƶ�Դ��������á�
//�������һ���˻�һ������������һ���˻���һ��������ȡ�ж���
//ĳЩ����£��ͻ�������߲��ܹ�ֱ������һ������
//�����������ڿͻ���Ŀ�����ֱ�����н�����á�
//�ͻ��˷ֱ治�����������������ʵ�������
//����ģʽ���Բ���֪�������ı��������
//����������һ�����������Ľӿڣ���ʱ���������ܹ��������������
//��������������ϵͳ��������ɫ��Ϊ���������롣

class SchoolGirl
{
public:
	string name;
};


class IGiveGift
{
public:
	virtual void giveDolls() = 0;
	virtual void giveFlowers() = 0;
};

class Pursuit :public IGiveGift
{
private:
	SchoolGirl mm;
public:
	Pursuit(SchoolGirl m)
	{
		mm = m;
	}
	void giveDolls()
	{
		cout << mm.name << " ��������" << endl;
	}
	void giveFlowers()
	{
		cout << mm.name << " �����ʻ�" << endl;
	}
};

class Proxy :public IGiveGift//�����������,ʵ���������������������Ҫ������,�Ӷ����������Ǹ���
{
private:
	Pursuit gg;
public:
	Proxy(SchoolGirl mm) :gg(mm)
	{
		//gg=g;
	}
	void giveDolls()
	{
		gg.giveDolls();
	}
	void giveFlowers()
	{
		gg.giveFlowers();
	}
};

int mainF()
{
	SchoolGirl lijiaojiao;
	lijiaojiao.name = "���";
	Pursuit zhuojiayi(lijiaojiao);
	Proxy daili(lijiaojiao);

	daili.giveDolls();
	cin.get();
	return 0;
}