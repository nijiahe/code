//#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS

#include<iostream>
//#include<hash_set>
#include<algorithm>
#include<string>
#include<unordered_map>

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
/*已经定义过了*/
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

void main110()
{
	student peo1(19, "njh");
	student peo2(19, "xy");
	student peo3(19, "ghl");
	student peo4(19, "njh");
	stuinfo angong161[] =
	{
		{ 111,peo1 },
		{ 112,peo2 },
		{ 101,peo3 },
		{ 111,peo4 },
	};
	/*student peo5(20, "hhh");
	stuinfo addangong(111, peo5);*/
	/*创建一个从idinfo到student的映射*/
	unordered_map<int, student> m;
	for (int i = 0; i < sizeof(angong161) / sizeof(stuinfo); i++)
	{
		m[angong161[i].idinfo] = angong161[i].stu;/*编号映射学生的信息*/
	}
	/*m[addangong.idinfo] = addangong.stu;/*map和set一样同一个id只能存储一个,如果一样会发生覆盖*/
	for (auto ibegin = m.begin(); ibegin != m.end(); ibegin++)
	{
		cout << (*ibegin).first << " " << (*ibegin).second << endl;
	}
	for (auto ibegin = m.begin(); ibegin != m.end(); ibegin++)
	{
		cout << m[(*ibegin).first] << endl;/*m将学生id映射到学生age、name,所以cout<<m[stuid]会输出学生的age、name*/
	}
	cin.get();
}