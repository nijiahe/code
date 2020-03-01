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

int main14_9_1()
{
	/*
	operator int()是定义自己的对类强转为int时的过程的定义,一般这个过程不会改变类内的值,所以被定义成const的,即
	operator int() const
	但是因为这样做有时隐式转换会发生难以预料的事情,所以一般会被设定为显示转换explicit,即
	explicit operator int() const
	但是被应用于条件语句中作为条件时,编译器会自动应用显示转换
	*/

	system("pause");
	return 0;
}