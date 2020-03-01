#include<iostream>

/*策略模式通过一个共同接口,继承这个接口分别实现不同的模式*/
/*依赖于纯虚函数*/
using namespace std;

class cashget
{
	virtual double getmoney(double money) = 0;
	friend class getmoneystyle;
};


class normalgetmoney:public cashget
{
public:
	double getmoney(double money)
	{
		return money;
	}
};

class onsalegetmoney:public cashget
{
	double discounts;//折扣度
public:
	onsalegetmoney(double discounts):discounts(discounts)
	{

	}
	double getmoney(double money)
	{
		return money*discounts;
	}
};

class fullminusgetmoney:public cashget
{
	double fullmoney;
	double minusmoney;
public:
	fullminusgetmoney(double fullmoney, double minusmoney)
		:fullmoney(fullmoney), minusmoney(minusmoney)
	{

	}
	double getmoney(double money)
	{
		if (money >= fullmoney)
		{
			return money - minusmoney;
		}
		return money;
	}
};

class getmoneystyle
{
	cashget* style;
public:
	getmoneystyle()
	{
		style = new normalgetmoney();
	}
	getmoneystyle(double discount)
	{
		style = new onsalegetmoney(discount);
	}
	getmoneystyle(int fullmoney, int minusmoney)
	{
		style = new fullminusgetmoney(fullmoney, minusmoney);
	}
	double getmoney(double money)
	{
		return style->getmoney(money);
	}
};
void mainB()
{
	getmoneystyle style1;
	cout << style1.getmoney(1000) << endl;

	getmoneystyle style2(0.8);
	cout << style2.getmoney(1000) << endl;

	getmoneystyle style3(900,500);
	cout << style3.getmoney(1000) << endl;

	cin.get();
}