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


//广度遍历(层次遍历)
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

//前序(先序)遍历
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

//中序遍历
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

//后序遍历
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
		if (!HasChild(*x)) {//无右无左
			BinNode<T>* t;
			do {
				t = x;
				visit(t->data);
				x = s.pop();
			} while (!s.empty()&&t->parent == x);//如果连哨兵nullptr都被弹出,则表示已经结束
		}
		else if (HasRChild(*x)) {
			if (HasLChild(*x)) {//有右有左
				s.push(x);
				s.push(x->rChild);
				x = x->lChild;
			}
			else {//有右无左
				s.push(x);
				x = x->rChild;
			}
		}
		else {//有左无右
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

//直接后继
template <typename T> BinNode<T>* BinNode<T>::succ() { //定位节点v的直接后继
	BinNode<T>* s = this; //记录后继的临时变量
	if (rChild) { //若有右孩子，则直接后继必在右子树中，具体地就是
		s = rChild; //右子树中
		while (HasLChild(*s)) s = s->lChild; //最靠左（最小）的节点
	}
	else { //否则，直接后继应是“将当前节点包含于其左子树中的最低祖先”，具体地就是
		while (IsRChild(*s)) s = s->parent; //逆向地沿右向分支,不断朝左上方移动
		s = s->parent; //最后再朝右上方移动一步,即抵达直接后继（如果存在）,如果是最后一个后继,则会返回根节点的父亲,即nullptr
	}
	return s;
}