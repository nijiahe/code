#include<iostream>
#include<set>/*multisetҲ��set�ļ���*/
#include<string>

using namespace std;

struct student
{
	int age;
	string name;
	student(int valueage, string valuename) :age(valueage), name(valuename)
	{

	}
	void show ()const
	{
		cout << age << " " << name << endl;
	}
};

struct ifless
{
	bool operator()(const student &s1, const student &s2) 
	{
		return s1.age < s2.age;
	}
};

void main70()
{
	multiset<student, ifless> grade1;
	student people1(9, "zzt");
	grade1.insert(people1);
	student people2(18, "ly");
	grade1.insert(people2);
	student people3(7, "njh");
	grade1.insert(people3);
	student people4(9, "zzt");
	grade1.insert(people4);
	student people5(18, "ly");
	grade1.insert(people5);
	student people6(7, "njh");
	grade1.insert(people6);
	student people7(9, "zzt");
	grade1.insert(people7);
	student people8(18, "ly");
	grade1.insert(people8);
	student people9(7, "njh");
	grade1.insert(people9);
	for (auto ibegin = grade1.begin(); ibegin != grade1.end(); ibegin++)
	{
		(*ibegin).show();
	}
	cin.get();
}

void main71()
{/*�ظ���Ԫ�����������ŵ�*/
	multiset<int> myset;
	myset.insert(100);
	myset.insert(101);
	myset.insert(100);
	myset.insert(103);
	myset.insert(100);
	/*����һ���ҵ���ֵ*/
	auto pfind = myset.find(101);/*findֻ���ҵ�һ��*/
	/*find���ص�ֵû�е�����*/
	cout << *pfind << endl;
	cout << "**************" << endl;
	/*���������ҵ���ֵ*/
	auto allfind = myset.equal_range(100);/*�ҵ�ȫ����ֵ*/
	cout << *(allfind.first) << endl;/*allfind.first����set�ڵ������ͷ�ڵ�*/
	cout << *(allfind.second) << endl;/*allfind.second������Ҫ���ҵ�ֵ������Ǹ�ֵ��ͷ�ڵ�*/
	cout << "**************" << endl;
	/*equal_range���ص�ֵ��һ�������ͷ�ڵ�,���ĵ������������������ǰ����*/
	for (auto it = allfind.first; it != allfind.second; it++)
	{
		cout << *it << endl;
	}
	cin.get();
}