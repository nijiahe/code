#include<iostream>
#include<queue>
#include<string>

using namespace std;
/*���ȼ�����*/
/*���ȼ����л��Զ�����*/
void main50()
{
	priority_queue<int> myq;
	myq.push(5);
	myq.push(9);
	myq.push(7);
	myq.push(3);
	myq.push(6);
	while (!myq.empty())
	{
		cout << myq.top()<<" ";
		myq.pop();
	}
	cin.get();
}
/*tmeplate<typename T>
priority_queue<T,vector<T>,���з���*/
struct student
{
	int age;
	string name;
	student(int valueage, string valuename):age(valueage),name(valuename)
	{

	}
	void show()
	{
		cout << age << " " << name << endl;
	}
};
struct ifless
{
	bool operator()(const student &s1, const student &s2) const
	{
		return s1.age < s2.age;
	}
};
/*���ȼ��������򷽷��Զ��巽��*/
/**/
void main51()
{
	/*���ݵ���������<�����е�Ԫ��,���б�����ʽ,����ȽϷ���������*/
	priority_queue<student, vector<student>, ifless> grade;
	student people1(9,"zzt");
	grade.push(people1);
	student people2(18, "ly");
	grade.push(people2);
	student people3(7, "njh");
	grade.push(people3);
	while (!grade.empty())
	{
		cout << grade.top().age << " " << grade.top().name << endl;
		grade.pop();
	}
	cin.get();
}