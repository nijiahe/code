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
		//ע:�����ظ���������������ͬ�Ĺؼ���ʱ,insert����ʲôҲ������,����std::pair���͵ĵ�����,�����second��Ա�������false
		//���ص�std::pair���͵�first��Ա��ָ�����ָ���ؼ���Ԫ�صĵ�����
		//�����ظ�������������һ��ָ�����Ԫ�صĵ�����,�����ظ��������ص�std::pair���͵�first��Ա����
		std::pair<std::map<std::string, int>::iterator, bool> pair = map.insert(std::make_pair(words,1));
		if (!pair.second)
			++pair.first->second;
	}
	std::for_each(map.begin(), map.end(), [](std::pair<std::string, int> pair)
	{ std::cout << pair.first << ":" << pair.second << std::endl; });
	*/

//��ϰ��:
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