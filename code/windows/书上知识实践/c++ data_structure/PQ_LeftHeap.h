#pragma once

#include "PQ.h"
#include "BinTree.h"

template<typename T>
class PQ_LeftHeap :public PQ<T>, public BinTree<T> {
public:
	PQ_LeftHeap() {};//默认构造
	PQ_LeftHeap(T* E, int n)//批量构造
	{
		for (int i = 0; i < n; i++)
			PQ<T>::insert(E[i]);
	}
	void insert(T e);//按照比较器确认的优先级插入元素
	T getMax();//取出优先级最高的元素
	T delMax();//删除优先级最高的元素
};

#include "PQ_LeftHeap_inplenmentation.h"