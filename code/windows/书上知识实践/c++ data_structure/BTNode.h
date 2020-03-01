#pragma once

#include "Vector.h"

template<typename T>
struct BTNode {//B-���ڵ�
	BTNode<T>* parent;//���ڵ�
	Vector<T> key;//ֵ
	Vector<BTNode<T>* > child;//������,�䳤�ȱ�key��һ

	//���캯��
	BTNode() { parent = nullptr; child.insert(0, nullptr); }
	BTNode(T e, BTNode<T>* lChild = nullptr, BTNode<T>* rChild = nullptr) {
		parent = nullptr;
		key.insert(0, e);
		child.insert(0, lChild);child.insert(0, rChild);
		if (lChild)lChild->parent = this;
		if (rChild)rChild->parent = this;
	}
	void logBTNode() {
		for (int i = 0; i < key.size(); i++)
			std::cout << key[i] << " ";
	}

};