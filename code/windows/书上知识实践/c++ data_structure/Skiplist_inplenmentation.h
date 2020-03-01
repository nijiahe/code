#pragma once

#include "Skiplist.h"
#include <cstdlib>

template<typename K,typename V>
V* Skiplist<K, V>::get(K k) {
	if (empty())
		return nullptr;
	ListNode<Quadlist<Entry<K, V>>*>* qlist = this->first();//最底层跳转表
	QuadlistNode<Entry<K, V>>* p = qlist->_data->first();//从最底层的首节点开始找
	return skipSearch(qlist, p, k) ? &(p->entry.value) : nullptr;
}

/*
skiplist查找算法,供内部调用
入口:qlist为顶层列表,p为qlist的首节点
出口:若成功,p为命中关键码的最顶部节点,qlist为p所属的四联表
	 若失败,qlist为空(即List中后继哨兵处的节点,其不包含任何四联表节点),p为最底层中不大于k的最大节点的位置
约定:多个词条命中时,沿四联表取最后者
*/
template<typename K,typename V>
bool Skiplist<K, V>::skipSearch(
	ListNode<Quadlist<Entry<K, V>>*>* &qlist,
	QuadlistNode<Entry<K, V>>* &p,
	K& k
) {
	while (true) {
		while (p->succ && (p->entry.value <= k))//从前向后查找
			p = p->succ;
		p = p->pred;//倒退一步,这样做是为了多个词条同时命中时取最后者
		if (p->pred && (k == p->entry.key))
			return true;
		qlist = qlist->_succ;
		if (!qlist->_succ)return false;//如果当前qlist已是哨兵,则失败
		p = (p->pred) ? p->below : qlist->_data->first();//否则转入当前塔下一层,对p->pred进行判断是防止p当前处在头哨兵处,没有below
	}
}

//向最底层插入词条,并且二分之一概率上升,这样就相当于若四联表长度为8,则链表的高度理想为4,若取特例,则为二分查找
template<typename K,typename V>
bool Skiplist<K, V>::put(K k, V v) {//跳转表词条插入算法
	Entry<K, V> e = Entry<K, V>(k, v);
	if (empty())//如果当前为空
		this->insertAsFirst(new Quadlist<Entry<K,V>>);//则新建一个四联表节点,插入链表中
	ListNode<Quadlist<Entry<K, V>>*>* qlist = this->first();//取顶层链表节点
	QuadlistNode<Entry<K, V>>* p = qlist->_data->first();//顶层链表的首个四联表节点
	if (skipSearch(qlist, p, k))//如果找到,需要到塔的最底层,未找到,p也存放着最底层k之前的节点
		while (p->below)//如有雷同词条,手动跳转到塔底
			p = p->below;
	qlist = this->last();//将qlist设为最底层(p此时也在最底层)
	QuadlistNode<Entry<K, V>>* b = qlist->_data->insertAfterAbove(e, p);//在塔底对应位置插入新词条(允许一层塔中有同样value的词条存在)
	while (rand() & 1) {//模拟抛硬币操作
		while (qlist->_data->valid(p) && !p->above)//找出高于当前p的高度的最近前驱
			p = p->pred;
		//这里的if-else操作将p移动到了上一层的对应位置处
		if (!qlist->_data->valid(p)) {//如果p移到了header
			if (qlist == this->first())//如果当前已经是最顶层
				this->insertAsFirst(new Quadlist<Entry<K, V>>);//就需要新增一层
			p = qlist->_pred->_data->first()->pred;//p赋值为上一层链表节点中的四联表的header
		}
		else 
			p = p->above;
		qlist = qlist->_pred;//qlist也上升一层
		b = qlist->_data->insertAfterAbove(e, p, b);//将b这个节点往上再升高一层
	}
	return true;
}

template<typename K,typename V>
bool Skiplist<K, V>::remove(K k) {
	if (empty())
		return false;
	ListNode<Quadlist<Entry<K, V>>*>* qlist = this->first();//顶层链表节点
	QuadlistNode<Entry<K, V>>* p = qlist->_data->first();//首节点
	if (!skipSearch(qlist, p, k))
		return false;
	do {//将一座塔上的四联表节点全部删除
		QuadlistNode<Entry<K, V>>* lower = p->below;
		qlist->_data->remove(p);
		p = lower; qlist = qlist->_succ;
	} while (qlist->_succ);
	while (!empty() && this->first()->_data->empty())//链表从上到下遍历,删除现在经过删除操作可能已经空了的四联表
		List<Quadlist<Entry<K, V> >* >::remove(this->first());
	return true;
}