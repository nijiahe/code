#include <iostream>
#include <string>
using namespace std;


//工厂方法模式：核心工厂类不再负责所有产品的创建，
//而是将具体创建的工作交给子类去做，成为一个抽象工厂角色
//，仅负责给出具体工厂类必须实现的接口，
//而不接触哪一个产品类应当被实例化这种细节。

//将一个方法对应一个工厂,实现扩展

/*同一个用户有不同的需求,在不同的工厂里被完成*/
class Operation//方法的抽象
{
public:
	double numberA, numberB;
	virtual double  getResult()//
	{
		return 0;
	}
};

class addOperation :public Operation// +  方法
{
	double getResult()
	{
		return numberA + numberB;
	}
};


class subOperation :public Operation// -  方法
{
	double getResult()
	{
		return numberA - numberB;
	}
};

class mulOperation :public Operation// *  方法
{
	double getResult()
	{
		return numberA*numberB;
	}
};

class divOperation :public Operation//  /  方法
{
	double getResult()
	{
		return numberA / numberB;
	}
};

class IFactory//工厂的抽象
{
public:
	virtual Operation *createOperation() = 0;
};


class AddFactory :public IFactory
{
public:
	static Operation *createOperation()
	{
		return new addOperation();
	}
};


class SubFactory :public IFactory
{
public:
	static Operation *createOperation()
	{
		return new subOperation();
	}
};

class MulFactory :public IFactory
{
public:
	static Operation *createOperation()
	{
		return new mulOperation();
	}
};

class DivFactory :public IFactory
{
public:
	static Operation *createOperation()
	{
		return new divOperation();
	}
};

int mainE()
{
	Operation *oper = MulFactory::createOperation();
	oper->numberA = 9;
	oper->numberB = 99;
	cout << oper->getResult() << endl;
	cin.get();
	return 0;
}