#include <iostream>
#include <string>
using namespace std;
//����ģʽ������ģʽȷ��ĳһ����ֻ��һ��ʵ����
//��������ʵ������������ϵͳ�ṩ���ʵ������ģʽ
//������ģʽֻӦ���������ġ���һʵ����������ʱ�ſ�ʹ�á�
//


//#define  public private 

class//��������1  ������
{
public:
protected:
private:
}a1;

class Singleton//��������2  ˽�еĹ��캯��
{
private:
	int i;
	static Singleton *instance;//����Ǹ���̬����,����ʱ�ʹ���
	Singleton(int i)
	{
		this->i = i;
	}
public:
	static Singleton *getInstance()
	{
		return instance;
	}
	void show()
	{
		cout << i << endl;
	}
};
Singleton* Singleton::instance = new Singleton(8899);

class A :public Singleton
{

};

int mainG()
{
	Singleton *s = Singleton::getInstance();
	Singleton *s2 = A::getInstance();
	cout << (s == s2) << endl;//��ͬ
	cin.get();
	return 0;
}