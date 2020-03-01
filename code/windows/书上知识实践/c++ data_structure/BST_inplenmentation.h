#pragma once

#include "BST.h"

#define EQUAL(e, v)  (!(v) || (e) == (v)->data) //�ڵ�v��������ͨ���ڱ����Ĺؼ������e

template < typename T> //����vΪ���ģ�AVL��SPLAY��rbTree�ȣ�BST�����в��ҹؼ���e
static BinNode<T>* & searchIn_iterative(BinNode<T>* & v, const T& e, BinNode<T>* & hot) {
    if (EQUAL(e, v)) 
		return v; 
	hot = v; //�˻���������������ڵ�v������
    while (1) { //һ��أ��������ϵ�
		BinNode<T>* & c = (e < hot->data) ? hot->lChild : hot->rChild; //ȷ�����뷽��
		if (EQUAL(e, c)) 
			return c; 
		hot = c; //���з��أ���������һ��
	
	} //hotʼ��ָ�����һ��ʧ�ܽڵ�
} //����ʱ������ֵָ�����нڵ㣨������ͨ���ڱ�����hotָ���丸�ף��˻�ʱΪ��ʼֵNULL��

template < typename T> //����vΪ���ģ�AVL��SPLAY��rbTree�ȣ�BST�����в��ҹؼ���e
static BinNode<T>* & searchIn_recursive(BinNode<T>* & v, const T& e, BinNode<T>* & hot) {
	if (EQUAL(e,v)) 
		return v; //�ݹ�����ڽڵ�v��������ͨ��ڵ㣩������
	hot = v; //һ��������ȼ��µ�ǰ�ڵ㣬Ȼ����
	return searchIn_recursive(((e < v->data) ? v->lChild : v->rChild), e, hot); //����һ�㣬�ݹ����
} //����ʱ������ֵָ�����нڵ㣨������ͨ���ڱ�����hotָ���丸�ף��˻�ʱΪ��ʼֵNULL��

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
	if (!x) {//����ԭ��û������ڵ�,���²���
		x = new BinNode<T>(e,_hot);
		this->_size++;
		this->updateHeightAbove(x);
	}
	return x;
}

//�����µĴ�����ʵ�ʱ�ɾ���ڵ��ϵĽڵ�
template<typename T>
static BinNode<T>* removeAt(BinNode<T>* &x, BinNode<T>* &hot) {//���ﴫ���x����һ�����丸�ڵ��еĺ��ӽڵ��ַ������,���˾���ֱ���޸ĸ��׽ڵ��еĺ���
	BinNode<T>* w = x;
	BinNode<T>* succ = nullptr;//��ʾ��xɾ������ʲô���x��λ��
	if (!HasLChild(*x))//���û������,�������Һ��Ӷ�û��
		succ = x = x->rChild;//x��Դ�ڸ��ڵ��е��ӽڵ�����,ֱ���޸ļ���
	else if (!HasRChild(*x))//���û���Һ���
		succ = x = x->lChild;
	else {//���Һ��Ӷ���
		w = w->succ();//w=x�ĺ��
		swap(x->data, w->data);//����x,w������,��ʱҪɾ��Ԫ�ر�Ϊ��w
		BinNode<T>* u = w->parent;//ͨ��w�ĸ����ж�wֱ����x���ҽڵ㻹����Ҫ������ת����
		((u == x) ? u->rChild : u->lChild) = succ = w->rChild;//����w�Ǻ��,���Ա�û������,ȡw���Һ�����Ϊ����w�Ľڵ�
	}
	//����,w��Ϊ����Ҫɾȥ�Ľڵ�,succ��������������wλ�õĽڵ�,�����Ǹ��սڵ�
	hot = w->parent;
	if (succ)succ->parent = hot;//������ǿսڵ�,succ�ĸ���Ϊ_hot
	release(w->data); release(w); return succ;
}

template <typename T>
bool BST<T>::remove(const T& e) { //ɾ��
	BinNode<T>*& x = searchIn(e);
	if (!x)//˵��δ�ҵ�
		return false;
	removeAt(x,_hot);
	this->_size--;
	this->updateHeightAbove(_hot);
	return true;
}

/*
T0,T1,T2,T3�ǽڵ������,����Ϊ��,�����Ҫ�ж�
		|--------b------|
	|---a---|		|---c----|
	T0		T1		T2		T3
*/
template <typename T>
BinNode<T>* BST<T>::connect34( //���ա�3 + 4���ṹ������3���ڵ㼰�Ŀ�����
	BinNode<T>* a, BinNode<T>* b, BinNode<T>* c,
	BinNode<T>* T0, BinNode<T>* T1, BinNode<T>* T2, BinNode<T>* T3) {
	a->lChild = T0; if (T0)T0->parent = a;
	a->rChild = T1; if (T1)T1->parent = a; this->updateHeight(a);
	c->lChild = T2; if (T2)T2->parent = c;
	c->rChild = T3; if (T3)T3->parent = c; this->updateHeight(c);
	b->lChild = a; a->parent = b;
	b->rChild = c; c->parent = b; this->updateHeight(b);

	return b;//����������
}

template <typename T>
BinNode<T>* BST<T>::rotateAt(BinNode<T>* v) { //��x���丸�ס��游��ͳһ��ת����,vΪ�ﱲ�ڵ�
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
	else {//v���Һ���
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
BinNode<T>* BST<T>::connect34_To_rightdown(//ԭ�������ϵ�,��Ϊ����
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
BinNode<T>* BST<T>::connect34_To_rightup(//ԭ�������µ�,��Ϊ����
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