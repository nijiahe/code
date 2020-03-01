#include <iostream>
#include"linklist.h"
/*模板类不是一种类型，实例化模板类的时候需要调用类中的函数，但是因为只知道声明，不知道定义，没有办法实例化，
* 如果要实例化，需要在模板类中的头文件中就完成对模板类的定义，或者在main.cpp中包含对类模板文件的定义*/
#include"linklist.cpp"
using namespace std;

void main()
{
	linklist<int> list1;
	list1.ListInsertHead(1);
	list1.ListInsertHead(2);
	list1.ListInsertHead(3);
	list1.ListInsertHead(4);
	list1.ListInsertHead(5);
	list1.ListInsertHead(6);
	list1.ListInsertHead(7);
	list1.ListInsertHead(8);
	list1.ListInsertHead(9);
	list1.ListShow();
	cout << list1.Maxkey(list1.nodecount(list1.ListFindIndex(1))) << endl;//最大值
	cout << list1.nodecount(list1.ListFindIndex(1)) << endl;//节点数
	cout << list1.Average(list1.nodecount(list1.ListFindIndex(1))) << endl;//平均值


	cin.get();
}