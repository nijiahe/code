#include<iostream>
/*RALL���Ʊ���ͨ�����ö�����Զ�����,ʹ����ԴҲ��������������,�����Զ�����(�Զ�����)�Ĺ��ܡ� �����������ָ��,lock_guard��������RALL������ʵ��*/
using namespace std;

class mystr
{
public:
	char* p = nullptr;
public:
	mystr(const char*str)
	{
		cout << "����" << endl;
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

/*��ָ���װ��һ����,����Զ�������������,���������ڵ����Զ�����
������ָ��*/


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