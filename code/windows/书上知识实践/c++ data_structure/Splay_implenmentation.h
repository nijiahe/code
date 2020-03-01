#pragma once

#include "Splay.h"

template <typename NodePosi> inline //�ڽڵ�*p��*lc������Ϊ�գ�֮�佨���������ӹ�ϵ
void attachAsLChild(NodePosi p, NodePosi lc) { 
	p->lChild= lc; 
	if (lc) 
		lc->parent = p; 
}

template <typename NodePosi> inline //�ڽڵ�*p��*rc������Ϊ�գ�֮�佨�������ң��ӹ�ϵ
void attachAsRChild(NodePosi p, NodePosi rc) { 
	p->rChild = rc; 
	if (rc) 
		rc->parent = p; 
}

template<typename T>
BinNode<T>* Splay<T>::splay(BinNode<T> * v) {//��v��չ����
	if (!v)
		return nullptr;
	BinNode<T>* p; BinNode<T>* g;
	while ((p = v->parent) && (g = p->parent)) {
		BinNode<T>* gg = g->parent;
		if (IsLChild(*v)) {
			if (IsLChild(*p))//������,���ϵ�,��Ϊ����
				v = this->connect34_To_rightdown(v, p, g, v->lChild, v->rChild, p->rChild, g->rChild);
			else {//һ��һ��,��ͨ��connect
				v = this->connect34(g, v, p, g->lChild, v->lChild, v->rChild, p->rChild);
			}
		}
		else {
			if (IsRChild(*p)) {//������,���µ�,��Ϊ����
				v = this->connect34_To_rightup(g, p, v, g->lChild, p->lChild, v->lChild, v->rChild);
			}
			else {//һ��һ��
				v = this->connect34(p, v, g, p->lChild, v->lChild, v->rChild, g->rChild);
			}
		}
		if (!gg)
			v->parent = nullptr;//���û���游,��v�Ѿ�����չ������
		else
			(g == gg->lChild) ? attachAsLChild(gg, v) : attachAsRChild(gg, v);
		this->updateHeight(g); this->updateHeight(p); this->updateHeight(v);//ԭ����v���,���p,g����������ȫ�෴��,����������v
	}
	if (p = v->parent) {//��ʱpΪ���ڵ�,gΪnullptr,vΪp�Ķ���,����Ҫ��һ����ת,��v��Ϊ���ڵ�
		if (IsLChild(*v)) {
			attachAsLChild(p, v->rChild); attachAsRChild(v, p);
		}
		else {//v��rChild
			attachAsRChild(p, v->lChild); attachAsLChild(v, p);
		}
		this->updateHeight(p); this->updateHeight(v);
	}
	v->parent = nullptr; 
	return v;
}

template<typename T>
BinNode<T>* &Splay<T>::search(const T&e) {//����(��д)
	BinNode<T>* p = this->searchIn(e);

	this->_root = splay(p ? p : this->_hot);
	
	return this->_root;
}

template<typename T>
BinNode<T>* Splay<T>::insert(const T&e) {//����(��д),���ز����ĸ��ڵ�
	if (!this->_root) {//�������
		this->_size++;
		return this->_root = new BinNode<T>(e);
	}
	BinNode<T>* p = search(e);//����Splay�е�search,�Ѿ��̳���splay��չ,���Զ����ҵ��Ļ���_hot��չ�����ڵ�
	if (p->data==e)//search�Ὣ��������¸��ڵ㷵��,����������ڵ��Ƿ������Ҫ�ҵ�Ŀ��
		return this->_root;//����,�򷵻ص�ǰ_root,����p
	this->_size++;
	BinNode<T>* t = this->_root;//����һ��ԭ���ڵ�,���ڵ�����Ҫ��Ϊe��
	//δ�ҵ�,��Ҫ����,��ʱ���ڵ�Ϊ_hot
	if (t->data > e) {
		t->parent = this->_root = new BinNode<T>(e, nullptr, t->lChild, t);
		if (t->lChild) {
			t->lChild->parent = this->_root;
			t->lChild = nullptr;
		}
	}
	else {//t->data<e
		t->parent = this->_root = new BinNode<T>(e, nullptr, t, t->rChild);
		if (t->rChild) {
			t->rChild->parent = this->_root;
			t->rChild = nullptr;
		}
	}

	this->updateHeightAbove(t);
	
	return this->_root;
}

template<typename T>
bool Splay<T>::remove(const T&e) {//ɾ��(��д)
	if (!this->_root)return false;//����,ֱ�ӷ���
	BinNode<T>* p = search(e);
	if (p->data!=e)//û�ҵ�,ֱ�ӷ���
		return false;
	//���ҵ�,��p��ʱ���Ǹ��ڵ�
	if (!HasLChild(*this->_root)) {//���û������
		this->_root = this->_root->rChild;
		if(this->_root)
			this->_root->parent = nullptr;
	}
	else if (!HasRChild(*this->_root)) {//û��������
		this->_root = this->_root->lChild;
		if(this->_root)
			this->_root->parent = nullptr;
	}
	else {//������������
		BinNode<T>* lTree = this->_root->lChild;
		lTree->parent = nullptr; this->_root->lChild = nullptr;//�ж�������
		this->_root = this->_root->rChild; this->_root->parent = nullptr;//���������������
		search(e);//������������һ������,����һ�Ÿ��ڵ�Ϊe+1,��û��������������
		lTree->parent = this->_root; this->_root->lChild = lTree;//��������ƴ�ӻ�ȥ
	}
	release(p->data); release(p);
	this->_size--;
	if (this->_root)
		this->updateHeight(this->_root);
	return true;
}