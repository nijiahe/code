#include <iostream>
#include <list>
#include <string>
using namespace std;
//������ģʽ��������ģʽ��Ŀ���Ƿ�װһЩʩ����ĳ�����ݽṹԪ��֮�ϵĲ�����
//һ����Щ������Ҫ�޸ĵĻ�������������������ݽṹ���Ա��ֲ��䡣
//������ģʽ���������ݽṹ���δ����ϵͳ��
//�������ݽṹ�������ڽṹ�ϵĲ���֮�����Ͻ��ѿ���
//ʹ�ò������Ͽ���������ɵ��ݻ���������ģʽʹ�������µĲ�����ĺ����ף�
//��������һ���µķ������ࡣ
//������ģʽ���йص���Ϊ���е�һ�������߶����У�
//�����Ƿ�ɢ��һ�����Ľڵ����С���ʹ�÷�����ģʽʱ��
//Ҫ�������ܶ�Ķ�������߼����ڷ��������У������Ƿŵ����������С�
//������ģʽ���Կ��������ĵȼ��ṹ�������ڲ�ͬ�ĵȼ��ṹ�ĳ�Ա�ࡣ
//



//������ģʽ����Ҫ�ı���࣬�������麯����


class Person
{
public:
	char * action;
	virtual void getConclusion()
	{

	};
};


class Man :public Person
{
public:

	void getConclusion()
	{
		if (action == "shuai")
		{
			cout << "thank" << endl;
		}
		else if (action == "mei")
		{
			cout << "gun" << endl;
		}
	}
};

class Woman :public Person
{
public:

	void getConclusion()
	{
		if (action == "shuai")
		{
			cout << "gun" << endl;
		}
		else if (action == "mei")
		{
			cout << "thanks" << endl;
		}
	}
};

int mainI()
{
	list<Person*> persons;/*����һ������ӿ�*/

	Person *man1 = new Man();
	man1->action = "shuai";
	persons.push_back(man1);

	Person *woman1 = new Woman();
	woman1->action = "shuai";
	persons.push_back(woman1);

	Person *man2 = new Man();
	man2->action = "mei";
	persons.push_back(man2);

	Person *woman2 = new Woman();
	woman2->action = "mei";
	persons.push_back(woman2);

	list<Person*>::iterator iter = persons.begin();
	while (iter != persons.end())
	{
		(*iter)->getConclusion();
		++iter;
	}

	cin.get();
	return 0;
}