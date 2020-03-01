#pragma once

#include "Skiplist.h"
#include <cstdlib>

template<typename K,typename V>
V* Skiplist<K, V>::get(K k) {
	if (empty())
		return nullptr;
	ListNode<Quadlist<Entry<K, V>>*>* qlist = this->first();//��ײ���ת��
	QuadlistNode<Entry<K, V>>* p = qlist->_data->first();//����ײ���׽ڵ㿪ʼ��
	return skipSearch(qlist, p, k) ? &(p->entry.value) : nullptr;
}

/*
skiplist�����㷨,���ڲ�����
���:qlistΪ�����б�,pΪqlist���׽ڵ�
����:���ɹ�,pΪ���йؼ��������ڵ�,qlistΪp������������
	 ��ʧ��,qlistΪ��(��List�к���ڱ����Ľڵ�,�䲻�����κ�������ڵ�),pΪ��ײ��в�����k�����ڵ��λ��
Լ��:�����������ʱ,��������ȡ�����
*/
template<typename K,typename V>
bool Skiplist<K, V>::skipSearch(
	ListNode<Quadlist<Entry<K, V>>*>* &qlist,
	QuadlistNode<Entry<K, V>>* &p,
	K& k
) {
	while (true) {
		while (p->succ && (p->entry.value <= k))//��ǰ������
			p = p->succ;
		p = p->pred;//����һ��,��������Ϊ�˶������ͬʱ����ʱȡ�����
		if (p->pred && (k == p->entry.key))
			return true;
		qlist = qlist->_succ;
		if (!qlist->_succ)return false;//�����ǰqlist�����ڱ�,��ʧ��
		p = (p->pred) ? p->below : qlist->_data->first();//����ת�뵱ǰ����һ��,��p->pred�����ж��Ƿ�ֹp��ǰ����ͷ�ڱ���,û��below
	}
}

//����ײ�������,���Ҷ���֮һ��������,�������൱������������Ϊ8,������ĸ߶�����Ϊ4,��ȡ����,��Ϊ���ֲ���
template<typename K,typename V>
bool Skiplist<K, V>::put(K k, V v) {//��ת����������㷨
	Entry<K, V> e = Entry<K, V>(k, v);
	if (empty())//�����ǰΪ��
		this->insertAsFirst(new Quadlist<Entry<K,V>>);//���½�һ��������ڵ�,����������
	ListNode<Quadlist<Entry<K, V>>*>* qlist = this->first();//ȡ��������ڵ�
	QuadlistNode<Entry<K, V>>* p = qlist->_data->first();//����������׸�������ڵ�
	if (skipSearch(qlist, p, k))//����ҵ�,��Ҫ��������ײ�,δ�ҵ�,pҲ�������ײ�k֮ǰ�Ľڵ�
		while (p->below)//������ͬ����,�ֶ���ת������
			p = p->below;
	qlist = this->last();//��qlist��Ϊ��ײ�(p��ʱҲ����ײ�)
	QuadlistNode<Entry<K, V>>* b = qlist->_data->insertAfterAbove(e, p);//�����׶�Ӧλ�ò����´���(����һ��������ͬ��value�Ĵ�������)
	while (rand() & 1) {//ģ����Ӳ�Ҳ���
		while (qlist->_data->valid(p) && !p->above)//�ҳ����ڵ�ǰp�ĸ߶ȵ����ǰ��
			p = p->pred;
		//�����if-else������p�ƶ�������һ��Ķ�Ӧλ�ô�
		if (!qlist->_data->valid(p)) {//���p�Ƶ���header
			if (qlist == this->first())//�����ǰ�Ѿ������
				this->insertAsFirst(new Quadlist<Entry<K, V>>);//����Ҫ����һ��
			p = qlist->_pred->_data->first()->pred;//p��ֵΪ��һ������ڵ��е��������header
		}
		else 
			p = p->above;
		qlist = qlist->_pred;//qlistҲ����һ��
		b = qlist->_data->insertAfterAbove(e, p, b);//��b����ڵ�����������һ��
	}
	return true;
}

template<typename K,typename V>
bool Skiplist<K, V>::remove(K k) {
	if (empty())
		return false;
	ListNode<Quadlist<Entry<K, V>>*>* qlist = this->first();//��������ڵ�
	QuadlistNode<Entry<K, V>>* p = qlist->_data->first();//�׽ڵ�
	if (!skipSearch(qlist, p, k))
		return false;
	do {//��һ�����ϵ�������ڵ�ȫ��ɾ��
		QuadlistNode<Entry<K, V>>* lower = p->below;
		qlist->_data->remove(p);
		p = lower; qlist = qlist->_succ;
	} while (qlist->_succ);
	while (!empty() && this->first()->_data->empty())//������ϵ��±���,ɾ�����ھ���ɾ�����������Ѿ����˵�������
		List<Quadlist<Entry<K, V> >* >::remove(this->first());
	return true;
}