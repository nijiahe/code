#include "Skiplist.h"

int main9_1() {
	Skiplist<int,int> slist;

	for (int i = 0; i < 70; i++) {
		slist.put(rand() % 70, rand() % 70);
	}

	for (int i = 0; i < 100; i++) {
		slist.remove(rand() % 70);
	}

	for (int i = 0; i < 70; i++) {
		slist.put(rand() % 70, rand() % 70);
	}

	for (int i = 0; i < 100; i++) {
		slist.remove(rand() % 70);
	}

	return 0;
}