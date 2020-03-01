#pragma once

#include "BTNode.h"
#include "release.h"

template<typename T>
class BTree {
protected:
	int _size;//关键码总数
	int _order;//B-树阶次,即一个超级节点最多有_order个子节点,这个超级节点本身最多包含_order-1个小节点
	
	BTNode<T>* _root;//根节点
	BTNode<T>* _hot;//search()操作最后访问的非空节点
	void solveOverflow(BTNode<T> * v);//插入后上溢而引发的分裂操作
	void solveUnderflow(BTNode<T> * v);//删除后下溢而引发的合并操作
public:
	BTree(int order = 3) :_order(order), _size(0)//构造函数,默认最低3阶,即含有3个小节点,4路B-树
	{_root = new BTNode<T>(); }
	~BTree() { 
		if (_root)
			release(_root); 
	}
	int const order() { return _order; }//返回阶次
	int const size() { return _size; }//返回大小
	BTNode<T>* &root() { return _root; }//返回root指针的引用,可以直接修改
	bool empty() const { return !_root; }//是否为空
	BTNode<T>* search(const T&e);//查找
	bool insert(const T&e);//插入
	bool remove(const T&e);//删除
};

#include "BTree_inlenmentation.h"