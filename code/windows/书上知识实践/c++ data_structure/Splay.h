#pragma once

#include "BST.h"

template<typename T>
class Splay:public BST<T>{
protected:
	BinNode<T>* splay(BinNode<T>* v);//将v伸展至根
public:
	BinNode<T>* &search(const T&e);//查找(重写)
	BinNode<T>* insert(const T&e);//插入(重写)
	bool remove(const T&e);//删除(重写)
};

#include "Splay_implenmentation.h"