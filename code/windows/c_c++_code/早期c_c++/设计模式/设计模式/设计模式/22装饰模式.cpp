#include <string>
#include <iostream>
using namespace std;

//װ��ģʽ��װ��ģʽ�ԶԿͻ���͸���ķ�ʽ��չ����Ĺ��ܣ�
//�Ǽ̳й�ϵ��һ������������ṩ�ȼ̳и��������ԡ�
//��̬��һ���������ӹ��ܣ���Щ���ܿ����ٶ�̬�ĳ�����
//������һЩ�������ܵ�������϶������ķǳ������Ĺ��ܡ�


/*��һ����ֱ�Ӽ̳�,�����������չ,ʵ�ָ���Ĺ���*/
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
		cout << "װ�����:" << m_strName << endl;
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
	Person *p = new Person("С��");
	BigTrouser *bt = new BigTrouser();
	TShirts *ts = new TShirts();

	bt->decorate(p);
	ts->decorate(bt);
	ts->show();
	cin.get();
	return 0;
}
