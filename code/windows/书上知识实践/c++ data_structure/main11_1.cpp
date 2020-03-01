#include "KMP.h"
#include <iostream>

using namespace std;

int main11_1() {
	const char* P = "abcab,ababa";
	const char* T = "abcabcba,bcabcbabcba,babcbaabcab,ababacbaba,bcbacb,acbabc,ababc,cbabcaabc";
	int m = std::strlen(P);
	int* Next = buildNext(P);
	for (int i = 0; i < m; i++) {
		std::cout << Next[i] << " ";
	}
	std::cout << std::endl;
	int num = KMP_match(P, T);
	std::cout << T + num << std::endl;

	return 0;
}