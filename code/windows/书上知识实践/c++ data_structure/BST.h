#pragma once

#include "BinTree.h"

template <typename T> class BST : public BinTree<T> { //��BinTree����BSTģ����
protected:
    BinNode<T>* _hot; //�����С��ڵ�ĸ���

    BinNode<T>* connect34( //���ա�3 + 4���ṹ������3���ڵ㼰�Ŀ�����
		BinNode<T>* a, BinNode<T>* b, BinNode<T>* c,
		BinNode<T>* T0, BinNode<T>* T1, BinNode<T>* T2, BinNode<T>* T3);
	BinNode<T>* connect34_To_rightdown(
		BinNode<T>* a, BinNode<T>* b, BinNode<T>* c,
		BinNode<T>* T0, BinNode<T>* T1, BinNode<T>* T2, BinNode<T>* T3);
	BinNode<T>* connect34_To_rightup(
		BinNode<T>* a, BinNode<T>* b, BinNode<T>* c,
		BinNode<T>* T0, BinNode<T>* T1, BinNode<T>* T2, BinNode<T>* T3);
	BinNode<T>* rotateAt(BinNode<T>* x); //��x���丸�ס��游��ͳһ��ת����
public: //�����ӿڣ���virtual���Σ�ǿ��Ҫ�����������ࣨBST���֣����ݸ��ԵĹ��������д
    virtual BinNode<T>* & searchIn(const T& e); //����
    virtual BinNode<T>* insert(const T& e); //����,Ψһ����,������,��ֻ���ض�Ӧλ��
	virtual bool remove(const T& e); //ɾ��
};


#include "BST_inplenmentation.h"