#include<iostream>
#include<vector>
#include<algorithm>/*算法头文件*/
#include<set>
using namespace std;


template<class T>
class myprint
{
public:
	void operator ()(const T &it)
	{
		cout << it << endl;
	}
};
void main01()
{
	vector<int> vec1;
	vec1.push_back(11);
	vec1.push_back(22);
	vec1.push_back(33);
	vec1.push_back(44);
	vec1.push_back(55);
	myprint<int> pint;
	/*for_each是一个算法,在算法头文件中*/
	for_each(vec1.begin(), vec1.end(), pint);/*相当于遍历这个数组,并把他当成pint的函数参数传递*/
	cin.get();
}
/*set*//*本质红黑树*/
/*set不能出现重复的数据,它只会记录一个*/
void main02()
{
	set<int> tree1;
	tree1.insert(10);
	tree1.insert(10);
	tree1.insert(10);
	tree1.insert(10);
	tree1.insert(10);
	tree1.insert(10);
	myprint<int> pint;
	for_each(tree1.begin(), tree1.end(), pint);
	cin.get();
}
/*multiset*/
void main03()
{
	multiset<int> multitree1;
	multitree1.insert(1);
	multitree1.insert(1);
	multitree1.insert(2);
	multitree1.insert(6);
	multitree1.insert(5);
	multitree1.insert(7);
	multitree1.insert(3);
	multitree1.insert(2);
	myprint<int> pint;
	for_each(multitree1.begin(), multitree1.end(), pint);
	cin.get();
}