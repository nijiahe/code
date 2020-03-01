#pragma once

#include "Quadlist.h"

//四联表初始化,初始创建头部哨兵和尾部哨兵,其余都指向nullptr
template<typename T>
void Quadlist<T>::init() {
	header = new QuadlistNode<T>;
	trailer = new QuadlistNode<T>;
	header->succ = trailer;header->pred = nullptr;
	trailer->pred = header; trailer->succ = nullptr;
	header->above = trailer->above = nullptr;
	header->below = trailer->below = nullptr;
	_size = 0;
}

template<typename T>
QuadlistNode<T>* Quadlist<T>::insertAfterAbove(T const&e,QuadlistNode<T>* p,QuadlistNode<T>* b){
	_size++;
	return p->insertAsSuccAbove(e, b);
}

template<typename T>
T Quadlist<T>::remove(QuadlistNode<T>* p) {
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	_size--;
	T e = p->entry; delete p;
	return e;
}

template<typename T>
int Quadlist<T>::clear() {
	int oldSize = _size;
	while (0 < _size)
		remove(header->succ);
	return oldSize;
}