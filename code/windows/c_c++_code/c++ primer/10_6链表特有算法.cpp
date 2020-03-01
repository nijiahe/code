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


int main10_6()
{
	std::vector<std::string> v1{ "the","quick","red","fox","jumps","over","the","slow","red","turtle" };
	std::list<std::string> list(v1.begin(), v1.end());
	list.sort();
	list.unique();
	std::for_each(list.begin(), list.end(), [](std::string str) {std::cout << str << std::ends; });

	system("pause");
	return 0;
}