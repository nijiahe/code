#include <iostream>
#include <string>
using namespace std;
//原型模式允许动态的增加或减少产品类，
//产品类不需要非得有任何事先确定的等级结构，
//原始模型模式适用于任何的等级结构。
//缺点是每一个类都必须配备一个克隆方法。

class Resume
{
private:
	string name, sex, age, timeArea, company;
public:
	Resume(string s)
	{
		name = s;
	}
	void setPersonalInfo(string s, string a)
	{
		sex = s;
		age = a;
	}
	void setWorkExperience(string t, string c)
	{
		timeArea = t;
		company = c;
	}
	void display()
	{
		cout << name << "  " << sex << "  " << age << endl;
		cout << "工作经历:  " << timeArea << "  " << company << endl << endl;

	}
	Resume *clone()
	{
		Resume *b;
		b = new Resume(name);
		b->setPersonalInfo(sex, age);
		b->setWorkExperience(timeArea, company);
		return b;
	}
};


int mainS()
{
	Resume *r = new Resume("李彦宏");
	r->setPersonalInfo("男", "30");
	r->setWorkExperience("2007-2010", "读研究生");
	r->display();


	Resume *r2 = r->clone();
	r2->setWorkExperience("2003-2007", "读本科");

	r->display();
	r2->display();

	cin.get();
	return 0;
}