#pragma once

typedef enum { RB_RED, RB_BLACK } RBColor; //节点颜色
#define stature(p) ((p)?(p)->height:-1)

#define IsRoot(x) ( ! ( (x).parent ) )
#define IsLChild(x) (!IsRoot(x) && (&(x) == (x).parent->lChild))
#define IsRChild(x) (!IsRoot(x) && (&(x) == (x).parent->rChild))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lChild)
#define HasRChild(x) ((x).rChild)
#define HasChild(x) (HasLChild(x) || HasRChild(x)) //至少拥有一个孩子
#define HasBothChild(x) (HasLChild(x) && HasRChild(x)) //同时拥有两个孩子
#define IsLeaf(x) (!HasChild(x))
#define sibling(p) /*兄弟*/ \
   ( IsLChild( * (p) ) ? (p)->parent->rChild : (p)->parent->lChild )

#define uncle(x) /*叔叔*/ \
   ( IsLChild( * ( (x)->parent ) ) ? (x)->parent->parent->rChild : (x)->parent->parent->lChild )

#define FromParentTo(x) /*来自父亲的引用*/ \
   ( IsRoot(x) ? this->_root : ( IsLChild(x) ? (x).parent->lChild : (x).parent->rChild ) )

#include "InfoH.h"

template<typename T>class BinNode:public InfoH {
public:
	BinNode<T>* parent;
	BinNode<T>* lChild;
	BinNode<T>* rChild;
	T data;
	int height;
	int npl;//Null Path Length(左式堆)
	RBColor color;//颜色(红黑树)

	int size();//计算以当前节点为根节点的子树的节点数

	BinNode() :parent(nullptr), lChild(nullptr), rChild(nullptr), height(0), npl(1), color(RB_RED) { }
	//BinNode(T const&e,BinNode<T>* p):height(p->height+1),parent(p),data(e){}
	BinNode(T e, BinNode<T>* p = nullptr, BinNode<T>* lc = nullptr, BinNode<T>* rc = nullptr,int h = 0,int l = 1,RBColor c = RB_RED):
		data(e),parent(p),lChild(lc),rChild(rc),height(h),npl(l),color(c){}
	
	BinNode<T>* insertAsLC(T const&);
	BinNode<T>* insertAsRC(T const&);
	BinNode<T>* succ();

	//traverse func
	template<typename VST> void travLevel(VST&);//子树层次遍历
	template<typename VST> void travPre(VST&);//子树前序遍历
	template<typename VST> void travIn(VST&);//子树中序遍历
	template<typename VST> void travPost(VST&);//子树后序遍历

	// 比较器、判等器（各列其一，其余自行补充）
	bool operator< (BinNode const& bn) { return data < bn.data; } //小于
	bool operator== (BinNode const& bn) { return data == bn.data; } //等于
};




#include "BinNode_inplenmentation.h"

