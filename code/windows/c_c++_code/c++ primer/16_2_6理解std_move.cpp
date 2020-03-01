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
#include <type_traits>

/*
std::move在标准库下的实现
先通过remove_reference::type取传入参数的最基础类型(例如:常量42取int,左值int&也取int)
然而返回值却是int&&,利用static_cast将int转化为了int&&,这就是std::move的内部机制了
*/
template<typename T>
typename std::remove_reference<T>::type&& move(T&& t)
{
	return static_cast<typename std::remove_reference<T>::type&&>(t);
}


int main16_2_6()
{
	

	system("pause");
	return 0;
}