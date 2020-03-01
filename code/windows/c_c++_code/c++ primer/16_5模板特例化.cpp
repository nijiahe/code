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

/*可以对一个模板进行特例化,以指定其指定模板类型时的特别操作*/
template<typename T>
int compare(const T& v1, const T& v2)
{
	if (v1 < v2)return -1;
	else if (v2 < v1) return 1;
	else return 0;
}

//特例化const char*类型
template<> //template<>代表这是一个特例化模板函数,而不是一个普通非模板函数
int compare(const char *const &p1, const char *const &p2)
{
	return strcmp(p1, p2);
}

/*
部分特例化:
部分特例化的意思不是对一个模板类型比如template<typename T,typename U>这样子的指定其T是什么
而是根据其传入的参数的具体特性来进行特例化,比如,传入的参数是一个左值int &,或者是一个右值int &&,通过传入参数的不同的性质加以区分
标准库的std::remove_reference类型就利用了部分特例化,对传入参数是左值或右值的情况下进行了不同的区分,如下所示:
*/
//最普通的情况,啥也不是,则remove_reference::type的类型仍然和原来的相同
template<class T> struct remove_reference {
	typedef T type;
};
//为传入参数是左值引用时进行特例化
template<class T> struct remove_reference<T &> { 
	typedef T type;
};
//右值
template<class T> struct remove_reference<T &&> { 
	typedef T type;
};

//这样就做到了去除变量类型的引用属性或者右值属性.type变为了最普通的类型,即左右值,既可读也可写

int main16_5()
{
	
	system("pause");
	return 0;
}