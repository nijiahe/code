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

int main12_2_2()
{
	//注:有序关联容器可以自己制定元素比较方法来控制其存放顺序,默认情况下标准库使用'<'来比较关键字
	std::multiset<int, bool(*)(int, int)> set([](int i, int j) {return i > j; });//自定义小于的规则来创建关联容器

	system("pause");
	return 0;
}