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
#include <map>
#include <set>
#include <utility>

void mapValueReplace(std::pair<std::string, int> pair, int num)
{
	pair.second = num;
}

int main11_3_1()
{
	//map的迭代器*iter得到的是std::pair类型,并且map和set的关键字都是const的,都不能被改变



	system("pause");
	return 0;
}