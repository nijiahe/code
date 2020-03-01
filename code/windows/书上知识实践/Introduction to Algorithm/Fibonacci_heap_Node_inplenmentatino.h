#pragma once

#include "Fibonacci_heap_Node.h"
#include <queue>

/*
 * ����쳲������ѵĽڵ�
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
* ��node��˫�����Ƴ�
*/
template<typename T>
void FibNode<T>::fib_node_remove()
{
	left->right = right;
	right->left = left;
	if (parent->child == this)
		parent->child == this->right;
	parent->degree--;
	if (!parent->degree)//���ڵ�û������
		parent->child = nullptr;
	parent = nullptr;
}

/*
 * ��������뵽root�ڵ�֮ǰ
 *   a ���� root
 *   a ���� node ���� root
 *
 * ע�⣺ �˴�node�ǵ����ڵ㣬��root��˫������
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
 * ��˫������b���ӵ�˫������a�ĺ���
 *
 * ע�⣺ �˴�a��b����˫������
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
* ��node���뵽root�ĺ��ӽڵ���
*/
template<typename T>
void FibNode<T>::fib_heap_link_as_child(FibNode<T>* root) {
	// ��node��˫�������Ƴ�
	fib_node_remove();
	// ��node��Ϊroot�ĺ���
	if (root->child == nullptr)
		root->child = this;
	else
		fib_node_add_Before(root->child);

	marked = 0;
}

/*
 * ���Ե�ǰ�ڵ�Ϊ������С���в��Ҽ�ֵΪkey�Ľڵ�,�ҵ����ش˽ڵ�,���򷵻�nullptr
 */
template<typename T>
FibNode<T>* FibNode<T>::fib_node_search(T k)
{
	FibNode<T>* p = nullptr;    // ���Ҫ���ҵĽڵ�
	FibNode<T>* temp = nullptr; // ������ǰ��鵽��Ԫ��

	queue<FibNode<T>*> q;
	q.push(this);
	while (!q.empty()) {//��s�ǿ�ʱ
		temp = q.front(); q.pop();
		if (temp->key == k){//��ǰ���Ľڵ������ҽڵ�
			p = temp;
			break;
		}
		else {//�������ҽڵ�,���к���,������ȫ�����������
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