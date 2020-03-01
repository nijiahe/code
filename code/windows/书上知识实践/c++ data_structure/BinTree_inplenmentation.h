#pragma once

#include "BinTree.h"
#include "release.h"
#include <algorithm>

using namespace std;

template<typename T>
int BinTree<T>::updateHeight(BinNode<T>* x) {
	return x->height = 1 + max(stature(x->lChild), stature(x->rChild));
}

template<typename T>
void BinTree<T>::updateHeightAbove(BinNode<T>* x) {
	while (x) {
		int prev = x->size();
		if (prev == updateHeight(x))break;
		x = x->parent;
	}
}

template<typename T>
BinNode<T>* BinTree<T>::insertAsLC(T const &e, BinNode<T> *x) {
	_size++; 
	x->insertAsLC(e);
	updateHeightAbove(x);
	return x->lChild;
}

template<typename T>
BinNode<T>* BinTree<T>::insertAsRC(T const &e, BinNode<T> *x) {
	_size++;
	x->insertAsRC(e);
	updateHeightAbove(x);
	return x->rChild;
}

template<typename T>
BinNode<T>* BinTree<T>::attachAsLC(BinNode<T>* x, BinTree<T>* &T) {//T��Ϊx����������
	if (x->lChild = T->_root) x->lChild->parent = x; //����
	_size += T->_size; updateHeightAbove(x); //����ȫ����ģ��x�������ȵĸ߶�
	T->_root = NULL; T->_size = 0; release(T); T = NULL; return x; //�ͷ�ԭ�������ؽ���λ��
}

template<typename T>
BinNode<T>* BinTree<T>::attachAsRC(BinNode<T>* x, BinTree<T>* &T) {//T��Ϊx����������
	if (x->rChild = T->_root) x->rChild->parent = x; //����
	_size += T->_size; updateHeightAbove(x); //����ȫ����ģ��x�������ȵĸ߶�
	T->_root = NULL; T->_size = 0; release(T); T = NULL; return x; //�ͷ�ԭ�������ؽ���λ��
}

template<typename T>
int BinTree<T>::remove(BinNode<T>* x) {//ɾ����λ��x���ڵ�Ϊ�������������ظ�����ԭ�ȵĹ�ģ
	FromParentTo(*x) = nullptr; //�ж����Ը��ڵ��ָ��
	updateHeightAbove(x->parent); //�������ȸ߶�
	int n = removeAt(x); _size -= n; return n; //ɾ������x�����¹�ģ������ɾ���ڵ�����
}

template < typename T> //ɾ����������λ��x���Ľڵ㼰���������ر�ɾ���ڵ����ֵ
static int removeAt(BinNode<T>* x) { //assert: xΪ�������еĺϷ�λ��
	if (!x) return 0; //�ݹ��������
	int n = 1 + removeAt(x->lChild) + removeAt(x->rChild); //�ݹ��ͷ���������
	release(x->data); release(x); return n; //�ͷű�ժ���ڵ㣬������ɾ���ڵ�����
} //release()�����ͷŸ��ӽṹ�����㷨��ֱ�ӹ�ϵ������ʵ����������

template <typename T> //���������������㷨��������x�ӵ�ǰ����ժ���������װΪһ�ö�����������
BinTree<T>* BinTree<T>::secede(BinNode<T>* x) { //assert: xΪ�������еĺϷ�λ��
	FromParentTo(*x) = NULL; //�ж����Ը��ڵ��ָ��
	updateHeightAbove(x->parent); //����ԭ�����������ȵĸ߶�
	BinTree<T>* S = new BinTree<T>; S->_root = x; x->parent = NULL; //������xΪ��
	S->_size = x->size(); _size -= S->_size; return S; //���¹�ģ�����ط������������
}

template <typename T>
BinNode<T>* BinTree<T>::insertAsRoot(T const& e) {
	_size = 1; return _root = new BinNode<T>(e);
}
