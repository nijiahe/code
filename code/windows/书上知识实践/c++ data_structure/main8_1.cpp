#include "Splay.h"
#include "VisualTree.h"
   

int main8_1() {
	Splay<int> s;

	VisualTree<BinNode<int>, int>  vtree(
		&BinNode<int>::parent, &BinNode<int>::lChild, &BinNode<int>::rChild, &BinNode<int>::data
	);

	for (int i = 0; i < 70; i++) {
		s.insert(rand() % 70);
		vtree.draw(s.root());
	}

	for (int i = 0; i < 100; i++) {
		s.remove(rand() % 70);
		vtree.draw(s.root());
	}

	for (int i = 0; i < 70; i++) {
		s.insert(rand() % 70);
		vtree.draw(s.root());
	}

	for (int i = 0; i < 100; i++) {
		s.remove(rand() % 70);
		vtree.draw(s.root());
	}

	return 0;
}