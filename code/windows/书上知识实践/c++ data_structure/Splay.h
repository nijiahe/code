#pragma once

#include "BST.h"

template<typename T>
class Splay:public BST<T>{
protected:
	BinNode<T>* splay(BinNode<T>* v);//��v��չ����
public:
	BinNode<T>* &search(const T&e);//����(��д)
	BinNode<T>* insert(const T&e);//����(��д)
	bool remove(const T&e);//ɾ��(��д)
};

#include "Splay_implenmentation.h"