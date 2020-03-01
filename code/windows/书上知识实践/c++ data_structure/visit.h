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
static void LOG_TREE(BinNode<T>* root) {//传入一个二叉树,按照层次遍历输出其结构
	std::cout << "start log" << std::endl;
	Queue<BinNode<T>* > q[2];
	int flag = 0;//flag为0表示正在从q[0]中读取节点,将新节点存到q[1];flag为1表示正在从q[1]读取节点,将新节点存到q[0]
	if (root) {
		q[0].enqueue(root);
		std::cout << "root:" << root->data << std::endl;
	}
	while (!q[0].empty() || !q[1].empty()) {//当q1和q2都非空时
		while (!q[flag].empty()) {//当前读的队列非空时
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
static void LOG_BTREE(BTNode<T>* root) {//传入一个B树,按照层次遍历输出其结构
	std::cout << "start log" << std::endl;
	Queue<BTNode<T>* > q[2];
	int flag = 0;//flag为0表示正在从q[0]中读取节点,将新节点存到q[1];flag为1表示正在从q[1]读取节点,将新节点存到q[0]
	if (root) {
		q[0].enqueue(root);
		std::cout << "root:";
		root->logBTNode();
		std::cout << std::endl;
	}
	while (!q[0].empty() || !q[1].empty()) {//当q1和q2都非空时
		while (!q[flag].empty()) {//当前读的队列非空时
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