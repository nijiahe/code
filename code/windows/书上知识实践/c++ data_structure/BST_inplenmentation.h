#pragma once

#include "BST.h"

#define EQUAL(e, v)  (!(v) || (e) == (v)->data) //节点v（或假想的通配哨兵）的关键码等于e

template < typename T> //在以v为根的（AVL、SPLAY、rbTree等）BST子树中查找关键码e
static BinNode<T>* & searchIn_iterative(BinNode<T>* & v, const T& e, BinNode<T>* & hot) {
    if (EQUAL(e, v)) 
		return v; 
	hot = v; //退化情况：在子树根节点v处命中
    while (1) { //一般地，反复不断地
		BinNode<T>* & c = (e < hot->data) ? hot->lChild : hot->rChild; //确定深入方向
		if (EQUAL(e, c)) 
			return c; 
		hot = c; //命中返回，或者深入一层
	
	} //hot始终指向最后一个失败节点
} //返回时，返回值指向命中节点（或假想的通配哨兵），hot指向其父亲（退化时为初始值NULL）

template < typename T> //在以v为根的（AVL、SPLAY、rbTree等）BST子树中查找关键码e
static BinNode<T>* & searchIn_recursive(BinNode<T>* & v, const T& e, BinNode<T>* & hot) {
	if (EQUAL(e,v)) 
		return v; //递归基：在节点v（或假想的通配节点）处命中
	hot = v; //一般情况：先记下当前节点，然后再
	return searchIn_recursive(((e < v->data) ? v->lChild : v->rChild), e, hot); //深入一层，递归查找
} //返回时，返回值指向命中节点（或假想的通配哨兵），hot指向其父亲（退化时为初始值NULL）

template < typename T>
BinNode<T>* & BST<T>::searchIn(const T& e) {
	/*switch (rand()%2)
	{
	case 0:*/
		return searchIn_iterative(this->_root, e, _hot = nullptr);
	/*default:
		return searchIn_recursive(this->_root, e, _hot = nullptr);*/
	/*}*/
}

template <typename T>
BinNode<T>* BST<T>::insert(const T& e) {
	BinNode<T>*& x = searchIn(e);
	if (!x) {//树中原先没有这个节点,则新插入
		x = new BinNode<T>(e,_hot);
		this->_size++;
		this->updateHeightAbove(x);
	}
	return x;
}

//返回新的存在于实际被删除节点上的节点
template<typename T>
static BinNode<T>* removeAt(BinNode<T>* &x, BinNode<T>* &hot) {//这里传入的x就是一个在其父节点中的孩子节点地址的引用,改了就能直接修改父亲节点中的孩子
	BinNode<T>* w = x;
	BinNode<T>* succ = nullptr;//表示将x删除后用什么替代x的位置
	if (!HasLChild(*x))//如果没有左孩子,或者左右孩子都没有
		succ = x = x->rChild;//x来源于父节点中的子节点引用,直接修改即可
	else if (!HasRChild(*x))//如果没有右孩子
		succ = x = x->lChild;
	else {//左右孩子都有
		w = w->succ();//w=x的后继
		swap(x->data, w->data);//交换x,w的数据,此时要删除元素变为了w
		BinNode<T>* u = w->parent;//通过w的父亲判断w直接是x的右节点还是需要经过左转操作
		((u == x) ? u->rChild : u->lChild) = succ = w->rChild;//由于w是后继,所以必没有左孩子,取w的右孩子作为代替w的节点
	}
	//至此,w变为了需要删去的节点,succ代表了用来代替w位置的节点,可能是个空节点
	hot = w->parent;
	if (succ)succ->parent = hot;//如果不是空节点,succ的父亲为_hot
	release(w->data); release(w); return succ;
}

template <typename T>
bool BST<T>::remove(const T& e) { //删除
	BinNode<T>*& x = searchIn(e);
	if (!x)//说明未找到
		return false;
	removeAt(x,_hot);
	this->_size--;
	this->updateHeightAbove(_hot);
	return true;
}

/*
T0,T1,T2,T3是节点的子树,可能为空,因此需要判断
		|--------b------|
	|---a---|		|---c----|
	T0		T1		T2		T3
*/
template <typename T>
BinNode<T>* BST<T>::connect34( //按照“3 + 4”结构，联接3个节点及四棵子树
	BinNode<T>* a, BinNode<T>* b, BinNode<T>* c,
	BinNode<T>* T0, BinNode<T>* T1, BinNode<T>* T2, BinNode<T>* T3) {
	a->lChild = T0; if (T0)T0->parent = a;
	a->rChild = T1; if (T1)T1->parent = a; this->updateHeight(a);
	c->lChild = T2; if (T2)T2->parent = c;
	c->rChild = T3; if (T3)T3->parent = c; this->updateHeight(c);
	b->lChild = a; a->parent = b;
	b->rChild = c; c->parent = b; this->updateHeight(b);

	return b;//返回新树根
}

template <typename T>
BinNode<T>* BST<T>::rotateAt(BinNode<T>* v) { //对x及其父亲、祖父做统一旋转调整,v为孙辈节点
	BinNode<T>* p = v->parent; BinNode<T>* g = p->parent;
	if (IsLChild(*p)) {
		if (IsLChild(*v)) {
			p->parent = g->parent;
			return connect34(v, p, g, v->lChild, v->rChild, p->rChild, g->rChild);
		}
		else {
			v->parent = g->parent;
			return connect34(p, v, g, p->lChild, v->lChild, v->rChild, g->rChild);
		}
	}
	else {//v是右孩子
		if (IsRChild(*v)) {
			p->parent = g->parent;
			return connect34(g, p, v, g->lChild, p->lChild, v->lChild, v->rChild);
		}
		else {
			v->parent = g->parent;
			return connect34(g, v, p, g->lChild, v->lChild, v->rChild, p->rChild);
		}
			
	}
}

template<typename T>
BinNode<T>* BST<T>::connect34_To_rightdown(//原先是右上的,改为右下
	BinNode<T>* a, BinNode<T>* b, BinNode<T>* c,
	BinNode<T>* T0, BinNode<T>* T1, BinNode<T>* T2, BinNode<T>* T3) {
	a->lChild = T0; if (T0)T0->parent = a;
	a->rChild = b;
	b->lChild = T1; if (T1)T1->parent = b;
	b->rChild = c;
	c->lChild = T2; if (T2)T2->parent = c;
	c->rChild = T3; if (T3)T3->parent = c;
	b->parent = a; c->parent = b;

	return a;
}

template<typename T>
BinNode<T>* BST<T>::connect34_To_rightup(//原先是右下的,改为右上
	BinNode<T>* a, BinNode<T>* b, BinNode<T>* c,
	BinNode<T>* T0, BinNode<T>* T1, BinNode<T>* T2, BinNode<T>* T3) {
	a->lChild = T0; if (T0)T0->parent = a;
	a->rChild = T1; if (T1)T1->parent = a;
	b->lChild = a;
	b->rChild = T2; if (T2)T2->parent = b;
	c->lChild = b;
	c->rChild = T3; if (T3)T3->parent = c;
	a->parent = b;
	b->parent = c;

	return c;
}