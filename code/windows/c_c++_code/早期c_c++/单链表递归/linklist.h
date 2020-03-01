#ifndef LINKLIST_H
#define LINKLIST_H
//一个链表结构存储头节点和尾节点
#include<iostream>
#include"listnode.h"


using namespace std;
template<class T> class listnode;//声明类
template<class T> void run(linklist<T> &it);//声明友元函数
											/*在类模板中使用友元函数，需要在类定义前加上函数的声明*/

template<class T>
class linklist
{
private:
	listnode<T>* topnode;
	listnode<T>* tailnode;
public:
	linklist();
	~linklist();
public:
	void ListInsertHead(T value);//前插  OK
	void ListInsertTail(T value);//尾插  OK
	void ListInsertIndex(int index, T value);//根据目录数，在目录数后面一个节点插入节点   OK
	void ListSort(bool flag);//对链表进行排序   OK
	void ListShow();//遍历链表,显示所有节点     OK
	listnode<T> * ListFindIndex(int index);//根据目录数返回第index个节点的地址    OK
	listnode<T> * ListFindValue(T value);//查找第一个出现指定值的节点的地址   OK
	/*当实例化为int时会和上面那个函数重复定义,所以去除*///void ListRemove(int index);//根据目录数删除节点    OK
	void ListRemove(T value);//根据值删除节点      OK
	void ListRemove(listnode<T>* valuenode);//根据节点地址删除节点   OK
											/*?如何实现void ListRemove(int index，Args...args)?*/
	void ListRevise(int index, T value);//根据目录数修改该目录节点的数据  OK
	friend void run<T>(linklist<T> &it);//类模板友元函数测试*/
										/*这个函数只是在T类型下的友元函数，不能通过这个类型的函数访问别的类型的类*/
	T Maxkey(int n);//递归实现返回前n个数中的最大值     OK
	int nodecount(listnode<T>* node);//递归实习求链表的结点个数      OK
	double Average(int n);//递归实现求n个数的平均值     OK
};


#endif // LINKLIST_H
