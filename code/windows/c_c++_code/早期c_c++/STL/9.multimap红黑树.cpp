#include<iostream>
#include<map>
#include<string>


using namespace std;
struct student
{
	int age;
	string name;
	student()
	{

	}
	student(int valueage, string valuename) :age(valueage), name(valuename)
	{

	}
	void show()const
	{
		cout << age << " " << name << endl;
	}
	friend ostream &operator <<(ostream & out, student &it);
};

/*ostream &operator <<(ostream & out, student &it)
{
	out << it.age << " " << it.name;
	return out;
}*/
struct stuinfo
{
	int idinfo;
	student stu;
	stuinfo(int valueidinfo, student& valuestu) :idinfo(valueidinfo), stu(valuestu)
	{

	}
	stuinfo()
	{

	}
};

void main90()
{
	student peo1(19, "njh");
	student peo2(19, "xy");
	student peo3(19, "ghl");
	student peo4(19, "njh");
	stuinfo angong161[] =
	{
		{ 111,peo1 },
		{ 111,peo2 },
		{ 101,peo3 },
		{ 111,peo4 },
	};
	multimap<int, student> multi1;
	multi1.insert(pair<int, student>(111, peo1));
	multi1.insert(pair<int, student>(111, peo2));
	multi1.insert(pair<int, student>(101, peo3));
	multi1.insert(pair<int, student>(111, peo4));
	multi1.insert(pair<int, student>(115, peo4));
	for (auto ibegin = multi1.begin(); ibegin != multi1.end(); ibegin++)
	{
		cout << (*ibegin).first << " " << (*ibegin).second << endl;
	}
	cout << "****************" << endl;
	auto ifind = multi1.find(111);/*这里的find返回的是是map相关联的两个数据的类*/
	cout << (*ifind).first << endl;/* find返回的这个类  相当于是搜索数的链表第一个节点*/
	cout << (*ifind).second << endl;/*find返回的这个类  */
	cout << "****************" << endl;
	auto allfind = multi1.equal_range(111);/*这里的equal_range返回的是一个节点链表的头节点*/
	cout << (*allfind.first).first << " "<<(*allfind.first).second<<endl;
	cout << (*allfind.second).first << " " << (*allfind.second).second << endl;
	for (auto it = allfind.first; it!= allfind.second;it++)
	{
		cout << (*it).first << " " << (*it).second << endl;
	}
	cin.get();
}
/*map和multimap的迭代器有first和second,因为map关联了两种数据*/