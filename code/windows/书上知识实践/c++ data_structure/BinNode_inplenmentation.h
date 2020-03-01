#pragma once

#include "BinNode.h"
#include "visit.h"
#include "Stack.h"
#include "Queue.h"

template<typename T>
BinNode<T>* BinNode<T>::insertAsLC(T const&e) {//assump the lChild is nullptr
	return lChild = new BinNode(e, this);
}

template<typename T>
BinNode<T>* BinNode<T>::insertAsRC(T const& e) {
	return rChild = new BinNode(e, this);
}

template<typename T>
int BinNode<T>::size() {
	int ret = 1;
	ret += lChild ? lChild->size() : 0;
	ret += rChild ? rChild->size() : 0;
	return ret;
}


//��ȱ���(��α���)
template<typename T>
template<typename VST>  void BinNode<T>::travLevel(VST& visit) {
	Queue<BinNode*> q;
	BinNode* x;
	q.enqueue(this);
	while (!q.empty()) {
		x = q.dequeue();
		visit(x->data);
		if(x->lChild)q.enqueue(x->lChild);
		if(x->rChild)q.enqueue(x->rChild);
	}
}

//ǰ��(����)����
template<typename T,typename VST>
void traversePrevOrder_r(BinNode<T>* x, VST &visit) {
	if (!x)return;
	visit(x->data);
	traversePrevOrder_r(x->lChild,visit);
	traversePrevOrder_r(x->rChild,visit);
}

template<typename T, typename VST>
void traversePrevOrder_I1(BinNode<T>* x, VST &visit) {
	Stack<BinNode<T>*> s;
	if (x)s.push(x);
	while (!s.empty())
	{
		x = s.pop(); visit(x->data);
		if (x->rChild)s.push(x->rChild);
		if (x->lChild)s.push(x->lChild);
	}
}

template<typename T, typename VST>
void traversePrevOrder_I2(BinNode<T>* x, VST &visit) {
	Stack<BinNode<T>*> s;
	while (!s.empty() || x) {
		if (x) {
			visit(x->data);
			s.push(x);
			x = x->lChild;
		}
		else {
			x = s.pop()->rChild;
		}
	}
}

template<typename T>
template<typename VST> void BinNode<T>::travPre(VST& visit) {
	switch (rand()%3)
	{
	case 0:
		traversePrevOrder_I1(this, visit);
		break;
	case 1:
		traversePrevOrder_I2(this, visit);
		break;
	default:
		traversePrevOrder_r(this,visit);
		break;
	}
}

//�������
template<typename T, typename VST>void traverseInOrder_r(BinNode<T>* x, VST &visit) {
	if (!x)return;
	if (x->lChild)traverseInOrder_r(x->lChild,visit);
	visit(x->data);
	if (x->rChild)traverseInOrder_r(x->rChild,visit);
}

template<typename T, typename VST>void traverseInOrder_i1(BinNode<T>* x, VST &visit) {
	Stack<BinNode<T>*> s;
	while (!s.empty() || x) {
		if (x) {
			s.push(x);
			x = x->lChild;
		}
		else {
			x = s.pop(); 
			visit(x->data);
			x = x->rChild;
		}
	}
}

template<typename T, typename VST>void traverseInOrder_i2(BinNode<T>* x, VST &visit) {
	while (HasLChild(*x))x = x->lChild;
	while (x) {
		visit(x->data);
		x = x->succ();
	}
}

template<typename T>
template<typename VST> void BinNode<T>::travIn(VST& visit) {
	switch (rand()%3)
	{
	case 0:
		traverseInOrder_i1(this, visit);
		break;
	case 1:
		traverseInOrder_i2(this, visit);
		break;
	default:
		traverseInOrder_r(this, visit);
		break;
	}
}

//�������
template<typename T, typename VST>void traversePostOrder_r(BinNode<T>* x, VST &visit) {
	if (!x)return;
	traversePostOrder_r(x->lChild,visit);
	traversePostOrder_r(x->rChild,visit);
	visit(x->data);
}

template<typename T, typename VST>void traversePostOrder_i1(BinNode<T>* x, VST &visit) {
	Stack<BinNode<T>*> s;
	s.push(nullptr);
	while (!s.empty()||x) {
		if (!HasChild(*x)) {//��������
			BinNode<T>* t;
			do {
				t = x;
				visit(t->data);
				x = s.pop();
			} while (!s.empty()&&t->parent == x);//������ڱ�nullptr��������,���ʾ�Ѿ�����
		}
		else if (HasRChild(*x)) {
			if (HasLChild(*x)) {//��������
				s.push(x);
				s.push(x->rChild);
				x = x->lChild;
			}
			else {//��������
				s.push(x);
				x = x->rChild;
			}
		}
		else {//��������
			s.push(x);
			x = x->lChild;
		}
	}
}


template<typename T>
template<typename VST> void BinNode<T>::travPost(VST& visit) {
	switch (rand() % 2)
	{
	case 0:
		traversePostOrder_i1(this, visit);
		break;
	default:
		traversePostOrder_r(this, visit);
		break;
	}
}

//ֱ�Ӻ��
template <typename T> BinNode<T>* BinNode<T>::succ() { //��λ�ڵ�v��ֱ�Ӻ��
	BinNode<T>* s = this; //��¼��̵���ʱ����
	if (rChild) { //�����Һ��ӣ���ֱ�Ӻ�̱����������У�����ؾ���
		s = rChild; //��������
		while (HasLChild(*s)) s = s->lChild; //�����С���Ľڵ�
	}
	else { //����ֱ�Ӻ��Ӧ�ǡ�����ǰ�ڵ���������������е�������ȡ�������ؾ���
		while (IsRChild(*s)) s = s->parent; //������������֧,���ϳ����Ϸ��ƶ�
		s = s->parent; //����ٳ����Ϸ��ƶ�һ��,���ִ�ֱ�Ӻ�̣�������ڣ�,��������һ�����,��᷵�ظ��ڵ�ĸ���,��nullptr
	}
	return s;
}