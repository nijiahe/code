#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <memory>
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

std::vector<int>* creatIntVec()
{
	return new std::vector<int>;
}

void readInVec(std::vector<int>* &vec)
{
	int num;
	while (std::cin >> num)
		vec->push_back(num);
}

void printAndDeleteVec(std::vector<int>* &vec)
{
	std::for_each(vec->begin(), vec->end(), [](int i) {std::cout << i << std::ends; });
	std::cout << std::endl;
	delete vec;
	vec = nullptr;
}

int main12_1_2()
{
	//对于类,new会按照其构造函数进行构造,但对于内置类型,默认初始化的结果是未定义的,要对其进行值初始化,只需在new的类型名加()即可
	int* num1 = new int;//num1是一个随机数
	int* num2 = new int();//num2是0
	std::cout << "num1 is " << *num1 << ",and meantime num 2 is " << *num2 << std::endl;

	//利用new auto()使编译器自动推测要new的类型
	std::string str;
	auto str2 = new auto(str);
	std::cout << typeid(str2).name() << std::endl;

	//若内存耗尽,new会抛出std::bad_alloc,要阻止抛出可使用(nothrow),此时new会返回一个空指针
	int* num3 = new(std::nothrow) int();

//练习题:
	auto vec = creatIntVec();
	readInVec(vec);
	printAndDeleteVec(vec);
	std::cout << "Now the vec is " << vec << std::endl;

	system("pause");
	return 0;
}
