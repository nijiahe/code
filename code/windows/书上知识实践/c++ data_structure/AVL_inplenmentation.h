#pragma once

#include "AVL.h"

template<typename T>
BinNode<T>* AVL<T>::insert(const T& e) {
	BinNode<T>* & x = this->searchIn(e);
	if (x)//e已经存在
		return x;
	this->_size++;
	BinNode<T>* xx = x = new BinNode<T>(e, this->_hot);
	for (BinNode<T>* g = this->_hot; g; g = g->parent) {//不停的遍历插入点的父节点,直到第一个失衡处,恢复平衡后,其上的不再会失衡
		if (!AVLBalanced(*g)) {//如果AVL失衡
			FromParentTo(*g) = this->rotateAt(tallerChild(tallerChild(g)));//rotateAt中只做到了子连父,没做到父连子,在这里做到
			break;
		}
		else {
			this->updateHeight(g);
		}
	}
	return xx;
}

template<typename T>
bool AVL<T>::remove(const T& e) {
	BinNode<T>* &x = this->searchIn(e);
	if (!x)//如果没找到
		return false;
	this->_size--;
	removeAt(x, this->_hot);
	for (BinNode<T>* g = this->_hot; g; g = g->parent) {
		if (!AVLBalanced(*g))
			g = FromParentTo(*g) = this->rotateAt(tallerChild(tallerChild(g)));
		this->updateHeight(g);
	}
	return true;
}