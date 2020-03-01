#include<iostream>
#include<queue>
#include<string>

using namespace std;
/*优先级队列*/
/*优先级队列会自动排序*/
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
priority_queue<T,vector<T>,排列方法*/
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
/*优先级队列排序方法自定义方法*/
/**/
void main51()
{
	/*传递的三个参数<队列中的元素,队列保存样式,排序比较方法的类名*/
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