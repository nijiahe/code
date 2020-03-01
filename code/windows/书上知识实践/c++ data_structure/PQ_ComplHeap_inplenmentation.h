#pragma once

#include "PQ_ComplHeap.h"

template<typename T>
T PQ_ComplHeap<T>::getMax() { return this->_elem[0]; }

template<typename T>
void PQ_ComplHeap<T>::insert(T e) {
	Vector<T>::insert(e);//���뵽���
	percolateUp(this->_size - 1);//�����һ��Ԫ�ؽ�������
}

template<typename T>
int PQ_ComplHeap<T>::percolateUp(int i) {
	while (ParentValid(i)) {//��i���и���
		int j = Parent(i);
		if (this->_elem[j] > this->_elem[i])
			break;
		std::swap(this->_elem[i], this->_elem[j]);
		i = j;
	}
	return i;
}

template<typename T>
T PQ_ComplHeap<T>::delMax() {
	T maxElem = this->_elem[0]; this->_elem[0] = this->_elem[--this->_size];//������_size��С,��ʵ�ʵ�ɾ��Ԫ��,ʵ����VectorҲ��������
	percolateDown(this->_size, 0);
	return maxElem;
}

template<typename T>
int PQ_ComplHeap<T>::percolateDown(int n, int i) {
	int j;
	while(i!=(j=ProperParent(this->_elem,n,i)))
	{
		std::swap(this->_elem[i], this->_elem[j]);
		i = j;
	}
	return i;
}

template<typename T>
void PQ_ComplHeap<T>::heapify(int n) {
	for (int i = LastInternal(n); InHeap(n, i); i--)
		percolateDown(n, i);
}