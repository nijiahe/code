//#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS

#include<iostream>
//#include<hash_set>
#include<algorithm>
#include<string>
#include<unordered_set>
using namespace std;
/*ʵ�ʺ�set�����һ��,ֻ�Ǽ���|���е�ʱ����hash�㷨����*/
void main100()
{
	const char *cmd[] = { "abc","calc","notepad","xyz","ghj" };
	unordered_set<const char*> hs;/*c++11��hash_set���ַ���������,�����Լ�����*/
	for (int i = 0; i < sizeof(cmd) / sizeof(char*); i++)
	{
		hs.insert(cmd[i]);
	}
	auto ifind = hs.find("abc");
	cout << *ifind << endl;
	cin.get();
}