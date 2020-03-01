#pragma once

typedef enum { RB_RED, RB_BLACK } RBColor; //�ڵ���ɫ
#define stature(p) ((p)?(p)->height:-1)

#define IsRoot(x) ( ! ( (x).parent ) )
#define IsLChild(x) (!IsRoot(x) && (&(x) == (x).parent->lChild))
#define IsRChild(x) (!IsRoot(x) && (&(x) == (x).parent->rChild))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lChild)
#define HasRChild(x) ((x).rChild)
#define HasChild(x) (HasLChild(x) || HasRChild(x)) //����ӵ��һ������
#define HasBothChild(x) (HasLChild(x) && HasRChild(x)) //ͬʱӵ����������
#define IsLeaf(x) (!HasChild(x))
#define sibling(p) /*�ֵ�*/ \
   ( IsLChild( * (p) ) ? (p)->parent->rChild : (p)->parent->lChild )

#define uncle(x) /*����*/ \
   ( IsLChild( * ( (x)->parent ) ) ? (x)->parent->parent->rChild : (x)->parent->parent->lChild )

#define FromParentTo(x) /*���Ը��׵�����*/ \
   ( IsRoot(x) ? this->_root : ( IsLChild(x) ? (x).parent->lChild : (x).parent->rChild ) )

#include "InfoH.h"

template<typename T>class BinNode:public InfoH {
public:
	BinNode<T>* parent;
	BinNode<T>* lChild;
	BinNode<T>* rChild;
	T data;
	int height;
	int npl;//Null Path Length(��ʽ��)
	RBColor color;//��ɫ(�����)

	int size();//�����Ե�ǰ�ڵ�Ϊ���ڵ�������Ľڵ���

	BinNode() :parent(nullptr), lChild(nullptr), rChild(nullptr), height(0), npl(1), color(RB_RED) { }
	//BinNode(T const&e,BinNode<T>* p):height(p->height+1),parent(p),data(e){}
	BinNode(T e, BinNode<T>* p = nullptr, BinNode<T>* lc = nullptr, BinNode<T>* rc = nullptr,int h = 0,int l = 1,RBColor c = RB_RED):
		data(e),parent(p),lChild(lc),rChild(rc),height(h),npl(l),color(c){}
	
	BinNode<T>* insertAsLC(T const&);
	BinNode<T>* insertAsRC(T const&);
	BinNode<T>* succ();

	//traverse func
	template<typename VST> void travLevel(VST&);//������α���
	template<typename VST> void travPre(VST&);//����ǰ�����
	template<typename VST> void travIn(VST&);//�����������
	template<typename VST> void travPost(VST&);//�����������

	// �Ƚ������е�����������һ���������в��䣩
	bool operator< (BinNode const& bn) { return data < bn.data; } //С��
	bool operator== (BinNode const& bn) { return data == bn.data; } //����
};




#include "BinNode_inplenmentation.h"

