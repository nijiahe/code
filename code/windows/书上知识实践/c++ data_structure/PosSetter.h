#pragma once

#include "InfoH.h"

template<class BinNode>

class PosSetter
{
public:
	PosSetter(BinNode* BinNode::* p, BinNode *BinNode::* l, BinNode *BinNode::* r) :
		parent(p), left(l), right(r){}
	void operator() (BinNode *node)
	{
		BinNode *p = node->*parent;
		if (p != NULL) {
			if (node == p->*left) { node->pos = p->pos - 1; }
			if (node == p->*right) { node->pos = p->pos + 1; }
		}
	}
private:
	BinNode *BinNode:: *parent;
	BinNode *BinNode:: *left;
	BinNode *BinNode:: *right;
};
