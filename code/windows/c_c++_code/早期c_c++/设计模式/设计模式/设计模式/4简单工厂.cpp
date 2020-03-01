#include <iostream>
#include <string>
using namespace std;


//��һ������������
//�ڶ����������кܶ࣬�����������ݵĲ���
//����ʵ�ֽӿ��࣬�þ�̬����ʵ�ֵ��ø���������

/*ͬһ���û��в�ͬ������,��ͬһ�������ﱻ���*/
class Operation    //����������
{
public:
	double numberA, numberB;//������
	virtual double  getResult()//��ȡ���
	{
		return 0;
	}
};

class addOperation :public Operation//�������Ų���
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

class operFactory //ʵ�ֵ��øĸ��Ŷ����
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