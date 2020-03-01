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
	c表示container,是关联容器
	c.find(x)寻找第一个找到的关键字为x的元素,返回其迭代器,若未找到,则返回尾后迭代器
	c.count(x)返回容器内所有关键字为x的元素的数量,对于不可重复容器,其返回值总是0或1
	c.lower_bound(x)返回容器中第一个key不小于x的元素,即若容器中有x,则返回一个指向x开始处的迭代器
	c.upper_bound(x)返回容器中第一个key大于x的元素,即若容器中有x,则返回一个指向x结尾后一个的迭代器
	c.equal_range(x)返回std::pair<iterator1,iterator2>类型,表示x的元素的范围,若x不存在,则两个迭代器都是c.end()
	注:在map,set的红黑树中,相同关键字的元素会被相邻存储,所以equal_range得以奏效
	*/

//练习题:
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
		//注:这里精妙绝伦,利用下标返回second值的方法,这里利用order_author的std::string返回其std::multiset,在将作品插入multiset中
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