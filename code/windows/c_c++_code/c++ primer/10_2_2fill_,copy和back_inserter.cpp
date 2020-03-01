#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <numeric>
#include <string>
#include <vector>

int main10_2_2()
{
	std::vector<int> v1{ 1,2,3,4,5,6 };
	for (auto i : v1)
		std::cout << i << std::ends;
	std::cout << std::endl;
	std::fill(v1.begin(), v1.end(), 3);//std::fill接收两个迭代器用以表示fill的范围，第三个参数用表示fill的值
	for (auto i : v1)
		std::cout << i << std::ends;
	std::cout << std::endl;

	std::vector<int> v2{ 1,2,3,4,5,6 };
	for (auto i : v2)
		std::cout << i << std::ends;
	std::cout << std::endl;
	std::fill_n(v2.begin(), v2.size()-1, 3);//std::fill_n接收一个迭代器和一个fill的数量用以表示范围，第三个参数用表示fill的值
	for (auto i : v2)
		std::cout << i << std::ends;
	std::cout << std::endl;

	//插入迭代器
	//向插入迭代器赋值相当于调用pushback()函数将值插入容器中
	//插入back_insert_iterator的++和--操作好像没有意义
	std::vector<int> v3;
	std::back_insert_iterator<std::vector<int> > bi = std::back_inserter(v3);
	std::fill_n(bi, 10, 6);//为此插入迭代器赋值相当于向容器内插入元素
	for (auto i : v3)
		std::cout << i << std::ends;
	std::cout << std::endl;

	//copy算法,接受3个参数,参数的意义与equal一样，前两个表示一个范围，将前两个确定的范围拷贝给第三个参数指示的容器的位置
	std::copy(v1.begin(), v1.end(), v3.begin());
	for (auto i : v3)
		std::cout << i << std::ends;
	std::cout << std::endl;

	//replace算法:接受四个参数，前两个迭代器确认范围，将范围内所有的第三个参数换为第四个参数
	std::replace(v3.begin(), v3.end(),6,9 );
	for (auto i : v3)
		std::cout << i << std::ends;
	std::cout << std::endl;

	//replace_copy算法:接受5个参数，此算法将第一二个参数确定的范围内的所有第四个参数替换为第五个参数，并传入到第三个参数所提供的插入迭代器中
	//这样做的意义是不改变不改变原有的容器，将替换后的序列放入新容器中
	std::vector<int> v4;
	std::replace_copy(v3.begin(), v3.end(), std::back_inserter(v4), 9, 7);
	for (auto i : v4)
		std::cout << i << std::ends;
	std::cout << std::endl;

//练习题:
	std::vector<int> v5{ 1,2,3,4,5,6,7,8,9 };
	for (int i : v5)
		std::cout << i << std::ends;
	std::cout << std::endl;
	std::fill_n(v5.begin(), v5.size(), 0);
	for (int i : v5)
		std::cout << i << std::ends;
	std::cout << std::endl;

	system("pause");
	return 0;
}