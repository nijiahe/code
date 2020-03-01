#pragma once

#include "BinTree.h"

template <typename T> class BST : public BinTree<T> { //由BinTree派生BST模板类
protected:
    BinNode<T>* _hot; //“命中”节点的父亲

    BinNode<T>* connect34( //按照“3 + 4”结构，联接3个节点及四棵子树
		BinNode<T>* a, BinNode<T>* b, BinNode<T>* c,
		BinNode<T>* T0, BinNode<T>* T1, BinNode<T>* T2, BinNode<T>* T3);
	BinNode<T>* connect34_To_rightdown(
		BinNode<T>* a, BinNode<T>* b, BinNode<T>* c,
		BinNode<T>* T0, BinNode<T>* T1, BinNode<T>* T2, BinNode<T>* T3);
	BinNode<T>* connect34_To_rightup(
		BinNode<T>* a, BinNode<T>* b, BinNode<T>* c,
		BinNode<T>* T0, BinNode<T>* T1, BinNode<T>* T2, BinNode<T>* T3);
	BinNode<T>* rotateAt(BinNode<T>* x); //对x及其父亲、祖父做统一旋转调整
public: //基本接口：以virtual修饰，强制要求所有派生类（BST变种）根据各自的规则对其重写
    virtual BinNode<T>* & searchIn(const T& e); //查找
    virtual BinNode<T>* insert(const T& e); //插入,唯一插入,若已有,则只返回对应位置
	virtual bool remove(const T& e); //删除
};


#include "BST_inplenmentation.h"