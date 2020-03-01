#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <numeric>
#include <string>
#include <vector>

int main10_2_3()
{
	std::vector<int> v1{ 1,3,5,7,6,1,3,9,8,1,3,4,8 };
	for (int i : v1)
		std::cout << i << std::ends;
	std::cout << std::endl;
	//sort算法,STL中的快速排序算法,按<的策略对传入的迭代器确定的范围进行快速排序
	std::sort(v1.begin(), v1.end());
	for (int i : v1)
		std::cout << i << std::ends;
	std::cout << std::endl;
	//unique算法,作用为消除相邻的重复元,返回一个迭代器指向这些重复元素的开始位置
	//std::unique并不改变容器的大小
	//注意:此时容器尾部的那些元素原来是啥现在还是啥，并没有变
	std::vector<int>::iterator end_unique = std::unique(v1.begin(), v1.end());
	for (int i : v1)
		std::cout << i << std::ends;
	std::cout << std::endl;
	v1.erase(end_unique, v1.end());//利用vector容器的vector算法传入两个迭代器，删除其中间的内容
	for (int i : v1)
		std::cout << i << std::ends;
	std::cout << std::endl;

	system("pause");
	return 0;
}