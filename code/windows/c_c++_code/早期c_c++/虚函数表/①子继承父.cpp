#include<iostream>

using namespace std;
/******************************************************************
���麯������ָһ�����д洢���麯���ĵ�ַ
���麯�����ڴ洢���Ǻ���ָ��,ÿ��4���ֽ�,��Ҫ��*ȡ�����еĺ���
���麯�����ڵĺ������Ȱ��������ڵ�����
�ܶ�̳�ʱ�������ж���麯����ָ��,��Ҫ�ֱ�ȡ��
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