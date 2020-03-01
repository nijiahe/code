#include "BST.h"
#include "AVL.h"
#include "VisualTree.h"

int main7() {
	BST<int> bst;

	VisualTree<BinNode<int>, int>  vtree(
		&BinNode<int>::parent, &BinNode<int>::lChild, &BinNode<int>::rChild, &BinNode<int>::data
	);
	
	for (int i = 0; i < 100; i++) {
		bst.insert(rand() % 200);
		vtree.draw(bst.root());
	}

	for (int i = 0; i < 50; i++) {
		bst.remove(rand() % 200);
		vtree.draw(bst.root());
	}

	//for (int i = 0; i < 50; i++) {
	//	bst.insert(rand() % 200);
	//	vtree.draw(bst.root());
	//}

	for (int i = 0; i < 50; i++) {
		bst.remove(rand() % 200);
		vtree.draw(bst.root());
	}
	
	/*
	AVL<int> avl;
	
	for (int i = 0; i <100; i++) {
		int num = rand() % 70;
		std::cout << "insert:" << num << std::endl;
		avl.insert(num);
		vtree.draw(avl.root());
	}
	
	for (int i = 0; i < 50; i++) {
		avl.remove(rand() % 70);
		vtree.draw(avl.root());
	}

	for (int i = 0; i < 50; i++) {
		avl.insert(rand() % 70);
		vtree.draw(avl.root());
	}

	for (int i = 0; i < 50; i++) {
		avl.remove(rand() % 70);
		vtree.draw(avl.root());
	}
	*/
	return 0;
}