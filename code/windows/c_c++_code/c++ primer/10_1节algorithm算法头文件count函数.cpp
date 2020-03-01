#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <list>
#include <algorithm>


int main10_1()
{
	std::string str("abcdhefg123");
	std::string::iterator result = find(str.begin(), str.end(), 'h');//返回一个迭代器
	std::cout << *result << std::endl;

	int num[] = { 1,3,5,121,8,9,121,165,121,3 };
	auto res = std::find(std::begin(num), std::end(num), 121);
	std::cout << *res << std::endl;

	std::vector<int> v1{ 1, 3, 5, 121, 8, 9, 121, 165, 121, 3 };
	std::cout << std::count(v1.begin(), v1.end(), 121) << std::endl;

	std::list<std::string> list1{ "a","aa","aaa","aa","1" };
	std::cout << std::count(list1.begin(), list1.end(), "aa") << std::endl;

	system("pause");

	return 0;
}