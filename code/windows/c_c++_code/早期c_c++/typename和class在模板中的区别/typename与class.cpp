#include<iostream>

using namespace std;

template<typename T>
class test
{
public:
	typename T::testtype* ptr;/*如果不加typename,编译器会把 T::testtype当成T里面的静态成员函数或者变量(因为只有静态的才能不建立实例直接访问)*/
};/*加了typename以后编译器知道这是在T里定义的类型*/

class temp
{
public:
	int* ptr;
	typedef int testtype;
};
void main()
{
	test<temp> test1;
	cin.get();
}