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

/*
由于模板被使用时才会实例化,所以在编译阶段无法将其进行代码复用,则在每个.cpp文件被编译时
都会生成一个其所需要的模板函数,这样在所有文件编译结束后,也许模板类型相同的函数已经会在很多.o文件中都出现,
这样子会加大开销.通过显式实例化(在当前.cpp文件中通过声明extern template class<...>来声明在别的.cpp文件中已经被编译的模板)
可以解决这一开销
*/

int main16_1_5()
{

	system("pause");
	return 0;
}