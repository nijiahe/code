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


int main10_4_3()
{
	//反向迭代器只适用于既有++又有--操作的容器,即forward_list(单向链表)和流不支持反向迭代器
	std::string str("FIRST,MIDDLE,LAST");
	std::string::reverse_iterator str_riter = std::find(str.rbegin(), str.rend(), ',');
	std::cout << std::string(str.rbegin(), str_riter) << std::endl;
	//reverse_iterator(反向迭代器)有成员函数base,可以将反向迭代器的迭代顺序变为正
	std::cout << std::string(str_riter.base(), str.end()) << std::endl;

//练习题:
	std::vector<int> v1{ 1,3,5,7,0,6,1,3,9,8,1,3,0,4,8 };
	std::for_each(v1.rbegin(), v1.rend(), [](int i) {std::cout << i << std::ends; }); std::cout << std::endl;

	for (std::vector<int>::iterator iter = v1.end(); iter != v1.begin(); )
	{
		std::cout << *(--iter) << std::ends;
	}
	std::cout << std::endl;

	std::vector<int>::reverse_iterator riter = std::find(v1.rbegin(), v1.rend(), 0);
	std::cout << std::distance(riter,v1.rend()) << std::endl;

	std::vector<int> v2{ 11,22,33,44,55,66,77,88,99,1010,1111 };
	std::list<int> list;
	std::copy(v2.rbegin() + 3, v2.rend() - 3, std::back_inserter(list));//我原本是直接用list初始化构造函数的,github中那个人用back_inserter明显更能回顾所学知识
	std::for_each(list.begin(), list.end(), [](int i) {std::cout << i << std::ends; });

	std::cout << std::endl;

	system("pause");
	return 0;
}