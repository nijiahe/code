#pragma once

#include "Splay.h"

template <typename NodePosi> inline //在节点*p与*lc（可能为空）之间建立父（左）子关系
void attachAsLChild(NodePosi p, NodePosi lc) { 
	p->lChild= lc; 
	if (lc) 
		lc->parent = p; 
}

template <typename NodePosi> inline //在节点*p与*rc（可能为空）之间建立父（右）子关系
void attachAsRChild(NodePosi p, NodePosi rc) { 
	p->rChild = rc; 
	if (rc) 
		rc->parent = p; 
}

template<typename T>
BinNode<T>* Splay<T>::splay(BinNode<T> * v) {//将v伸展至根
	if (!v)
		return nullptr;
	BinNode<T>* p; BinNode<T>* g;
	while ((p = v->parent) && (g = p->parent)) {
		BinNode<T>* gg = g->parent;
		if (IsLChild(*v)) {
			if (IsLChild(*p))//都是左,右上的,改为右下
				v = this->connect34_To_rightdown(v, p, g, v->lChild, v->rChild, p->rChild, g->rChild);
			else {//一左一右,普通的connect
				v = this->connect34(g, v, p, g->lChild, v->lChild, v->rChild, p->rChild);
			}
		}
		else {
			if (IsRChild(*p)) {//都是右,右下的,改为右上
				v = this->connect34_To_rightup(g, p, v, g->lChild, p->lChild, v->lChild, v->rChild);
			}
			else {//一左一右
				v = this->connect34(p, v, g, p->lChild, v->lChild, v->rChild, g->rChild);
			}
		}
		if (!gg)
			v->parent = nullptr;//如果没曾祖父,则v已经被伸展至树根
		else
			(g == gg->lChild) ? attachAsLChild(gg, v) : attachAsRChild(gg, v);
		this->updateHeight(g); this->updateHeight(p); this->updateHeight(v);//原本是v最低,其次p,g现在则是完全相反了,所以最后更新v
	}
	if (p = v->parent) {//此时p为根节点,g为nullptr,v为p的儿子,还需要做一次旋转,将v变为根节点
		if (IsLChild(*v)) {
			attachAsLChild(p, v->rChild); attachAsRChild(v, p);
		}
		else {//v是rChild
			attachAsRChild(p, v->lChild); attachAsLChild(v, p);
		}
		this->updateHeight(p); this->updateHeight(v);
	}
	v->parent = nullptr; 
	return v;
}

template<typename T>
BinNode<T>* &Splay<T>::search(const T&e) {//查找(重写)
	BinNode<T>* p = this->searchIn(e);

	this->_root = splay(p ? p : this->_hot);
	
	return this->_root;
}

template<typename T>
BinNode<T>* Splay<T>::insert(const T&e) {//插入(重写),返回插入后的根节点
	if (!this->_root) {//空树情况
		this->_size++;
		return this->_root = new BinNode<T>(e);
	}
	BinNode<T>* p = search(e);//调用Splay中的search,已经继承了splay伸展,会自动将找到的或者_hot伸展到根节点
	if (p->data==e)//search会将搜索后的新根节点返回,不管这个根节点是否就是所要找的目标
		return this->_root;//已有,则返回当前_root,就是p
	this->_size++;
	BinNode<T>* t = this->_root;//保存一下原根节点,根节点马上要变为e了
	//未找到,需要插入,此时根节点为_hot
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
bool Splay<T>::remove(const T&e) {//删除(重写)
	if (!this->_root)return false;//树空,直接返回
	BinNode<T>* p = search(e);
	if (p->data!=e)//没找到,直接返回
		return false;
	//若找到,则p此时已是根节点
	if (!HasLChild(*this->_root)) {//如果没左子树
		this->_root = this->_root->rChild;
		if(this->_root)
			this->_root->parent = nullptr;
	}
	else if (!HasRChild(*this->_root)) {//没有右子树
		this->_root = this->_root->lChild;
		if(this->_root)
			this->_root->parent = nullptr;
	}
	else {//左右子树都有
		BinNode<T>* lTree = this->_root->lChild;
		lTree->parent = nullptr; this->_root->lChild = nullptr;//切断左子树
		this->_root = this->_root->rChild; this->_root->parent = nullptr;//将右子树变成树根
		search(e);//对右子树进行一次搜索,生成一颗根节点为e+1,且没有左子树的新树
		lTree->parent = this->_root; this->_root->lChild = lTree;//将左子树拼接回去
	}
	release(p->data); release(p);
	this->_size--;
	if (this->_root)
		this->updateHeight(this->_root);
	return true;
}