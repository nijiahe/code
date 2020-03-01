#pragma once

#include "Fibonacci_heap_Node.h"
#include <queue>

/*
 * 创建斐波那契堆的节点
 */
template<typename T>
static FibNode<T>* FibNode<T>::fib_node_make(T key)
{
	FibNode<T>* node;

	node = new FibNode<T>;
	if (node == nullptr)
	{
		printf("Error: make Node failed\n");
		return nullptr;
	}
	node->key = key;
	node->degree = 0;
	node->left = node;
	node->right = node;
	node->parent = nullptr;
	node->child = nullptr;

	return node;
}


/*
* 将node从双链表移除
*/
template<typename T>
void FibNode<T>::fib_node_remove()
{
	left->right = right;
	right->left = left;
	if (parent->child == this)
		parent->child == this->right;
	parent->degree--;
	if (!parent->degree)//父节点没孩子了
		parent->child = nullptr;
	parent = nullptr;
}

/*
 * 将自身加入到root节点之前
 *   a …… root
 *   a …… node …… root
 *
 * 注意： 此处node是单个节点，而root是双向链表
*/
template<typename T>
void FibNode<T>::fib_node_add_Before(FibNode<T>* root)
{
	left = root->left;
	root->left->right = this;
	right = root;
	root->left = this;
	parent = root->parent;
	if (parent)
		parent->degree++;
}

/*
 * 将双向链表b链接到双向链表a的后面
 *
 * 注意： 此处a和b都是双向链表
*/
template<typename T>
static void FibNode<T>::fib_node_cat(FibNode *a, FibNode *b) {
	FibNode *tmp;

	tmp = a->right;
	a->right = b->right;
	b->right->left = a;
	b->right = tmp;
	tmp->left = b;
}

/*
* 将node插入到root的孩子节点中
*/
template<typename T>
void FibNode<T>::fib_heap_link_as_child(FibNode<T>* root) {
	// 将node从双链表中移除
	fib_node_remove();
	// 将node设为root的孩子
	if (root->child == nullptr)
		root->child = this;
	else
		fib_node_add_Before(root->child);

	marked = 0;
}

/*
 * 在以当前节点为根的最小堆中查找键值为key的节点,找到返回此节点,否则返回nullptr
 */
template<typename T>
FibNode<T>* FibNode<T>::fib_node_search(T k)
{
	FibNode<T>* p = nullptr;    // 存放要查找的节点
	FibNode<T>* temp = nullptr; // 用来当前检查到的元素

	queue<FibNode<T>*> q;
	q.push(this);
	while (!q.empty()) {//当s非空时
		temp = q.front(); q.pop();
		if (temp->key == k){//当前检查的节点是所找节点
			p = temp;
			break;
		}
		else {//不是所找节点,若有孩子,将孩子全部放入队列中
			FibNode<T>* c = temp->child; 
			FibNode<T>* c1 = c;
			if(c!=nullptr)
				do {
					q.push(c1); c1 = c1->right;
				} while (c1 != c);
		}
	}
	return p;
}