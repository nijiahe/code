#pragma once

#include "BST.h"

#define Balanced(x) (stature((x).lChild)==stature((x).rChild))//����ƽ������
#define BalFac(x)	(stature((x).lChild)-stature((x).rChild))//ƽ������
#define AVLBalanced(x)	((-2<BalFac(x))&&(BalFac(x)<2))

//ѡ���ڵ�x���Һ����и��ߵĽڵ�,����ȸ�,��ѡ��xͬ���,���ȸߵĻ�AVLBalanced(x)����true,һ���ֲ�������ִ���˾�
//ͬ��,��ΪAVLBalanced(x)ʧ��,���Աؿ���ѡ��tallerChild(tallerChild(x)),������ȡ��nullptr
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