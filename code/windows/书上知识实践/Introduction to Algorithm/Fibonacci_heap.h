#pragma once

#include "Fibonacci_heap_Node.h"
#include "common.h"

template<typename T>
class FibHeap {
public:
	int   keyNum;                    // 堆中节点的总数
	int   maxDegree;                 // 最大度(不是根节点中degreee最大的值,而是在extract_min时算法逻辑上形成的所有节点的节点可能存在的最大度,log(&,n),&=(1+√5)/2=黄金分割率)
	FibNode<T>* min;				 // 最小节点(某个最小堆的根节点)
	FibNode<T>** cons;				 // 最大度的内存区域

	//删除堆,调用这个函数前应该先调用destroy_all_node
	static void fib_heap_destroy(FibHeap<T>* heap);
	// 将h1, h2合并成一个堆，并返回合并后的堆
	static FibHeap<T>* fib_heap_union(FibHeap<T> *h1, FibHeap<T> *h2);
	// 打印"斐波那契堆"
	static void fib_print(FibHeap<T>* heap);

	// 新建键值为key的节点，并将其插入到斐波那契堆中,O(1)
	void fib_heap_insert_key(T key);
	// 删除键值为key的结点,通过decrease key+extract_min的方式,需要O(1)+O(lgn)=O(lgn)
	void fib_heap_delete(T key);
	// 移除最小节点,O(lgn),因为需要重构以使不存在相同度的节点,使每个节点的度数回到最多不超过D(n)=O(lgn)=log(&,n),&=(1+√5)/2=黄金分割率
	void fib_heap_extract_min();
	// 更新heap的中的oldkey为newkey,O(1)
	void fib_heap_update(T oldkey, T newkey);
	// 在斐波那契堆heap中是否存在键值为key的节点；存在返回true，否则返回false,O(n)
	bool fib_heap_contains(T key);
	// 获取最小节点对应的值(保存在pkey中)；成功返回1，失败返回0,O(1)
	bool fib_heap_get_min(T& key);
	//删除释放所有节点,将堆变为刚创建时的样子
	void fib_heap_destroy_all_node();
	
protected:
	FibNode<T> *fib_heap_search(T k);				//在堆里寻找
	void fib_heap_insert_node(FibNode<T> *node);	//向堆中插入节点
	FibNode<T>* fib_heap_remove_min();				//将最小节点从堆中删除,(仅仅只是移除,不更新min和maxDegree等,内部接口)
	void fib_heap_cons_make();						//创建fib_heap_consolidate所需空间
	void fib_heap_consolidate();					//合并斐波那契堆的根链表中左右相同度数的树
	FibNode<T>* _fib_heap_extract_min();			//移除最小节点，并返回移除节点后的斐波那契堆(对内接口)
	void fib_heap_cut(FibNode<T>* node);			//将node从其父节点中脱离,并加入到堆的根节点链表中
	void fib_heap_cascading_cut(FibNode<T>* node);	//对节点node进行"级联剪切",即在父亲为非根节点的情况下,其孩子被切除,第一次标记marked,第二次将其提升为新的根节点,并且递归标记
	void fib_heap_decrease(FibNode<T>* node, T key);//将堆中节点node的值减少为key
	void fib_heap_increase(FibNode<T>* node, T key);//将斐波那契堆heap中节点node的值增加为key
	void _fib_heap_update(FibNode<T>* node, T key);	//更新二项堆heap的节点node的键值为key(对内接口)
	void _fib_heap_delete(FibNode<T>* node);		//删除结点node,通过将node值变为min->key-1,使其到根节点链表中(对内接口)
};

// 创建Fibonacci堆(工厂代理模式)
template<typename T>
static FibHeap<T>* fib_heap_make();

#include "Fibonacci_heap_inplenmentation.h"











