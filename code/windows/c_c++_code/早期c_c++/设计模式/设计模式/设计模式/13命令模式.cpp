#include <iostream>
#include <string>
#include <list>
//命令模式：命令模式把一个请求或者操作封装到一个对象中。
//命令模式把发出命令的责任和执行命令的责任分割开，委派给不同的对象。
//命令模式允许请求的一方和发送的一方独立开来，
//使得请求的一方不必知道接收请求的一方的接口，
//更不必知道请求是怎么被接收，
//以及操作是否执行，何时被执行以及是怎么被执行的。
//系统支持命令的撤消。

using namespace std;

class Barbecuer  //这里存储所有可以执行的命令,用于传递命令
{
public:
	void bakeMutton()
	{
		cout << "烤羊肉串" << endl;
	}
	void bakeChickenWing()
	{
		cout << "烤鸡翅" << endl;
	}
};

class Command   //接受命令的抽象类
{
protected:
	Barbecuer *receiver;//类的包含
public:
	Command(Barbecuer *receiver)//命令接受
	{
		this->receiver = receiver;
	}
	virtual void executeCommand() = 0;
};

class BakeMuttonCommand :public Command  //这个类接收命令之后可以执行命令中的bakeMutton命令
{
public:
	BakeMuttonCommand(Barbecuer *receiver) :Command(receiver)
	{}
	void executeCommand()
	{
		receiver->bakeMutton();
	}
};

class BakeChikenWingCommand :public Command  //这个类接收命令之后可以执行命令中的bakeChickenWing命令
{
public:
	BakeChikenWingCommand(Barbecuer *receiver) :Command(receiver)
	{}
	void executeCommand()
	{
		receiver->bakeChickenWing();
	}
};

class Waiter        //服务员  用于管理接收命令的类  调用其使其执行
{
private:
	Command *command;
public:
	void setOrder(Command *command)
	{
		this->command = command;
	}
	void notify()
	{
		command->executeCommand();
	}
};

class Waiter2   //用于管理多个接受了命令的类 调用其使其执行
{
private:
	list<Command*> orders;
public:
	void setOrder(Command *command)
	{
		orders.push_back(command);
	}
	void cancelOrder(Command *command)
	{
		orders.remove(command);
	}
	void notify()
	{
		list<Command*>::iterator iter = orders.begin();
		while (iter != orders.end())
		{
			(*iter)->executeCommand();
			iter++;
		}
	}
};


int mainM()
{
	Barbecuer *boy = new Barbecuer();
	Command *bm1 = new BakeMuttonCommand(boy);
	Command *bm2 = new BakeMuttonCommand(boy);
	Command *bc1 = new BakeChikenWingCommand(boy);

	Waiter2 *girl = new Waiter2();

	girl->setOrder(bm1);
	girl->setOrder(bm2);
	girl->setOrder(bc1);

	girl->notify();


	cin.get();

	return 0;
}