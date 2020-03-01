#include <iostream>
#include <list>
#include <string>
using namespace std;
//访问者模式：访问者模式的目的是封装一些施加于某种数据结构元素之上的操作。
//一旦这些操作需要修改的话，接受这个操作的数据结构可以保持不变。
//访问者模式适用于数据结构相对未定的系统，
//它把数据结构和作用于结构上的操作之间的耦合解脱开，
//使得操作集合可以相对自由的演化。访问者模式使得增加新的操作变的很容易，
//就是增加一个新的访问者类。
//访问者模式将有关的行为集中到一个访问者对象中，
//而不是分散到一个个的节点类中。当使用访问者模式时，
//要将尽可能多的对象浏览逻辑放在访问者类中，而不是放到它的子类中。
//访问者模式可以跨过几个类的等级结构访问属于不同的等级结构的成员类。
//



//访问者模式不需要改变基类，不依赖虚函数，


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
	list<Person*> persons;/*创造一个基类接口*/

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