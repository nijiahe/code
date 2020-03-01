#include "List.h"
#include <iostream>

using namespace std;

int main3()
{
	List<int> list;

	list.insertAsLast(3);
	list.insertAsLast(2);
	list.insertAsLast(5);
	list.insertAsLast(7);
	list.insertAsLast(9);
	list.insertAsLast(8);
	list.insertAsLast(4);
	list.insertAsLast(9);
	list.insertAsLast(8);
	list.insertAsLast(4);
	list.insertAsLast(9);
	list.insertAsLast(8);
	list.insertAsLast(4);

	cout << "The size is: " << list.size() << endl;
	list.traverse([](int& i) {cout << i << " "; });
	cout << endl;

	list.sort();
	cout << "The size is: " << list.size() << endl;
	list.traverse([](int& i) {cout << i << " "; });
	cout << endl;

	list.deduplicate();
	cout << "The size is: " << list.size() << endl;
	list.traverse([](int& i) {cout << i << " "; });
	cout << endl;

	return 0;
}