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

ostream &operator <<(ostream & out, student &it)
{
	out << it.age << " " << it.name;
	return out;
}
struct stuinfo
{
	int idinfo;
	student stu;
	stuinfo(int valueidinfo, student& valuestu):idinfo(valueidinfo), stu(valuestu)
	{

	}
	stuinfo()
	{

	}
};

void main80()
{
	student peo1(19, "njh") ;
	student peo2(19, "xy") ;
	student peo3(19, "ghl") ;
	student peo4(19, "njh") ;
	stuinfo angong161[] = 
	{ 
		{111,peo1 },
		{ 112,peo2 }, 
		{ 101,peo3 }, 
		{ 111,peo4 }, 
	};
	/*student peo5(20, "hhh");
	stuinfo addangong(111, peo5);*/
	/*����һ����idinfo��student��ӳ��*/
	map<int, student> m;	
	for (int i = 0; i < sizeof(angong161) / sizeof(stuinfo); i++)
	{
		m[angong161[i].idinfo] = angong161[i].stu;/*���ӳ��ѧ������Ϣ*/
	}
	/*m[addangong.idinfo] = addangong.stu;/*map��setһ��ͬһ��idֻ�ܴ洢һ��,���һ���ᷢ������*/
	for (auto ibegin = m.begin(); ibegin != m.end(); ibegin++)
	{
		cout << (*ibegin).first << " " << (*ibegin).second << endl;
	}
	for (auto ibegin = m.begin(); ibegin != m.end(); ibegin++)
	{
		cout << m[(*ibegin).first] << endl;/*m��ѧ��idӳ�䵽ѧ��age��name,����cout<<m[stuid]�����ѧ����age��name*/
	}
	cin.get();
}

void main1111()
{
	/*map�������ӵķ�ʽinsert���з�ʽ�����Ⱥ�˳��*/
	map<const char *, int> mymap;
	mymap["˾��"] = 10;//ӳ�� ,�Եȵ�ӳ�����
	mymap["����"] = 9;
	mymap["ʦ��"] = 8;
	mymap["�ó�"] = 7;

	/*cout << mymap["˾��"] << endl;
	cout << mymap["����"] << endl;
	cout << mymap["ʦ��"] << endl;
	cout << mymap["�ó�"] << endl;*/
	for (auto ibegin = mymap.begin(); ibegin != mymap.end(); ibegin++)
	{
		cout << (*ibegin).first << endl;
	}
	std::cin.get();
}
/*map��multimap�ĵ�������first��second,��Ϊmap��������������*/