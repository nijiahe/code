#include<iostream>
#include<boost\function.hpp>
#include<boost\bind.hpp>
using namespace std;


void mainD()
{
	//function<����ֵ(����)>
	boost::function<int(char* )> fun = atoi;
	cout << fun("123") + fun("456");
	cin.get();
}

class worker
{
public:
	int id;
	void run(int toid)
	{
		id = toid;
		cout << id << "worker" << endl;
	}
	void run2(int toid)
	{
		cout << "toid" << endl;
	}

};

class manager
{
public:
	boost::function<void(int)> _func;
public:
	void setfunc(boost::function<void(int)> func)
	{
		_func = func;
	}
	void run()
	{
		for (int i = 0; i < 10; i++)
		{
			_func(i);
		}
	}
};


//function ����һ������
void mainE()
{
	worker w;
	manager m;
	boost::function<void(int)> func1 = boost::bind(&worker::run, &w, _1);
	//�����ڲ��ĳ�Ա����
	//boost::function<void(int)> func2 = boost::bind(&worker::run2, _1);
	m.setfunc(func1);
	m.run();
	//���ڲ��ķǾ�̬������������ʵ��,��Ϊ����ڲ���Ա���������޸����ڲ�����ֵ,����ʱҲӦ��һ�����ʵ��
	cin.get();
}