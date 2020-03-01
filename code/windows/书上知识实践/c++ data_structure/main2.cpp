#include "Vector.h"

using namespace std;

int main2()
{
	Vector<int> vec;
	
	vec.insert(3);
	vec.insert(2);
	vec.insert(5);
	vec.insert(7);
	vec.insert(9);
	vec.insert(8);
	vec.insert(4);
	vec.insert(9);
	vec.insert(8);
	vec.insert(4);

	cout << "The size is: " << vec.size() << endl;
	vec.traverse([](int& i) {cout << i << " "; });
	cout << endl;

	vec.sort(0, vec.size());
	cout << "The size is: " << vec.size() << endl;
	vec.traverse([](int& i) {cout << i << " "; });
	cout << endl;

	vec.deduplicate();
	cout << "The size is: " << vec.size() << endl;
	vec.traverse([](int& i) {cout << i << " "; });
	cout << endl;

	return 0;
}