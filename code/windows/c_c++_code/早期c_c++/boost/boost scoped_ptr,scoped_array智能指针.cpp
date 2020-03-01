#include<iostream>
#include<boost/scoped_ptr.hpp>
#include<boost/scoped_array.hpp>

using namespace std;

void mainI()
{
	boost::scoped_ptr<int> ptr(new int);
	*ptr = 12;
	//ptr.get()返回的是ptr储存的地址
	cout << *ptr.get() << endl;
	ptr.reset(new int);//重新赋值,删除前一个地址
	*ptr.get() = 3;
	//boost::scoped_ptr<int> ptr2(ptr);拷贝构造是私有,无法访问,可以保证用用智能指针创建的指针不会重复删除
	cout << *ptr.get() << endl;

	cin.get();
}
//智能指针数组
void mainJ()
{
	boost::scoped_array<int> ptr(new int[10]);
	for (int i = 0; i < 10; i++)
	{
		ptr[i] = i;
	}
	for (int i = 0; i < 10; i++)
	{
		cout << ptr[i] << " ";
	}
	cin.get();
}