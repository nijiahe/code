#include<iostream>
#include<boost\function.hpp>
#include<boost\bind.hpp>
using namespace std;


void mainD()
{
	//function<返回值(参数)>
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


//function 接收一个函数
void mainE()
{
	worker w;
	manager m;
	boost::function<void(int)> func1 = boost::bind(&worker::run, &w, _1);
	//绑定类内部的成员函数
	//boost::function<void(int)> func2 = boost::bind(&worker::run2, _1);
	m.setfunc(func1);
	m.run();
	//类内部的非静态函数必须绑定类的实例,因为类的内部成员函数可以修改类内部的数值,而绑定时也应绑定一个类的实例
	cin.get();
}