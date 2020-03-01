#pragma once

#include "Entry.h"

//T��һ����������
template<typename T>
struct QuadlistNode { //������ڵ�
	T entry;//����

	QuadlistNode<T>* pred;//ǰ��
	QuadlistNode<T>* succ;//����

	QuadlistNode<T>* above;//����
	QuadlistNode<T>* below;//����

	//���캯��
	QuadlistNode(T e = T(),QuadlistNode<T>* p =nullptr,QuadlistNode<T>* s = nullptr,QuadlistNode<T>* a =nullptr,QuadlistNode<T>* b = nullptr)
		:entry(e),pred(p),succ(s),above(a),below(b){}

	//����,�����Լ�����,b����
	QuadlistNode<T>* insertAsSuccAbove(T const& e, QuadlistNode<T>* b = nullptr);
};

template<typename T>
QuadlistNode<T>* QuadlistNode<T>::insertAsSuccAbove(T const&e, QuadlistNode<T>* b) {
	QuadlistNode<T>* x = new QuadlistNode<T>(e, this, succ, nullptr, b);
	succ->pred = x;
	succ = x;
	if (b)b->above = x;
	return x;
}