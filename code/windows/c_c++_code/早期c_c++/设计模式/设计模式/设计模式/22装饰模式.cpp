#include <string>
#include <iostream>
using namespace std;

//装饰模式：装饰模式以对客户端透明的方式扩展对象的功能，
//是继承关系的一个替代方案，提供比继承更多的灵活性。
//动态给一个对象增加功能，这些功能可以再动态的撤消。
//增加由一些基本功能的排列组合而产生的非常大量的功能。


/*将一个类直接继承,并对其进行扩展,实现更多的功能*/
class Person
{
private:
	string m_strName;
public:
	Person(string strName)
	{
		m_strName = strName;
	}
	Person() {}
	virtual void show()
	{
		cout << "装扮的是:" << m_strName << endl;
	}
};

class Finery :public Person
{
protected:
	Person *m_component;
public:
	void decorate(Person* component)
	{
		m_component = component;
	}
	virtual void show()
	{
		m_component->show();
	}
};

class TShirts :public Finery
{
public:
	virtual void show()
	{
		m_component->show();
		cout << "T shirts" << endl;
	}
};

class BigTrouser :public Finery
{
public:
	virtual void show()
	{
		m_component->show();
		cout << "Big Trouser" << endl;
	}
};

int mainV()
{
	Person *p = new Person("小李");
	BigTrouser *bt = new BigTrouser();
	TShirts *ts = new TShirts();

	bt->decorate(p);
	ts->decorate(bt);
	ts->show();
	cin.get();
	return 0;
}
