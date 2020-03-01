#pragma once

#include "ListNode.h"

typedef int Rank;

template<typename T>
class List
{
private:
	int _size; 
	ListNode<T>* _header; 
	ListNode<T>* _trailer;

protected:
	void init(); //列表创建时的初始化
	int clear(); //清除所有节点
	void copyNodes(ListNode<T>*, int); //初始化列表，复制列表中自位置p起的n项
	void merge(ListNode<T>*&, int, List<T>&, ListNode<T>*, int); //归并
	void mergeSort(ListNode<T>*&, int); //对从p开始连续的n个节点归并排序
	void selectionSort(ListNode<T>*, int); //对从p开始连续的n个节点选择排序
	void insertionSort(ListNode<T>*, int); //对从p开始连续的n个节点插入排序
	ListNode<T>* getNodeByRank(Rank r) const;
	void swapNode(ListNode<T>* n1, ListNode<T>* n2);//不改变节点地址，不重新分配节点的情况下，将两个节点在链表中的顺序完全交换

public:
	//构造函数
	List(); //默认
	List(List<T> const& L); //整体复制列表L
	List(List<T> const& L, Rank r, int n); //复制列表L中自第r项起的n项
	List(ListNode<T>* p, int n); //复制列表中自位置p起的n项
	//析构函数
	~List(); //释放（包含头、尾哨兵在内的）所有节点
	// 只读访问接口
	Rank size() const { return _size; } //规模
	bool empty() const { return _size <= 0; } //判空
	T& operator[] (Rank r) const; //重载，支持循秩访问（效率低）
	ListNode<T>* first() { return _header->_succ; } //首节点位置
	ListNode<T>* last() const { return _trailer->_pred; } //末节点位置
	bool valid(ListNode<T>* p) //判断位置p是否对外合法
	{ return p && (_trailer != p) && (_header != p); } //将头、尾节点等同于NULL
	ListNode<T>* find(T const& e) const //无序列表查找
	{ return find(e, _size, _trailer); }
	ListNode<T>* find(T const& e, int n, ListNode<T>* p) const; //无序区间查找，在节点p的n个真前驱中找到e的最后者
	ListNode<T>* search(T const& e) const //有序列表查找
	{ return search(e, _size, _trailer); }
	ListNode<T>* search(T const& e, int n, ListNode<T>* p) const; //在有序列表内节点p（可能是trailer）的n个（真）前驱中，找到不大于e的最后者
	ListNode<T>* selectMax(ListNode<T>* p, int n); //在p及其n-1个后继中选出最大者
	ListNode<T>* selectMax() { return selectMax(_header->_succ, _size); } //整体最大者
	//可写访问接口
	ListNode<T>* insertAsFirst(T const& e); //将e当作首节点插入
	ListNode<T>* insertAsLast(T const& e); //将e当作末节点插入
	ListNode<T>* insertA(ListNode<T>* p, T const& e); //将e当作p的后继插入（After）
	ListNode<T>* insertB(ListNode<T>* p, T const& e); //将e当作p的前驱插入（Before）
	T remove(ListNode<T>* p); //删除合法位置p处的节点,返回被删除节点
	void merge(List<T>& L) { merge(first(), _size, L, L.first(), L._size); } //全列表归并
	void sort(ListNode<T>* p, int n); //列表区间排序，对用户留的接口，因此p不再是前驱，因为用户不可能输入_header，在具体排序中在还原
	void sort() { sort(first(), _size); } //列表整体排序
	int deduplicate(); //无序去重
	int uniquify(); //有序去重
	void reverse(); //前后倒置（习题）
	//遍历
	void traverse(void(*) (T&)); //遍历，依次实施visit操作（函数指针，只读或局部性修改）
	template < typename VST> void traverse(VST&); //遍历，依次实施visit操作（函数对象，可全局性修改）
};

#include "List_implementation.h"