#include <iostream>
#include"linklist.h"
/*模板类不是一种类型，实例化模板类的时候需要调用类中的函数，但是因为只知道声明，不知道定义，没有办法实例化，
* 如果要实例化，需要在模板类中的头文件中就完成对模板类的定义，或者在main.cpp中包含对类模板文件的定义*/
#include"linklist.cpp"
using namespace std;

int main()
{

	linklist<double> list1;
	list1.ListInsertHead(1.1);
	list1.ListInsertHead(2.1);
	list1.ListInsertHead(3.1);
	list1.ListInsertHead(4.1);
	list1.ListInsertTail(5.1);
	list1.ListInsertIndex(3, 10.1);
	list1.ListInsertIndex(1, 8.1);
	list1.ListSort(1);
	list1.ListShow();
	std::cout << "**********************" << std::endl;
	list1.ListRemove(1.1);
	list1.ListShow();
	run(list1);//类模板友元函数测试
	/*test<double> test1;
	test1.show(list1);//类模板友元类测试*/
	

	std::cin.get();
	return 0;
}