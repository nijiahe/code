#pragma once

template<typename T>
class ListNode
{
public:
	// 成员
	T _data; //数据
	ListNode<T>* _pred; //前驱
	ListNode<T>* _succ; //后继
	// 构造函数
	ListNode() {} //针对header和trailer的构造
	ListNode(T e, ListNode<T>* p = nullptr, ListNode<T>* s = nullptr): _data(e), _pred(p), _succ(s) {} //默认构造器
	// 操作接口
	ListNode<T>* insertAsPred(T const& e); //紧靠当前节点之前插入新节点
	ListNode<T>* insertAsSucc(T const& e); //紧随当前节点之后插入新节点
};

#include "ListNode_implementation.h"