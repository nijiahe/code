#include"linklist.h"
#include"linklist.cpp"
#include<iostream>

using namespace std;

void main()
{
	linklist<int> list1;
	list1.pushback(1);
	list1.pushback(2);
	list1.pushback(3);
	listnode<int>* node=list1.pushback(4);
	list1.listshow();

	list1.indexinsert(1, 12);
	list1.listshow();

	list1.revise(6, 99);
	list1.listshow();

	cout << list1.findvalue(12)->data << endl;
	cout << "*********************" << endl;

	list1.remove(3);
	list1.remove(node);
	list1.listshow();
	cin.get();
}