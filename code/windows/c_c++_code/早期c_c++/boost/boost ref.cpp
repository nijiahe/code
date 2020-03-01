#include<iostream>
#include<boost\bind.hpp>
#include<boost\function.hpp>
#include<boost\ref.hpp>
#include<vector>

using namespace std;

void print(ostream &os,int i)
{
	os << i << endl;
}

void mainF()
{//�˴�bind�������ص���һ��print������һ��������Ϊcout�ĺ���
	boost::function<void(int)> func = boost::bind(print, boost::ref(cout), _1);
	vector<int>vec;
	vec.push_back(11);
	vec.push_back(22);
	vec.push_back(33);
	vec.push_back(44);
	for_each(vec.begin(), vec.end(), func);
	cin.get();
}