#pragma once
#include "common.h"

template<typename T>
class FibNode
{
public:
	T   key;						// �ؼ���(��ֵ)
	int degree;                     // ����
	FibNode<T> *left;				// ���ֵ�
	FibNode<T> *right;				// ���ֵ�
	FibNode<T> *child;				// ��һ�����ӽڵ�
	FibNode<T> *parent;				// ���ڵ�
	int marked;                     //�Ƿ�ɾ����1������(1��ʾɾ����0��ʾδɾ��)


	static FibNode* fib_node_make(T key);	//����쳲������ѵĽڵ�
	static void fib_node_cat(FibNode *a, FibNode *b);	//��˫������b���ӵ�˫������a�ĺ���

	void fib_node_remove();		//��node��˫�����Ƴ�
	void fib_node_add_Before(FibNode<T>* root);	//��������뵽root֮ǰ,root��Ŀ�������еĽڵ�
	void fib_heap_link_as_child(FibNode<T>* root);	//��node���뵽root�ĺ��ӽڵ���,������Ϊ��λ����,marked������
	FibNode<T>* fib_node_search(T k);//���Ե�ǰ�ڵ�Ϊ������С���в��Ҽ�ֵΪkey�Ľڵ�

};

#include "Fibonacci_heap_Node_inplenmentatino.h"