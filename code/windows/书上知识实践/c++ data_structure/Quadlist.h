#pragma once

#include "QuadlistNode.h"

//四联表,T是一种词条类型
template<typename T>
class Quadlist {
private:
	int _size;//大小
	QuadlistNode<T>* header;//头哨兵
	QuadlistNode<T>* trailer;//尾哨兵

protected:
	void init();//初始化
	int clear();//清除所有节点

public:
	Quadlist() { init(); }//构造函数
	~Quadlist() { clear(); delete header; delete trailer; }//析构函数

	int size() const { return _size; }
	bool empty() const { return _size <= 0; }

	QuadlistNode<T>* first() const { return header->succ; } //首节点位置
	QuadlistNode<T>* last() const { return trailer->pred; } //末节点位置
	bool valid(QuadlistNode<T>* p) //判断位置p是否对外合法
	    { return p && (trailer != p) && (header != p); }

	// 可写访问接口
	T remove(QuadlistNode<T>* p); //删除（合法）位置p处的节点，返回被删除节点的数值
	QuadlistNode<T>* insertAfterAbove(T const& e, QuadlistNode<T>* p, QuadlistNode<T>* b = nullptr);//将e作为p的后继、b的上邻插入
	
	//遍历
	void traverse(void(*) (T&)); //遍历各节点，依次实施指定操作（函数指针，只读或局部修改）
	template < typename VST>void traverse(VST&); //遍历各节点，依次实施指定操作（函数对象，可全局性修改节点）
};

#include "Quadlist_inplenmentation.h"