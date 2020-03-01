#include <iostream>
#include <string>
using namespace std;


//第一，基类存放数据
//第二，派生类有很多，派生类存放数据的操作
//第三实现接口类，用静态函数实现调用各种派生类

/*同一个用户有不同的需求,在同一个工厂里被完成*/
class Operation    //基类存放数据
{
public:
	double numberA, numberB;//两个数
	virtual double  getResult()//获取结果
	{
		return 0;
	}
};

class addOperation :public Operation//派生类存放操作
{
	double getResult()
	{
		return numberA + numberB;
	}
};


class subOperation :public Operation
{
	double getResult()
	{
		return numberA - numberB;
	}
};

class mulOperation :public Operation
{
	double getResult()
	{
		return numberA*numberB;
	}
};

class divOperation :public Operation
{
	double getResult()
	{
		return numberA / numberB;
	}
};

class operFactory //实现调用改革吃哦啊做
{
public:
	static Operation *createOperation(char c)
	{
		switch (c)
		{
		case '+':
			return new addOperation;
			break;

		case '-':
			return new subOperation;
			break;

		case '*':
			return new mulOperation;
			break;

		case '/':
			return new divOperation;
			break;
		}
		return nullptr;
	}
};

int mainD()
{
	Operation *oper = operFactory::createOperation('-');
	oper->numberA = 9;
	oper->numberB = 99;
	cout << oper->getResult() << endl;

	cin.get();
	return 0;
}