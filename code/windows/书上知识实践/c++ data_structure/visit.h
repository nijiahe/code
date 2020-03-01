#pragma once

#include <iostream>
#include "BinNode.h"
#include "Queue.h"
#include "BTNode.h"

template<typename T>
class Visit {
public:
	void operator()(T& data) {
		std::cout << data <<" ";
	}
};

template<typename T>
static void LOG_TREE(BinNode<T>* root) {//����һ��������,���ղ�α��������ṹ
	std::cout << "start log" << std::endl;
	Queue<BinNode<T>* > q[2];
	int flag = 0;//flagΪ0��ʾ���ڴ�q[0]�ж�ȡ�ڵ�,���½ڵ�浽q[1];flagΪ1��ʾ���ڴ�q[1]��ȡ�ڵ�,���½ڵ�浽q[0]
	if (root) {
		q[0].enqueue(root);
		std::cout << "root:" << root->data << std::endl;
	}
	while (!q[0].empty() || !q[1].empty()) {//��q1��q2���ǿ�ʱ
		while (!q[flag].empty()) {//��ǰ���Ķ��зǿ�ʱ
			BinNode<T>* t = q[flag].dequeue();
			if (t->lChild) {
				std::cout << t->lChild->data << " <-" << t->data <<" ";
				q[!flag].enqueue(t->lChild);
			}
			if (t->rChild) {
				std::cout << t->data << " ->" << t->rChild->data << " ";
				q[!flag].enqueue(t->rChild);
			}
		}
		std::cout << std::endl;
		flag = !flag;
	}
}

template<typename T>
static void LOG_BTREE(BTNode<T>* root) {//����һ��B��,���ղ�α��������ṹ
	std::cout << "start log" << std::endl;
	Queue<BTNode<T>* > q[2];
	int flag = 0;//flagΪ0��ʾ���ڴ�q[0]�ж�ȡ�ڵ�,���½ڵ�浽q[1];flagΪ1��ʾ���ڴ�q[1]��ȡ�ڵ�,���½ڵ�浽q[0]
	if (root) {
		q[0].enqueue(root);
		std::cout << "root:";
		root->logBTNode();
		std::cout << std::endl;
	}
	while (!q[0].empty() || !q[1].empty()) {//��q1��q2���ǿ�ʱ
		while (!q[flag].empty()) {//��ǰ���Ķ��зǿ�ʱ
			BTNode<T>* t = q[flag].dequeue();
			std::cout << " ->";
			t->logBTNode();
			std::cout << "<- ";
			for (int i = 0; i < t->child.size(); i++) {
				BTNode<T>* v = t->child[i];
				if(v)
					q[!flag].enqueue(v);
			}
		}
		std::cout << std::endl;
		flag = !flag;
	}
}