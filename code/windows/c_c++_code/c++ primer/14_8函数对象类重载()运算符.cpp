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

class calcu
{
public:
	int operator()(int a, int b, int c)
	{
		return a ? b : c;
	}
};

class PrintString
{
public:
	std::string operator()(std::istream& in)
	{
		std::string str;
		getline(in, str);
		return in ? str : std::string();
	}
};

class Equal
{
public:
	bool operator()(int a, int b)
	{
		return a == b ? true : false;
	}
};

int main14_8()
{
	calcu c1;
	std::cout << c1(2 > 1, 2, 3) << std::endl;

	std::vector<std::string> v1;
	std::string line;
	while ((line = PrintString()(std::cin)) != std::string())
	{
		v1.push_back(line);
	}
	for (auto l : v1)
	{
		std::cout << l << std::endl;
	}

	std::vector<int> v2{ 3,4,3,5,6,3,7,3,8 };
	std::replace_if(v2.begin(), v2.end(),std::bind(Equal(),3,std::placeholders::_1),5);
	for (auto n : v2)
		std::cout << n << std::ends;
	std::cout << std::endl;

	system("pause");
	return 0;
}
