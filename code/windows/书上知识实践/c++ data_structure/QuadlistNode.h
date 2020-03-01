#pragma once

#include "Entry.h"

//T是一个词条类型
template<typename T>
struct QuadlistNode { //四联表节点
	T entry;//词条

	QuadlistNode<T>* pred;//前驱
	QuadlistNode<T>* succ;//后驱

	QuadlistNode<T>* above;//上邻
	QuadlistNode<T>* below;//下邻

	//构造函数
	QuadlistNode(T e = T(),QuadlistNode<T>* p =nullptr,QuadlistNode<T>* s = nullptr,QuadlistNode<T>* a =nullptr,QuadlistNode<T>* b = nullptr)
		:entry(e),pred(p),succ(s),above(a),below(b){}

	//插入,插在自己后面,b上面
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