#pragma once

#include "BST.h"

#define IsBlack(p) (!(p)||(RB_BLACK==(p)->color))//�ж��Ƿ�Ϊ��
#define IsRed(p) (!IsBlack(p))
#define BlackHeightUpdated(x) ( /*��������¸߶�(�����ǰ�ڵ��Ǻڽڵ�,��߶ȼ�һ,���򲻱�)*/\
	(stature( (x).lChild ) == stature( (x).rChild ) ) && \
	( (x).height == ( IsRed(&x)?stature( (x).lChild ):stature( (x).lChild) +1) ) \
)

template<typename T>
class RedBlack :public BST<T> {
protected:
	void solveDoubleRed(BinNode<T>* x);//˫������
	void solveDoubleBlack(BinNode<T>* x);//˫������
	virtual int updateHeight(BinNode<T>* x);//���¸߶�
public:
	BinNode<T>* insert(const T&e);//����
	bool remove(const T&e);
};

#include "RedBlack_inpenmentation.h"