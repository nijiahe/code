#include<iostream>
#include<vector>
#include<algorithm>/*�㷨ͷ�ļ�*/
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
	/*for_each��һ���㷨,���㷨ͷ�ļ���*/
	for_each(vec1.begin(), vec1.end(), pint);/*�൱�ڱ����������,����������pint�ĺ�����������*/
	cin.get();
}
/*set*//*���ʺ����*/
/*set���ܳ����ظ�������,��ֻ���¼һ��*/
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