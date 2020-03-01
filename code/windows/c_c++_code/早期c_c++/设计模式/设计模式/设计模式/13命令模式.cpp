#include <iostream>
#include <string>
#include <list>
//����ģʽ������ģʽ��һ��������߲�����װ��һ�������С�
//����ģʽ�ѷ�����������κ�ִ����������ηָ��ί�ɸ���ͬ�Ķ���
//����ģʽ���������һ���ͷ��͵�һ������������
//ʹ�������һ������֪�����������һ���Ľӿڣ�
//������֪����������ô�����գ�
//�Լ������Ƿ�ִ�У���ʱ��ִ���Լ�����ô��ִ�еġ�
//ϵͳ֧������ĳ�����

using namespace std;

class Barbecuer  //����洢���п���ִ�е�����,���ڴ�������
{
public:
	void bakeMutton()
	{
		cout << "�����⴮" << endl;
	}
	void bakeChickenWing()
	{
		cout << "������" << endl;
	}
};

class Command   //��������ĳ�����
{
protected:
	Barbecuer *receiver;//��İ���
public:
	Command(Barbecuer *receiver)//�������
	{
		this->receiver = receiver;
	}
	virtual void executeCommand() = 0;
};

class BakeMuttonCommand :public Command  //������������֮�����ִ�������е�bakeMutton����
{
public:
	BakeMuttonCommand(Barbecuer *receiver) :Command(receiver)
	{}
	void executeCommand()
	{
		receiver->bakeMutton();
	}
};

class BakeChikenWingCommand :public Command  //������������֮�����ִ�������е�bakeChickenWing����
{
public:
	BakeChikenWingCommand(Barbecuer *receiver) :Command(receiver)
	{}
	void executeCommand()
	{
		receiver->bakeChickenWing();
	}
};

class Waiter        //����Ա  ���ڹ�������������  ������ʹ��ִ��
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

class Waiter2   //���ڹ������������������ ������ʹ��ִ��
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