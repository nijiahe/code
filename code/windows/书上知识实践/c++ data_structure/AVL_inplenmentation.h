#pragma once

#include "AVL.h"

template<typename T>
BinNode<T>* AVL<T>::insert(const T& e) {
	BinNode<T>* & x = this->searchIn(e);
	if (x)//e�Ѿ�����
		return x;
	this->_size++;
	BinNode<T>* xx = x = new BinNode<T>(e, this->_hot);
	for (BinNode<T>* g = this->_hot; g; g = g->parent) {//��ͣ�ı��������ĸ��ڵ�,ֱ����һ��ʧ�⴦,�ָ�ƽ���,���ϵĲ��ٻ�ʧ��
		if (!AVLBalanced(*g)) {//���AVLʧ��
			FromParentTo(*g) = this->rotateAt(tallerChild(tallerChild(g)));//rotateAt��ֻ������������,û����������,����������
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
	if (!x)//���û�ҵ�
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