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
#include <cstring>

int add(int a, int b) { return a + b; }
class devide
{
public:
	int operator()(int a, int b) { return a / b; };
};
auto mod = [](int a, int b) {return a % b; };

auto binops = std::map<std::string, std::function<int(int, int)>>
{
	{"+",add},
	{"-",std::minus<int>()},
	{"/",devide()},
	{"*",[](int a,int b) {return a * b; }},
	{"%",mod}
};

int main14_8_3()
{
	/*
	 lambda表达式的实质是一个类
	 函数指针类对象的实质是函数指针
	 普通函数指针的意义是函数指针
	 为了让其统一为同一种类型,标准库定义了function类
	 function类可以由函数指针,函数对象和lambda表达式初始化
	 注意:对于重载过的函数,由于一个名字对应了好多个参数不同的函数,可以通过另创指针取名字或为其创建别的形式的方式来取代.从而消除二义性
	 */
	std::string ops;
	int a, b;
	while (std::cin >> ops >> a >> b)
	{
		std::cout << binops[ops](a, b) << std::endl;
	}

	system("pause");
	return 0;
}