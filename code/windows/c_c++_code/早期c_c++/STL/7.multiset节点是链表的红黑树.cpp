#include<iostream>
#include<set>/*multiset也在set文件下*/
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
{/*重复的元素是用链表存放的*/
	multiset<int> myset;
	myset.insert(100);
	myset.insert(101);
	myset.insert(100);
	myset.insert(103);
	myset.insert(100);
	/*返回一个找到的值*/
	auto pfind = myset.find(101);/*find只能找到一个*/
	/*find返回的值没有迭代器*/
	cout << *pfind << endl;
	cout << "**************" << endl;
	/*返回所有找到的值*/
	auto allfind = myset.equal_range(100);/*找到全部的值*/
	cout << *(allfind.first) << endl;/*allfind.first代表set节点链表的头节点*/
	cout << *(allfind.second) << endl;/*allfind.second是排在要查找的值下面的那个值的头节点*/
	cout << "**************" << endl;
	/*equal_range返回的值是一个链表的头节点,他的迭代器是在这个链表上前进的*/
	for (auto it = allfind.first; it != allfind.second; it++)
	{
		cout << *it << endl;
	}
	cin.get();
}