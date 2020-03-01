#include "BTree.h"
#include "visit.h"

int main8_2(){
	BTree<int> btree;

	for (int i = 0; i < 70; i++) {
		int num = rand() % 70;
		std::cout << "insert:" << num << std::endl;
		btree.insert(num);
	}
	LOG_BTREE(btree.root());
	

	for (int i = 0; i < 100; i++) {
		int num = rand() % 70;
		std::cout << "remove:" << num << std::endl;
		btree.remove(num);
		LOG_BTREE(btree.root());
	}
	

	return 0;
}