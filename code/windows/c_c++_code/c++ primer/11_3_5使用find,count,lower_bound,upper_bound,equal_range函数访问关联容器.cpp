#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <iterator>
#include <cstdlib>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <utility>


int main11_3_5()
{
	/*
	c��ʾcontainer,�ǹ�������
	c.find(x)Ѱ�ҵ�һ���ҵ��Ĺؼ���Ϊx��Ԫ��,�����������,��δ�ҵ�,�򷵻�β�������
	c.count(x)�������������йؼ���Ϊx��Ԫ�ص�����,���ڲ����ظ�����,�䷵��ֵ����0��1
	c.lower_bound(x)���������е�һ��key��С��x��Ԫ��,������������x,�򷵻�һ��ָ��x��ʼ���ĵ�����
	c.upper_bound(x)���������е�һ��key����x��Ԫ��,������������x,�򷵻�һ��ָ��x��β��һ���ĵ�����
	c.equal_range(x)����std::pair<iterator1,iterator2>����,��ʾx��Ԫ�صķ�Χ,��x������,����������������c.end()
	ע:��map,set�ĺ������,��ͬ�ؼ��ֵ�Ԫ�ػᱻ���ڴ洢,����equal_range������Ч
	*/

//��ϰ��:
	std::multimap<std::string, std::string> mmap{
		{"Nijiahe","The art of programing the world"},
		{"Nijiahe","The art of craking oteration system"},
		{"Nijiahe","The art of Universe's algorithm"},
		{"Evil","Life's circulation"} };
	std::for_each(mmap.begin(), mmap.end(), [](std::pair<std::string, std::string> pair) 
	{std::cout << pair.first << ":" << pair.second << std::endl; });
	std::cout << std::endl;
	mmap.erase(mmap.lower_bound("Nijiahe"),mmap.upper_bound("Nijiahe"));
	std::for_each(mmap.begin(), mmap.end(), [](std::pair<std::string, std::string> pair)
	{std::cout << pair.first << ":" << pair.second << std::endl; });
	std::cout << std::endl;

	std::multimap<std::string,std::string> authors{
		{ "alan", "DMA" },
		{ "pezy", "LeetCode" },
		{ "alan", "CLRS" },
		{ "wang", "FTP" },
		{ "pezy", "CP5" },
		{ "wang", "CPP-Concurrency"}};
	std::map<std::string, std::multiset<std::string> > order_authors;
	for (std::pair<std::string, std::string> pair : authors)
		//ע:���ﾫ�����,�����±귵��secondֵ�ķ���,��������order_author��std::string������std::multiset,�ڽ���Ʒ����multiset��
		order_authors[pair.first].insert(pair.second);

	for (std::pair<std::string, std::multiset<std::string> >pair : order_authors)
	{
		std::cout << pair.first << ":" << std::endl;
		for (std::string str : pair.second)
			std::cout << "	" << str << std::endl;
	}

	system("pause");
	return 0;
}