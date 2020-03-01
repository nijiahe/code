#include "BM.h"
#include <iostream>

int main11_2() {
	const char* P = "abcdabc";
	int s = std::strlen(P);
	int* SS = buildSS(P);
	for (int i = 0; i < s; i++)
		std::cout << SS[i] << " ";
	std::cout << std::endl;

	return 0;
}