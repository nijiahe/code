#pragma once

#include "List.h"
#include "Entry.h"//����
#include "Quadlist.h"//������
#include "Dictionary.h"//�ʵ�

//��ת��,���ڴʵ������ʵ��,�����ÿһ���ڵ���һ��������
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
	bool put(K k, V v);//���
	V* get(K k);//��ȡ
	bool remove(K k);//ɾ��
};

#include "Skiplist_inplenmentation.h"