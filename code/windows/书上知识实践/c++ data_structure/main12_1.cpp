#include "Vector.h"
#include "majority.h"

int main12_1() {
	Vector<int> v;
	for (int i = 0; i < 5; i++)
		v.insert(rand() % 100);
	int n = rand() % 100;
	for (int i = 0; i < 6; i++)
		v.insert(n);
	v.traverse([](int& n) {std::cout << n << " "; });
	std::cout << std::endl;

	v.quickSort(0, v.size());

	v.traverse([](int& n) {std::cout << n << " "; });
	std::cout << std::endl;

	int maj;
	if (majority(v, maj))
		std::cout << "majority is " << maj << std::endl;

	return 0;
}
