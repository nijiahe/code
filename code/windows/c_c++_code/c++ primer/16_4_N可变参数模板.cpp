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

/*16_3*/
template<typename T>
std::string debug_req(const T &t)
{
	std::ostringstream ret;
	ret << t;
	return ret.str();
}

/*16_4*//*使用sizeof(Args/args)打印可变参数量*/
template<typename T,typename...Args>
void foo(const T &t, const Args...args)
{
	std::cout << sizeof...(Args) << std::ends;//sizeof...可以用来统计不同类型的数量
	std::cout << sizeof...(args) << std::endl;//sizeof...可以用来统计可变参数的数量
}

/*16_4_1*//*巧妙利用多一个的参数,来实现可变参数递归遍历*/
//这个函数相当于递归终止条件,根据最特例化匹配原则,在函数算上可变参数只剩两个参数时,会匹配到这个函数,而不是下面那个可变参函数
template<typename T>
std::ostream &print(std::ostream &os, const T &t)
{
	return os << t << std::endl;
}

template<typename T, typename...Args>
std::ostream &print(std::ostream &os, const T&t, const Args...rest)
{
	os << t << ",";
	return print(os, rest...);//这样每次就有一个原本属于rest中的参数被接收为了const T& t
}

/*16_4_2*//*包扩展*/
template<typename...Args>
std::ostream &errorMsg(std::ostream &os, const Args...rest)
{
	return print(os, debug_req(rest)...);
	//相当于编写了return print(os, debug_req(rest1),debug_req(rest2),debug_req(rest3)等等),对debug_req(...)进行了扩展
}


int main16_4_N()
{
	/*16_4*/
	int i = 0; double d = 3.14; std::string s = "how now brown cow";
	foo(i, s, 42, d);
	foo(s, 42, "hi");
	foo(d,s);
	foo("hi");

	/*16_4_1*/
	print(std::cout, i, s, 42);

	/*16_4_2*/
	errorMsg(std::cout, i, s, 42);

	system("pause");
	return 0;
}