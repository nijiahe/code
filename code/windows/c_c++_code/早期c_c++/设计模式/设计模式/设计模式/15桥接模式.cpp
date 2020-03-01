#include <iostream>
#include <string>
using namespace std;
//桥梁模式：将抽象化与实现化脱耦，使得二者可以独立的变化，

//也就是说将他们之间的强关联变成弱关联，

//也就是指在一个软件系统的抽象化和实现化之间使用组合 

/// 聚合关系而不是继承关系，从而使两者可以独立的变化。


//将功能抽象化,将调用功能的接口也抽象化,这样可以实现一个接口调用很多功能
class HandsetSoft
{
public:
	virtual void run() = 0;
};

class HandsetGame :public HandsetSoft
{
public:
	void run()
	{
		cout << "运行手机游戏" << endl;
	}
};

class HandsetAddressList :public HandsetSoft
{
public:
	void run()
	{
		cout << "运行手机通讯录" << endl;
	}
};
/*软件搭配硬件*/
class HandsetBrand
{
protected:
	HandsetSoft *soft;
public:
	void setHandsetSoft(HandsetSoft *soft)
	{
		this->soft = soft;
	}
	virtual void run() = 0;
};

class HandsetBrandN :public HandsetBrand
{
public:
	void run()
	{
		soft->run();
	}
};

class HandsetBrandM :public HandsetBrand
{
public:
	void run()
	{
		soft->run();
	}
};

int mainO()
{
	HandsetBrand *hb;
	hb = new HandsetBrandM();

	hb->setHandsetSoft(new HandsetGame());
	hb->run();
	hb->setHandsetSoft(new HandsetAddressList());
	hb->run();

	cin.get();
	return 0;
}