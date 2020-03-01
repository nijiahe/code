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


int main11_3_2()
{
	/*
	std::map<std::string, int> map;
	std::string words;
	while (std::cin >> words)
	{
		//注:不可重复关联容器插入相同的关键字时,insert函数什么也不会做,返回std::pair类型的迭代器,里面的second成员保存的是false
		//返回的std::pair类型的first成员是指向具有指定关键字元素的迭代器
		//而可重复关联容器返回一个指向插入元素的迭代器,即不重复容器返回的std::pair类型的first成员变量
		std::pair<std::map<std::string, int>::iterator, bool> pair = map.insert(std::make_pair(words,1));
		if (!pair.second)
			++pair.first->second;
	}
	std::for_each(map.begin(), map.end(), [](std::pair<std::string, int> pair)
	{ std::cout << pair.first << ":" << pair.second << std::endl; });
	*/

//练习题:
	std::map<std::string, int> map1;
	std::set<std::string> set{ "the","a","an","and","but" };
	std::string word;
	while (std::cin >> word)
	{
		std::for_each(word.begin(), word.end(), [](char &ch) {ch = tolower(ch); });
		word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());
		if (std::find(set.begin(), set.end(), word) == set.end())
		{
			std::pair<std::map<std::string,int>::iterator,bool> iter = map1.insert(std::pair<std::string,int>(word, 1));
			if (!iter.second)
				++iter.first->second;
		}
	}
	std::for_each(map1.begin(), map1.end(), [](std::pair<std::string, int> map_pair)
	{std::cout << "The word is " << map_pair.first << ", and the count is " << map_pair.second << std::endl; });

	system("pause");
	return 0;
}