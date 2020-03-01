#include<iostream>
/*RALL机制便是通过利用对象的自动销毁,使得资源也具有了生命周期,有了自动销毁(自动回收)的功能。 更多的如智能指针,lock_guard都利用了RALL机制来实现*/
using namespace std;

class mystr
{
public:
	char* p = nullptr;
public:
	mystr(const char*str)
	{
		cout << "销毁" << endl;
		int length = strlen(str);
		p = new char[length + 1];
		strcpy_s(p,length+1,str);
	}
	~mystr()
	{
		delete[]p;
	}
};

void go()
{
	char* p = new char[100];
	mystr str1 = "ABCD";
}


void mainG()
{
	cin.get();
}

/*将指针包装成一个类,类会自动调用析构函数,即生命周期到了自动销毁
即智能指针*/


template<class T>
class pmy
{
public:
	pmy()
	{

	}
	pmy(T* t)
	{
		p = t;
	}
	~pmy()
	{
		if (p != nullptr)
		{
			delete p;
		}
	}
private:
	T* p = nullptr;
};

class Test
{
public:
	Test()
	{
		cout << "Test create" << endl;
	}
	~Test()
	{
		cout << "Test delete" << endl;
	}
};
void run()
{
	pmy<Test>p(new Test);
}

void mainH()
{
	run();
	cin.get();
}