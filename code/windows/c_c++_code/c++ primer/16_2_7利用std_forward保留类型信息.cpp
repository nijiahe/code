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

void f(int v1, int& v2)
{
	std::cout << v1 << " " << ++v2 << std::endl;
}
void g(int &&i, int &j)
{
	std::cout << i << " " << j << std::endl;
}

/*
当使用模板函数的模板类型接收参数时,例如下例模板函数
我们希望通过flip1调用f来改变v2作为一个引用来传入的值
若直接调用f(42,i),是能够按照预期进行的,但是若期望调用flip1(f,42,i),flip1被实例化为flip(func*,int,int),当然不会如预期一般了
于是有了flip2的版本,此版本利用类型折叠,保留了左值的信息,但是若是调用flip2(g,42,i),由于42会被接收为int,即flip2被实例化为flip2(func*,int,int)//注意:还是不太懂,也不太确定
而利用std::forward<T>(t)可以保留参数的信息
*/
template<typename F,typename T1,typename T2>
void flip1(F f, T1 t1, T2 t2)
{
	f(t1, t2);
}
template<typename F, typename T1, typename T2>
void flip2(F f, T1 &&t1, T2 &&t2)
{
	f(t1, t2);
}
template<typename F, typename T1, typename T2>
void flip(F f, T1 &&t1, T2 &&t2)
{
	std::cout << typeid(t1).name() << typeid(t2).name() << std::endl;
	f(std::forward<T1>(t1), std::forward<T2>(t2));
}


int main16_2_7()
{
	int i = 1;
	flip(g, 42, i);

	system("pause");
	return 0;
}