#include "visit.h"
#include "RedBlack.h"
#include "VisualTree.h"

int main8_3() {
	RedBlack<int> rb;

	VisualTree<BinNode<int>, int>  vtree(
		&BinNode<int>::parent, &BinNode<int>::lChild, &BinNode<int>::rChild, &BinNode<int>::data
	);

	for (int i = 0; i < 70; i++) {
		rb.insert(rand() % 70);
		vtree.draw(rb.root());
	}

	for (int i = 0; i < 100; i++) {
		rb.remove(rand() % 70);
		vtree.draw(rb.root());
	}

	for (int i = 0; i < 70; i++) {
		rb.insert(rand() % 70);
		vtree.draw(rb.root());
	}

	for (int i = 0; i < 100; i++) {
		rb.remove(rand() % 70);
		vtree.draw(rb.root());
	}

	return 0;
}