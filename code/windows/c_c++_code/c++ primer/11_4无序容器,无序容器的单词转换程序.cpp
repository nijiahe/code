#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <iterator>
#include <cstdlib>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <set>
#include <utility>


std::unordered_map<std::string, std::string> buildRuleMap2(std::ifstream &file)
{
	std::unordered_map<std::string, std::string> rule_map;
	std::string key;
	std::string value;
	while (file >> key && std::getline(file, value))
	{
		if (value.size() > 1)
			rule_map[key] = value.substr(1);//去除前置空格
		else
			throw std::runtime_error("[Error]:There is no value for this key");
	}
	return rule_map;
}

std::string transform2(std::string word, const std::unordered_map<std::string, std::string> &rule_map)
{
	std::unordered_map<std::string, std::string>::const_iterator iter = rule_map.find(word);
	if (rule_map.find(word) != rule_map.end())
		return iter->second;
	else
		return word;
}

void word_translation2(std::ifstream &map_file, std::ifstream &file)
{
	std::unordered_map<std::string, std::string> rule_map = buildRuleMap2(map_file);
	std::string line, word;
	while (std::getline(file, line))
	{
		std::istringstream strstream(line);
		bool first_word = true;
		while (strstream >> word)
		{
			if (first_word)
				first_word = false;
			else
				std::cout << " ";
			std::cout << transform2(word, rule_map);
		}
		std::cout << std::endl;
	}
}

int main11_4()
{
	/*
	注:有序容器是序的,默认由从小到大排列,所以使用其做字典是的结果是字典序
	而无序容器遍历时就不会按照字典序输出了
	*/

//练习题:无序版本的单词转换程序
	std::ifstream file1("F:\\word translation1.txt");
	std::ifstream file2("F:\\word translation2.txt");
	word_translation2(file1, file2);



	system("pause");
	return 0;
}
