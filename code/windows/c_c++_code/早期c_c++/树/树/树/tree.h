#pragma once
#include<iostream>
#include"leaf.h"


template<class T>
class tree
{
public:
	leaf<T>* topleaf=nullptr;
	int leafnum = 0;
public:
	tree();
	~tree();
	leaf<T>* idtoleaf(leaf<T>* top,int id);//根据id寻找叶子
	void addleaf(T value);//增加叶子
	void showtreehouxu(leaf<T>* top);//后序序遍历并按层次显示整棵树
	void showtreeqianxu(leaf<T>* top);//前序遍历并按层次显示整棵树
	void showtreezhongxu(leaf<T>* top,int grade=0);//中序遍历并按层次显示整棵树
};

