#include "BinTree.h"
#include <cstdlib>

/*
								0
				1							2
		3				4							5
	 6		7									8		9
10		  11 12									  13  14
*/

int main5() {
	BinTree<int> tree;
	tree.insertAsRoot(0);
	tree.insertAsLC(1, tree.root());
	tree.insertAsRC(2, tree.root());
	tree.insertAsLC(3, tree.root()->lChild);
	tree.insertAsRC(4, tree.root()->lChild);
	tree.insertAsRC(5, tree.root()->rChild);
	tree.insertAsLC(6, tree.root()->lChild->rChild);
	tree.insertAsRC(7, tree.root()->lChild->rChild);
	tree.insertAsLC(8, tree.root()->rChild->rChild);
	tree.insertAsRC(9, tree.root()->rChild->rChild);
	tree.insertAsLC(10, tree.root()->lChild->rChild->lChild);
	tree.insertAsLC(11, tree.root()->lChild->rChild->rChild);
	tree.insertAsRC(12, tree.root()->lChild->rChild->rChild);
	tree.insertAsRC(13, tree.root()->rChild->rChild->lChild);
	tree.insertAsLC(14, tree.root()->rChild->rChild->rChild);
	
	Visit<int> v;
	tree.travPre(v);//前序
	cout << endl;
	tree.travIn(v);//中序
	cout << endl;
	tree.travPost(v);//后序
	cout << endl;
	tree.travLevel(v);//层次
	cout << endl;

	system("pause");
	return 0;
}