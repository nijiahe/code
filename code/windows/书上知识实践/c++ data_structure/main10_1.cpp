#include "PQ_ComplHeap.h"

int main10_1() {
	PQ_ComplHeap<int> pq;

	for (int i = 0; i < 70; i++) {
		pq.insert(rand() % 70);
	}

	for (int i = 0; i < 100; i++) {
		pq.delMax();
	}

	return 0;
}