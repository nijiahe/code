#include<iostream>

using namespace std;

class F
{
	virtual void a()
	{
		cout << "F.a" << endl;
	}
	virtual void b()
	{
		cout << "F.b" << endl;
	}
};

class G
{
	virtual void a()
	{
		cout << "G.a" << endl;
	}
	virtual void c()
	{
		cout << "G.c" << endl;
	}
};

class H : public G,public F
{
	
};

typedef void(*FUN)(void);

void main()
{
	F testf;
	G testg;
	H testh;
	cout << sizeof(testh) << endl;
	//调用testh的第一个虚函数表
	for (int i = 0; i < 2; i++)
	{
		FUN pfun = (FUN)*((int*)*(int*)(&testh) + i);
		pfun();
	}
	cout << "**************************" << endl;
	//用循环调用testh的所有虚函数表
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			FUN pfun = (FUN)*((int*)*((int*)(&testh)+i)  + j);
			pfun();
		}
	}


	cin.get();
}