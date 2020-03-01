#include<iostream>

using namespace std;

class C
{
	virtual void A()
	{
		cout << "C.a" << endl;
	}
	virtual void B()
	{
		cout << "C.b" << endl;
	}
};
class D:public C
{
	void B()
	{
		cout << "D.b" << endl;
	}
	virtual void C()
	{
		cout << "D.c" << endl;
	}
};
class E :public D
{
	void A()
	{
		cout << "E.a" << endl;
	}
	void C()
	{
		cout << "E.c" << endl;
	}
};


typedef void(*FUN)(void);

void mainB()
{
	C testc;
	D testd;
	E teste;
	for (int i = 0; i < 2; i++)
	{
		FUN pfun = (FUN)*((int*)*(int*)(&testc) + i);
		pfun();
	}
	cout << "*****************" << endl;
	for (int i = 0; i < 3; i++)
	{
		FUN pfun = (FUN)*((int*)*(int*)(&testd) + i);
		pfun();
	}
	cout << "*****************" << endl;
	for (int i = 0; i < 3; i++)
	{
		FUN pfun = (FUN)*((int*)*(int*)(&teste) + i);
		pfun();
	}
	cout << "*****************" << endl;



	cin.get();
}