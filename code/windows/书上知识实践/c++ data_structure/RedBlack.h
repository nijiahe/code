#pragma once

#include "BST.h"

#define IsBlack(p) (!(p)||(RB_BLACK==(p)->color))//判断是否为黑
#define IsRed(p) (!IsBlack(p))
#define BlackHeightUpdated(x) ( /*红黑树更新高度(如果当前节点是黑节点,则高度加一,否则不变)*/\
	(stature( (x).lChild ) == stature( (x).rChild ) ) && \
	( (x).height == ( IsRed(&x)?stature( (x).lChild ):stature( (x).lChild) +1) ) \
)

template<typename T>
class RedBlack :public BST<T> {
protected:
	void solveDoubleRed(BinNode<T>* x);//双红修正
	void solveDoubleBlack(BinNode<T>* x);//双黑修正
	virtual int updateHeight(BinNode<T>* x);//更新高度
public:
	BinNode<T>* insert(const T&e);//插入
	bool remove(const T&e);
};

#include "RedBlack_inpenmentation.h"