#pragma once

#include "PQ.h"
#include "Vector.h"

#define  Parent(i)         (((i)-1) >> 1) //PQ[i]的父节点（floor((i-1)/2)，i无论正负）
#define  LastInternal(n)	Parent(n-1)
#define  LChild(i)         (1 + ((i) << 1)) //PQ[i]的左孩子
#define  RChild(i)         ((1 + (i)) << 1) //PQ[i]的右孩子
#define  ParentValid(i)		(0<i)
#define  InHeap(n, i)      (((-1) < (i)) && ((i) < (n))) //判断PQ[i]是否合法
#define  LChildValid(n, i) InHeap(n, LChild(i)) //判断PQ[i]是否有一个（左）孩子
#define  RChildValid(n, i) InHeap(n, RChild(i)) //判断PQ[i]是否有两个孩子
#define  Bigger(PQ, i, j)  ((PQ[i]< PQ[j]) ? j : i) //取大者（等时前者优先）
#define  ProperParent(PQ, n, i) /*父子（至多）三者中的大者*/ \
            ( RChildValid(n, i) ? Bigger( PQ, Bigger( PQ, i, LChild(i) ), RChild(i) ) : \
            ( LChildValid(n, i) ? Bigger( PQ, i, LChild(i) ) : i \
            ) \
            ) //相等时父节点优先，如此可避免不必要的交换

//完全二叉堆的优先级队列
template<typename T>
class PQ_ComplHeap:public PQ<T>,public Vector<T> {
protected:
	int percolateDown(int n, int i);//对前n个元素中的秩为i的进行下滤
	int percolateUp(int i);//对秩为i的元素进行上滤
	void heapify(int n);//建堆
public:
	PQ_ComplHeap(){}
	PQ_ComplHeap(T* A, int n) { copyFrom(A, 0, n); heapify(n); }
	virtual void insert(T e) override;
	T getMax();
	T delMax();
};

#include "PQ_ComplHeap_inplenmentation.h"