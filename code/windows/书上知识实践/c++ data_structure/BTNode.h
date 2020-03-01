#pragma once

#include "Vector.h"

template<typename T>
struct BTNode {//B-树节点
	BTNode<T>* parent;//父节点
	Vector<T> key;//值
	Vector<BTNode<T>* > child;//孩子们,其长度比key多一

	//构造函数
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