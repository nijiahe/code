//#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS

#include<iostream>
//#include<hash_set>
#include<algorithm>
#include<string>
#include<unordered_set>
using namespace std;
/*实质和set红黑树一样,只是检索|排列的时候用hash算法检索*/
void main100()
{
	const char *cmd[] = { "abc","calc","notepad","xyz","ghj" };
	unordered_set<const char*> hs;/*c++11的hash_set有字符串的排列,不用自己定义*/
	for (int i = 0; i < sizeof(cmd) / sizeof(char*); i++)
	{
		hs.insert(cmd[i]);
	}
	auto ifind = hs.find("abc");
	cout << *ifind << endl;
	cin.get();
}