#pragma once

#include "PQ.h"
#include "Vector.h"

#define  Parent(i)         (((i)-1) >> 1) //PQ[i]�ĸ��ڵ㣨floor((i-1)/2)��i����������
#define  LastInternal(n)	Parent(n-1)
#define  LChild(i)         (1 + ((i) << 1)) //PQ[i]������
#define  RChild(i)         ((1 + (i)) << 1) //PQ[i]���Һ���
#define  ParentValid(i)		(0<i)
#define  InHeap(n, i)      (((-1) < (i)) && ((i) < (n))) //�ж�PQ[i]�Ƿ�Ϸ�
#define  LChildValid(n, i) InHeap(n, LChild(i)) //�ж�PQ[i]�Ƿ���һ�����󣩺���
#define  RChildValid(n, i) InHeap(n, RChild(i)) //�ж�PQ[i]�Ƿ�����������
#define  Bigger(PQ, i, j)  ((PQ[i]< PQ[j]) ? j : i) //ȡ���ߣ���ʱǰ�����ȣ�
#define  ProperParent(PQ, n, i) /*���ӣ����ࣩ�����еĴ���*/ \
            ( RChildValid(n, i) ? Bigger( PQ, Bigger( PQ, i, LChild(i) ), RChild(i) ) : \
            ( LChildValid(n, i) ? Bigger( PQ, i, LChild(i) ) : i \
            ) \
            ) //���ʱ���ڵ����ȣ���˿ɱ��ⲻ��Ҫ�Ľ���

//��ȫ����ѵ����ȼ�����
template<typename T>
class PQ_ComplHeap:public PQ<T>,public Vector<T> {
protected:
	int percolateDown(int n, int i);//��ǰn��Ԫ���е���Ϊi�Ľ�������
	int percolateUp(int i);//����Ϊi��Ԫ�ؽ�������
	void heapify(int n);//����
public:
	PQ_ComplHeap(){}
	PQ_ComplHeap(T* A, int n) { copyFrom(A, 0, n); heapify(n); }
	virtual void insert(T e) override;
	T getMax();
	T delMax();
};

#include "PQ_ComplHeap_inplenmentation.h"