#pragma once

#include "BTNode.h"
#include "release.h"

template<typename T>
class BTree {
protected:
	int _size;//�ؼ�������
	int _order;//B-���״�,��һ�������ڵ������_order���ӽڵ�,��������ڵ㱾��������_order-1��С�ڵ�
	
	BTNode<T>* _root;//���ڵ�
	BTNode<T>* _hot;//search()���������ʵķǿսڵ�
	void solveOverflow(BTNode<T> * v);//���������������ķ��Ѳ���
	void solveUnderflow(BTNode<T> * v);//ɾ��������������ĺϲ�����
public:
	BTree(int order = 3) :_order(order), _size(0)//���캯��,Ĭ�����3��,������3��С�ڵ�,4·B-��
	{_root = new BTNode<T>(); }
	~BTree() { 
		if (_root)
			release(_root); 
	}
	int const order() { return _order; }//���ؽ״�
	int const size() { return _size; }//���ش�С
	BTNode<T>* &root() { return _root; }//����rootָ�������,����ֱ���޸�
	bool empty() const { return !_root; }//�Ƿ�Ϊ��
	BTNode<T>* search(const T&e);//����
	bool insert(const T&e);//����
	bool remove(const T&e);//ɾ��
};

#include "BTree_inlenmentation.h"