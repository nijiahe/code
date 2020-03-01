#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <numeric>
#include <string>
#include <vector>

inline bool isLongerThan5(std::string str)
{
	return str.size() >= 5;
}

inline bool isLonger(const std::string &i, const std::string& j)
{
	return i.size()>j.size();
}

void elimDups(std::vector<std::string> &v)
{
	std::sort(v.begin(), v.end());
	std::vector<std::string>::iterator end_unique = std::unique(v.begin(), v.end());
	v.erase(end_unique, v.end());
}

int main10_3_1()
{
	std::vector<std::string> v1{ "the","quick","red","fox","jumps","over","the","slow","red","turtle" };
	for (std::string i : v1)
		std::cout << i << std::ends;
	std::cout << std::endl;
	elimDups(v1);//先利用正常的sort来消除重复单词
	for (std::string i: v1)
		std::cout << i << std::ends;
	std::cout << std::endl;
	std::stable_sort(v1.begin(), v1.end(), isLonger);//stable_sort会将比较相等的元素按照按照原来的次序排列
	for (std::string i : v1)
		std::cout << i << std::ends;
	std::cout << std::endl;

//练习题10.13
	std::vector<std::string> v2{ "the","quick","red","fox","jumps","over","the","slow","red","turtle" };
	std::vector<std::string>::iterator end_part = std::stable_partition(v2.begin(), v2.end(), isLongerThan5);
	if (end_part != v2.begin())
		std::cout << "exit" << std::endl;
	for (std::vector<std::string>::iterator ib = v2.begin(); ib != end_part; ++ib)
		std::cout << *ib << std::ends;
	std::cout << std::endl;

	system("pause");
	return 0;
}