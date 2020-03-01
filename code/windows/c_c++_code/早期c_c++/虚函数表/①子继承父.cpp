#include<iostream>

using namespace std;
/******************************************************************
①虚函数表是指一个类中存储的虚函数的地址
②虚函数表内存储的是函数指针,每个4个字节,需要用*取出其中的函数
③虚函数表内的函数优先按照子类内的排序
④多继承时子类中有多个虚函数表指针,需要分别取出
******************************************************************/
class A
{
	virtual void a()
	{
		cout << "A.a" << endl;
	}
	virtual void b()
	{
		cout << "A.b" << endl;
	}
};

class B :public A
{
	void a()
	{
		cout << "B.a" << endl;
	}
	void b()
	{
		cout << "B.b" << endl;
	}
	virtual void c()
	{
		cout << "B.c" << endl;
	}
};
typedef  void(*FUN)(void);
void mainA()
{
	A testa;
	B testb;
	cout << sizeof(testa) << " " << sizeof(testb) << endl;
	for (int i = 0; i < 3; i++)
	{
		FUN pfun = (FUN)*((int*)*(int*)(&testb)+i);
		pfun();
	}
	cin.get();
}