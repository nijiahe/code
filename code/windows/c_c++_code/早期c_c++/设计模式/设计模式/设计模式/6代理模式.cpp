#include <iostream>
#include <string>
using namespace std;
//代理模式：代理模式给某一个对象提供一个代理对象，
//并由代理对象控制对源对象的引用。
//代理就是一个人或一个机构代表另一个人或者一个机构采取行动。
//某些情况下，客户不想或者不能够直接引用一个对象，
//代理对象可以在客户和目标对象直接起到中介的作用。
//客户端分辨不出代理主题对象与真实主题对象。
//代理模式可以并不知道真正的被代理对象，
//而仅仅持有一个被代理对象的接口，这时候代理对象不能够创建被代理对象，
//被代理对象必须有系统的其他角色代为创建并传入。

class SchoolGirl
{
public:
	string name;
};


class IGiveGift
{
public:
	virtual void giveDolls() = 0;
	virtual void giveFlowers() = 0;
};

class Pursuit :public IGiveGift
{
private:
	SchoolGirl mm;
public:
	Pursuit(SchoolGirl m)
	{
		mm = m;
	}
	void giveDolls()
	{
		cout << mm.name << " 送你娃娃" << endl;
	}
	void giveFlowers()
	{
		cout << mm.name << " 送你鲜花" << endl;
	}
};

class Proxy :public IGiveGift//包含上面的类,实现用这个类完成上面这个类要做的事,从而隐藏上面那个类
{
private:
	Pursuit gg;
public:
	Proxy(SchoolGirl mm) :gg(mm)
	{
		//gg=g;
	}
	void giveDolls()
	{
		gg.giveDolls();
	}
	void giveFlowers()
	{
		gg.giveFlowers();
	}
};

int mainF()
{
	SchoolGirl lijiaojiao;
	lijiaojiao.name = "李娇娇";
	Pursuit zhuojiayi(lijiaojiao);
	Proxy daili(lijiaojiao);

	daili.giveDolls();
	cin.get();
	return 0;
}