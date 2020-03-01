#pragma once

#include "List.h"
#include "Entry.h"//词条
#include "Quadlist.h"//四联表
#include "Dictionary.h"//词典

//跳转表,基于词典和链表实现,链表的每一个节点是一个四联表
template<typename K,typename V>
class Skiplist :public Dictionary<K, V>, public List<Quadlist<Entry<K, V> >* > {
protected:
	bool skipSearch(ListNode<Quadlist<Entry<K, V>>*>* &qlist,
		QuadlistNode<Entry<K, V>>* &p,
		K& k);

public:
	int size() const { return empty() ? 0 : this->last()->_data->size(); }
	int level() { return List<Quadlist<Entry<K, V> >* >::size(); }
	bool empty() const { return  List<Quadlist<Entry<K, V> >* >::empty(); }
	bool put(K k, V v);//存放
	V* get(K k);//读取
	bool remove(K k);//删除
};

#include "Skiplist_inplenmentation.h"