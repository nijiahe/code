#include <iostream>
#include <algorithm>
#include <functional>
#include <iterator>
#include <cstdlib>
#include <string>
#include <vector>
#include <list>


int mainmain10_4_1()
{
	/*
	注意:一些特殊的迭代器定义在头文件<iterator>下
	三种插入迭代器:
	1.std::back_inserter	创建一个使用push_back的迭代器
	2.std::front_inserter	创建一个使用push_front的迭代器
	3.std::inserter			创建一个使用insert的迭代器,此函数接受第二个参数,用以指定一个给定容器的迭代器,元素将被插入到此给定迭代器所指元素之前
	对插入迭代器而言,*it,++it,it++,--it,it--对it没有任何作用,每种操作都返回it
	*/

//练习题:
	std::vector<int> v1{ 1,3,5,7,6,1,3,9,8,1,3,4,8 };
	std::sort(v1.begin(), v1.end());
	std::vector<int> v2;
	std::back_insert_iterator<std::vector<int> > biter = std::back_inserter(v2);
	std::unique_copy(v1.begin(), v1.end(), biter);
	std::for_each(v2.begin(), v2.end(), [](int i) {std::cout << i << std::ends; });
	std::cout << std::endl;

	std::vector<int> v3{ 1,2,3,4,5,6,7,8,9 };
	std::list<int> list1;
	std::insert_iterator<std::list<int> > ins = std::inserter(list1, list1.begin());//insert_iterator迭代器调用inserth
	std::copy(v3.begin(), v3.end(), ins);
	std::for_each(list1.begin(), list1.end(), [](int i) {std::cout << i << std::ends; });
	std::cout << std::endl;
	list1.clear();
	std::back_insert_iterator<std::list<int> > bins = std::back_inserter(list1);//back_insert_iterator迭代器调用push_back
	std::copy(v3.begin(), v3.end(), bins);
	std::for_each(list1.begin(), list1.end(), [](int i) {std::cout << i << std::ends; });
	std::cout << std::endl;
	list1.clear();
	std::front_insert_iterator<std::list<int> > fins = std::front_inserter(list1);//front_insert_iterator迭代器调用push_front
	std::copy(v3.begin(), v3.end(), fins);
	std::for_each(list1.begin(), list1.end(), [](int i) {std::cout << i << std::ends; });
	std::cout << std::endl;


	system("pause");
	return 0;
}