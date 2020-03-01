#pragma once

#include "BinTree.h"
#include "release.h"
#include <algorithm>

using namespace std;

template<typename T>
int BinTree<T>::updateHeight(BinNode<T>* x) {
	return x->height = 1 + max(stature(x->lChild), stature(x->rChild));
}

template<typename T>
void BinTree<T>::updateHeightAbove(BinNode<T>* x) {
	while (x) {
		int prev = x->size();
		if (prev == updateHeight(x))break;
		x = x->parent;
	}
}

template<typename T>
BinNode<T>* BinTree<T>::insertAsLC(T const &e, BinNode<T> *x) {
	_size++; 
	x->insertAsLC(e);
	updateHeightAbove(x);
	return x->lChild;
}

template<typename T>
BinNode<T>* BinTree<T>::insertAsRC(T const &e, BinNode<T> *x) {
	_size++;
	x->insertAsRC(e);
	updateHeightAbove(x);
	return x->rChild;
}

template<typename T>
BinNode<T>* BinTree<T>::attachAsLC(BinNode<T>* x, BinTree<T>* &T) {//T作为x左子树接入
	if (x->lChild = T->_root) x->lChild->parent = x; //接入
	_size += T->_size; updateHeightAbove(x); //更新全树规模与x所有祖先的高度
	T->_root = NULL; T->_size = 0; release(T); T = NULL; return x; //释放原树，返回接入位置
}

template<typename T>
BinNode<T>* BinTree<T>::attachAsRC(BinNode<T>* x, BinTree<T>* &T) {//T作为x右子树接入
	if (x->rChild = T->_root) x->rChild->parent = x; //接入
	_size += T->_size; updateHeightAbove(x); //更新全树规模与x所有祖先的高度
	T->_root = NULL; T->_size = 0; release(T); T = NULL; return x; //释放原树，返回接入位置
}

template<typename T>
int BinTree<T>::remove(BinNode<T>* x) {//删除以位置x处节点为根的子树，返回该子树原先的规模
	FromParentTo(*x) = nullptr; //切断来自父节点的指针
	updateHeightAbove(x->parent); //更新祖先高度
	int n = removeAt(x); _size -= n; return n; //删除子树x，更新规模，返回删除节点总数
}

template < typename T> //删除二叉树中位置x处的节点及其后代，返回被删除节点的数值
static int removeAt(BinNode<T>* x) { //assert: x为二叉树中的合法位置
	if (!x) return 0; //递归基：空树
	int n = 1 + removeAt(x->lChild) + removeAt(x->rChild); //递归释放左、右子树
	release(x->data); release(x); return n; //释放被摘除节点，并返回删除节点总数
} //release()负责释放复杂结构，与算法无直接关系，具体实现详见代码包

template <typename T> //二叉树子树分离算法：将子树x从当前树中摘除，将其封装为一棵独立子树返回
BinTree<T>* BinTree<T>::secede(BinNode<T>* x) { //assert: x为二叉树中的合法位置
	FromParentTo(*x) = NULL; //切断来自父节点的指针
	updateHeightAbove(x->parent); //更新原树中所有祖先的高度
	BinTree<T>* S = new BinTree<T>; S->_root = x; x->parent = NULL; //新树以x为根
	S->_size = x->size(); _size -= S->_size; return S; //更新规模，返回分离出来的子树
}

template <typename T>
BinNode<T>* BinTree<T>::insertAsRoot(T const& e) {
	_size = 1; return _root = new BinNode<T>(e);
}
