#pragma once

#include "BST.h"

#define Balanced(x) (stature((x).lChild)==stature((x).rChild))//理想平衡条件
#define BalFac(x)	(stature((x).lChild)-stature((x).rChild))//平衡因子
#define AVLBalanced(x)	((-2<BalFac(x))&&(BalFac(x)<2))

//选出节点x左右孩子中更高的节点,如果等高,则选与x同向的,但等高的话AVLBalanced(x)就是true,一般轮不到这里执行了就
//同理,因为AVLBalanced(x)失衡,所以必可以选出tallerChild(tallerChild(x)),而不会取到nullptr
#define tallerChild(x) (  \
	stature( (x)->lChild )<stature( (x)->rChild )?(x)->rChild:(  \
	stature( (x)->lChild )>stature( (x)->rChild )?(x)->lChild:(  \
	IsLChild( *(x) )?(x)->lChild:(x)->rChild  \
	)  \
	)  \
)

template<typename T>
class AVL :public BST<T> {
public:
	BinNode<T>* insert(const T& e);
	bool remove(const T& e);
};

#include "AVL_inplenmentation.h"