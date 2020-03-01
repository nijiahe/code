#pragma once

#include "PQ.h"
#include "BinTree.h"

template<typename T>
class PQ_LeftHeap :public PQ<T>, public BinTree<T> {
public:
	PQ_LeftHeap() {};//Ĭ�Ϲ���
	PQ_LeftHeap(T* E, int n)//��������
	{
		for (int i = 0; i < n; i++)
			PQ<T>::insert(E[i]);
	}
	void insert(T e);//���ձȽ���ȷ�ϵ����ȼ�����Ԫ��
	T getMax();//ȡ�����ȼ���ߵ�Ԫ��
	T delMax();//ɾ�����ȼ���ߵ�Ԫ��
};

#include "PQ_LeftHeap_inplenmentation.h"