#include <iostream>
#include <string>
using namespace std;
//单例模式：单例模式确保某一个类只有一个实例，
//而且自行实例化并向整个系统提供这个实例单例模式
//。单例模式只应在有真正的“单一实例”的需求时才可使用。
//


//#define  public private 

class//单例方法1  匿名类
{
public:
protected:
private:
}a1;

class Singleton//单例方法2  私有的构造函数
{
private:
	int i;
	static Singleton *instance;//这个是个静态变量,编译时就存在
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
	cout << (s == s2) << endl;//相同
	cin.get();
	return 0;
}