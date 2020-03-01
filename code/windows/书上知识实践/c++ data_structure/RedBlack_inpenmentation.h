#pragma once

#include "RedBlack.h"

template<typename T>
int RedBlack<T>::updateHeight(BinNode<T>* x) {//更新节点高度
	x->height = max(stature(x->lChild), stature(x->rChild));
	return IsBlack(x) ? x->height++ : x->height;
}

template<typename T>
BinNode<T>* RedBlack<T>::insert(const T&e) {
	BinNode<T>* &x = this->searchIn(e);
	if (x)//如果已存在,直接返回
		return x;
	//否则插入
	x = new BinNode<T>(e, this->_hot, nullptr, nullptr, -1);//-1是树的高度,默认为红色
	this->_size++;
	solveDoubleRed(x);
	return x ? x : this->_hot->parent;//solveDoubleRed接收的不是引用,照理说x不会被改动啊
}

template<typename T>
void RedBlack<T>::solveDoubleRed(BinNode<T>* x){
	if (IsRoot(*x)) {//如果已经根节点
		this->_root->color = RB_BLACK;
		this->_root->height++;
		return;
	}
	BinNode<T>* p = x->parent;
	if (IsBlack(p)) //如果p是黑色,则未引发双红,可直接返回,这也就保证了p为根节点时可以直接返回,不会有g不存在的情况
		return;
	//否则
	BinNode<T>* g = p->parent;
	BinNode<T>* u = uncle(x);//叔父节点,即g异于p的孩子节点
	if (IsBlack(u)) {//如果叔父节点是黑,则没有继续诱发双红的可能,此次修正后可直接返回
		if (IsLChild(*x) == IsLChild(*p)) //如果x于p同侧
			p->color = RB_BLACK;//则p的颜色变为黑色
		else//异侧
			x->color = RB_BLACK;
		g->color = RB_RED;//不管如何,g的颜色都会变成红色
		BinNode<T>* gg = g->parent;//曾祖父
		BinNode<T>* r = FromParentTo(*g) = this->rotateAt(x);//rotate中调用3+4重构,且自行处理各种情况,并且gg的相应孩子更新
		r->parent = gg;//r的父节点更新
	}
	else {//叔父是红色
		p->color = RB_BLACK; p->height++;//这里的height++没看懂,为什么要++?,底下不是红节点吗
		u->color = RB_BLACK; u->height++;//这里的height++也是
		if (!IsRoot(*g))g->color = RB_RED;
		solveDoubleRed(g);
	}
}

template<typename T>
bool RedBlack<T>::remove(const T& e) {
	BinNode<T>* &x = this->searchIn(e);
	if (!x)//如果不存在,返回失败
		return false;
	BinNode<T>* r = removeAt(x, this->_hot);//与直接后继进行数值上的交换,然后删除直接后继所在的,返回新的在被删位置上的节点
	if (!(--this->_size))//如果连根节点都被删完了,直接返回
		return true;
	if (!this->_hot) {//如果_hot为空,即x为根节点,则将其变为黑节点
		this->_root->color = RB_BLACK;
		updateHeight(this->_root);
		return true;
	}
	if (BlackHeightUpdated(*this->_hot))//如果实际被删节点为红,其父节点必为黑,则必平衡
		return true;
	//若不平衡,若新节点为红,则原先被删节点必为黑,则作为替代,将这个节点染黑即可,这样就像黑色根本没变化一样
	if (IsRed(r)) {
		r->color = RB_BLACK; r->height++; return true;
	}
	//否则,两个被删节点和现在在其位置上的节点都是黑色的,现在一定少了一个黑,需要修正
	solveDoubleBlack(r);
	return true;
}

//首先r节点是接替了被删节点位置的新节点,由于两个都是黑,删了一个以后导致了此通路上黑色失衡
//其次,由于被删节点是直接后继,所以接替它的r节点也没有左孩子节点
template<typename T>
void RedBlack<T>::solveDoubleBlack(BinNode<T>* r) {
	BinNode<T>* p = r ? r->parent : this->_hot;
	if (!p)//r为根节点,则返回
		return;
	BinNode<T>* s = (r == p->lChild) ? p->rChild : p->lChild;//r的兄弟节点
	if (IsBlack(s)) {//兄弟s为黑
		BinNode<T>* t = nullptr;
		if (IsRed(s->rChild))
			t = s->rChild;
		if (IsRed(s->lChild))
			t = s->lChild;
		if (t) {//如果s有红色的孩子,则将红色孩子染黑,然后进行3+4重构即可
			RBColor oldColor = p->color;//备份原p节点的颜色
			BinNode<T>* b = FromParentTo(*p) = this->rotateAt(t);//3+4重构
			if (HasLChild(*b)) {
				b->lChild->color = RB_BLACK;
				updateHeight(b->lChild);
			}
			if (HasRChild(*b)) {
				b->rChild->color = RB_BLACK;
				updateHeight(b->rChild);
			}
			b->color = oldColor;
			updateHeight(b);
		}
		else {//s无红孩子,则将s改为红
			s->color = RB_RED;
			s->height--;
			if (IsRed(p)) {//如果p为红,BB-2R,此时黑色不会再向上失衡,结束
				p->color = RB_BLACK;
			}
			else {//BB-2B,继续向上检查是否失衡,p为黑
				p->height--;//p保持黑,但旋转后黑高度下降
				solveDoubleBlack(p);//继续迭代
			}
		}
	}
	else {//如果兄弟s为红,则p和s的孩子必然都为黑
		s->color = RB_BLACK; p->color = RB_RED;
		BinNode<T>* t = IsLChild(*s) ? s->lChild : s->rChild;//取其兄弟s同侧的孩子,对其做3+4调整,令s成为顶点,p与s同侧孩子高度一样
		this->_hot = p; FromParentTo(*p) = this->rotateAt(t);
		solveDoubleBlack(r);//继续对r调整,此时r的新父亲是红色,所以此时r的新兄弟s必为黑色,顾只有BB-1或BB-2R的情况
	}
}