#pragma once

#include "PQ_LeftHeap.h"

template<typename T>
static BinNode<T>* merge(BinNode<T>* a, BinNode<T>* b) {
	if (!a)return b;//µÝ¹é»ù
	if (!b)return a;//µÝ¹é»ù
	if (a->data < b->data)
		std::swap(a->data, b->data);
	//Æ´½Ó
	a->rChild = merge(a->rChild, b);
	a->rChild->parent = a;
	if (!a->lChild || a->lChild->npl < a->rChild->npl)
		std::swap(a->lChild, a->rChild);
	a->npl = a->rChild ? a->rChild->npl + 1 : 1;
	return a;
}

template<typename T>
void PQ_LeftHeap<T>::insert(T e) {
	BinNode<T>* x = new BinNode<T>(e);
	this->_root = merge(this, x);
	this->_root->parent = nullptr;
	this->_size++;
}

template<typename T>
T PQ_LeftHeap<T>::getMax() {
	return this->_root;
}

template<typename T>
T PQ_LeftHeap<T>::delMax() {
	T e = this->_root->data;
	BinNode<T>* lc = this->_root->lChild;
	BinNode<T>* rc = this->_root->rChild;
	delete this->_root; this->_size--;
	this->_root = merge(lc, rc);
	if (this->_root)this->_root->parent = nullptr;
	return e;
}