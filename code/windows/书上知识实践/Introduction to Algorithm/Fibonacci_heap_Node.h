#pragma once
#include "common.h"

template<typename T>
class FibNode
{
public:
	T   key;						// 关键字(键值)
	int degree;                     // 度数
	FibNode<T> *left;				// 左兄弟
	FibNode<T> *right;				// 右兄弟
	FibNode<T> *child;				// 第一个孩子节点
	FibNode<T> *parent;				// 父节点
	int marked;                     //是否被删除第1个孩子(1表示删除，0表示未删除)


	static FibNode* fib_node_make(T key);	//创建斐波那契堆的节点
	static void fib_node_cat(FibNode *a, FibNode *b);	//将双向链表b链接到双向链表a的后面

	void fib_node_remove();		//将node从双链表移除
	void fib_node_add_Before(FibNode<T>* root);	//将自身加入到root之前,root是目标链表中的节点
	void fib_heap_link_as_child(FibNode<T>* root);	//将node插入到root的孩子节点中,并且因为换位置了,marked标记清除
	FibNode<T>* fib_node_search(T k);//在以当前节点为根的最小堆中查找键值为key的节点

};

#include "Fibonacci_heap_Node_inplenmentatino.h"