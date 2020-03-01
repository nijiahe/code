#include "Stack.h"
#include "Queue.h"
#include <iostream>

using namespace std;

int main4() {
	Stack<int> s;

	s.push(3);
	s.push(2);
	s.push(5);
	s.push(7);
	s.push(9);
	s.push(8);
	s.push(4);
	s.push(9);
	s.push(8);
	s.push(4);
	s.push(9);
	s.push(8);
	s.push(4);

	cout << "The size is: " << s.size() << endl;
	s.traverse([](int& i) {cout << i << " "; });
	cout << endl;

	s.pop();
	cout << "The size is: " << s.size() << endl;
	s.traverse([](int& i) {cout << i << " "; });
	cout << endl;

	s.sort();
	cout << "The size is: " << s.size() << endl;
	s.traverse([](int& i) {cout << i << " "; });
	cout << endl;

	s.deduplicate();
	cout << "The size is: " << s.size() << endl;
	s.traverse([](int& i) {cout << i << " "; });
	cout << endl;

	Stack<char> sc;
	_int64 n = 123456;
	int base = 2;
	cout << "The num " << n << " in base " << base << " is:";
	convert(sc, n, base);
	char c;
	int size = sc.size();
	for (int i = 0; i < size; i++)
		cout << (c=sc.pop());
	cout << endl;

	char str[] = "{x+2*[2+3]/(a+b)}";
	cout << "The expression \"" << str << "\" is lawful? :" << parenMatch(str, 0, sizeof(str)-1);
	cout << endl;

	char str2[] = "6*2-(2+2*(3-3)/2)+2";
	Vector<char> v;
	cout << "The expression \""<<str2<<"\" result is :"<<evaluate(str2,v) << endl;
	cout << "The RPN expression is \"";
	v.traverse([](char& c) {cout  << c ; });
	cout << "\""<<endl;

	Queue<int> q;
	q.insertAsLast(4);
	q.insertAsLast(9);
	q.insertAsLast(8);
	q.traverse([](int& i) {cout << i << " "; });
	cout << endl;

	return 0;
}