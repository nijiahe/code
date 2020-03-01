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

template<typename> class T2;

//可以为模板提供默认实参,在定义模板类对象时在后面加上<>表示这是一个模板
template<typename T=int>
class T1
{
public:
	//friend class T3;//T3不是模板类,此时为非模板类的友元声明方式
	//template <typename X>friend class T2;//所有的T2都为T1的友元类,此时声明模板所选用的模板参数不应与此类本身的模板相同
	//下例为一对一友元关系,只让对应实例的T2成为T1的友元,但此时必须在T1之前声明T2是一个友元类,
	//否则编译器会应不知晓T2是一个模板类而将<>符号是为语法错误
	friend class T2<T>;
	friend T;//在c++11中,可以将用于模板类型声明为友元,如T是另一个类Foo,那么此时Foo是T1<Foo>的友元类
	T data = 99;
};

template<typename T>
class T2
{
	T1<int> t1;
	T data;
};

class T3
{
	int t3;
};


int main16_1_2()
{
	T1<> t1;
	std::cout << t1.data << std::endl;
	system("pause");
	return 0;
}